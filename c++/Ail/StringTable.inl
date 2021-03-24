////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __STRING_TABLE_INL__
#define __STRING_TABLE_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class StringTableEntry
// ----- ----------------
template <typename _T>
StringTableEntry<_T>::StringTableEntry(const _T& _data) : Data(_data), Left(null), Middle(null), Right(null)
{
}

template <typename _T>
StringTableEntry<_T>::~StringTableEntry()
{
    Left = Middle = Right = null;
}
////////////////////////////////////////////////////////////////////////////////////////
// class StringTable
// ----- -----------
template <typename _T, typename _Mutex, typename _Allocator>
StringTable<_T, _Mutex, _Allocator>::StringTable(uint _count, uint _alignment, bool _cleanup, const tchar* _mutex_name, uint _timeout) : Cleanup(_cleanup), Root(null), Mutex(_mutex_name, _timeout), Allocator(sizeof(StringTableEntry<_T>), _count, _alignment)
{
}

template <typename _T, typename _Mutex, typename _Allocator>
StringTable<_T, _Mutex, _Allocator>::~StringTable()
{
    Destroy();
}

template <typename _T, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ StringTableEntry<_T>* StringTable<_T, _Mutex, _Allocator>::GetRoot() const
{
    return Root;
}

template <typename _T, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ bool StringTable<_T, _Mutex, _Allocator>::HasString(const tchar* _string) const
{
    return Search(_string);
}

template <typename _T, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ bool StringTable<_T, _Mutex, _Allocator>::Search(const tchar* _string, void** _data) const
{
    //
    Synchronization::Guard<_Mutex> guard(Mutex);
    //
    StringTableEntry<_T>* e = Root;

    int rc;
    tchar* s = const_cast<tchar*>(_string);

    while(e != null)
    {
        if((rc = *s-e->Data) == 0)
        {
            if(*s++ == 0)
            {
                if(_data != null)
                {
                    *_data = e->PData;
                }
                return true;
            }

            e = e->Middle;
        }
        else if(rc < 0) 
        {
            e = e->Left;
        }
        else
        {
            e = e->Right;
        }
    }
    
    return false;
}

template <typename _T, typename _Mutex, typename _Allocator>
void StringTable<_T, _Mutex, _Allocator>::PartialMatchSearch(const StringTableEntry<_T>* _e, const tchar* _string, ...) const
{
    if(_e == null)
    {
        return;
    }
    
    //
    static const tchar _dot_ = _t('.');
    //

    if(*_string == _dot_ || *_string < _e->Data)
    {
        PartialMatchSearch(_e->Left, _string);
    }

    if(*_string == _dot_ || *_string == _e->Data)
    {
        if(_e->Data != 0 && *_string != 0)
        {
            PartialMatchSearch(_e->Middle, _string+1);
        }
    }

    if(*_string == 0 && _e->Data == 0)
    {
        // get the string to somewhere, i.e. Middle->PData could contain the ptr to the string
    }

    if(*_string == _dot_ || *_string > _e->Data)
    {
        PartialMatchSearch(_e->Right, _string);
    }
}

template <typename _T, typename _Mutex, typename _Allocator>
void StringTable<_T, _Mutex, _Allocator>::NearSearch(const StringTableEntry<_T>* _e, const tchar* _string, int _d, ...) const
{
    if(_e == null)
    {
        return;
    }

    if(_d > 0 || *_string < _e->Data)
    {
        NearSearch(_e->Left, _string, _d);
    }

    if(_e->Data == 0)
    {
        if(_tcslen(_string) <= _d)
        {
            // get the string to somewhere, i.e. Middle->PData could contain the ptr to the string
        }
    }
    else
    {
        NearSearch(_e->Middle, *_string ? _string+1 : _string, (*_string == _e->Data) ? _d : _d-1);
    }

    if(_d > 0 || *_string > _e->Data)
    {
        NearSearch(_e->Right, _string, _d);
    }
}

template <typename _T, typename _Mutex, typename _Allocator>
void StringTable<_T, _Mutex, _Allocator>::Insert(const tchar* _string, void* _data)
{
    // see "Fast Algorithms for Sorting and Searching Strings"
    // by Jon L. Bentley and Robert Sedgewick
    // Dr. Dobb's Journal April 1998
    // the best way to insert a string is to sort it and insert from median
    if(_string == null)
    {
        return;
    }
    //
    Synchronization::Guard<_Mutex> guard(Mutex);
    //
    StringTableEntry<_T>*  e;
    StringTableEntry<_T>** pe = &Root;

    int rc;
    tchar* s = const_cast<tchar*>(_string);

    // phase I (skip the same prefix)
    while((e = *pe) != null)
    {
        if((rc = *s-e->Data) == 0)
        {
            if(*s++ == 0)
            {
                return;
            }
            pe = &e->Middle;
        }
        else if(rc < 0)
        {
            pe = &e->Left;
        }
        else
        {
            pe = &e->Right;
        }
    }

    // phase II (insert rest of the input)
    for(;;)
    {
        void* p  = Allocator.Allocate(sizeof(StringTableEntry<_T>));
             *pe = new (p) StringTableEntry<_T>(*s);
              e  = *pe;

        if(*s++ == 0)
        {
            // an entry with Data == '\0' does not have a Middle entry ptr ! ...
            e->PData = _data;
            return;
        }
        pe = &e->Middle;
    }
}

template <typename _T, typename _Mutex, typename _Allocator>
void StringTable<_T, _Mutex, _Allocator>::Destroy()
{
    if(Cleanup)
    {
        //
        Synchronization::Guard<_Mutex> guard(Mutex);
        //
        DoCleanup(Root);
    }
}

template <typename _T, typename _Mutex, typename _Allocator>
void StringTable<_T, _Mutex, _Allocator>::DoCleanup(StringTableEntry<_T>* _e)
{
    if(_e != null)
    {
        DoCleanup(_e->Left);

        if(_e->Data != 0)
        {
            DoCleanup(_e->Middle);
        }

        DoCleanup(_e->Right);

        // destroy
       _e->~StringTableEntry<_T>();
        Allocator.Deallocate(_e);
    }
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __STRING_TABLE_INL__
