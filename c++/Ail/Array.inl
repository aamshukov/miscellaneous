////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __ARRAY_INL__
#define __ARRAY_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class Array
// ----- -----
template <typename _T, typename _Mutex, typename _Allocator>
Array<_T, _Mutex, _Allocator>::Array(uint _count, ushort _delta, int _lb, ushort _flags, const tchar* _mutex_name, uint _timeout) : Mutex(_mutex_name, _timeout)
{
    Initialize(_count, _delta, _lb, _flags);
}

template <typename _T, typename _Mutex, typename _Allocator>
Array<_T, _Mutex, _Allocator>::Array(const Array<_T, typename _Mutex, _Allocator>& _other, const tchar* _mutex_name, uint _timeout) : Mutex(_mutex_name, _timeout)
{
    operator = (_other);
}

template <typename _T, typename _Mutex, typename _Allocator>
Array<_T, _Mutex, _Allocator>::~Array()
{
    Destroy();
}

template <typename _T, typename _Mutex, typename _Allocator>
const Array<_T, _Mutex, _Allocator>& Array<_T, _Mutex, _Allocator>::operator = (const Array<_T, _Mutex, _Allocator>& _other)
{
#ifndef __NO_THREADS__
    Synchronization::Guard<_Mutex> guard(Mutex);
#endif
    //
    if(Data != _other.Data)
    {
        if(_other.Count > 0)
        {
           _T* tmp = reinterpret_cast<_T*>(_Allocator::Allocate(sizeof(_T)*_other.Count));

            try
            {
                for(uint i = 0; i < Count; i++)
                {
                    tmp[i] = _other.Data[i];
                }
            }
            catch(...)
            {
                _Allocator::Deallocate(tmp);
                throw;
            }

            Destroy();

            Data  = tmp;
            Count = _other.Count;
        }
    }
    return *this;
}

template <typename _T, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ _T& Array<_T, _Mutex, _Allocator>::operator [] (int _i)
{
#ifndef __NO_THREADS__
    Synchronization::Guard<_Mutex> guard(Mutex);
#endif
    //
    if(IsAutoResize())
    {
        if(ZeroBase(_i) < ZeroBase(LowerBound) || ZeroBase(_i) >= ZeroBase(LowerBound)+Count)
        {
            Resize(_i+1);
        }
    }
    else
    {
        AssertRange(_i);
    }
    return Data[ZeroBase(_i)];
}

template <typename _T, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ _T& Array<_T, _Mutex, _Allocator>::operator [] (int _i) const
{
#ifndef __NO_THREADS__
    Synchronization::Guard<_Mutex> guard(Mutex);
#endif
    //
    AssertRange(_i);
    return Data[ZeroBase(_i)];
}

template <typename _T, typename _Mutex, typename _Allocator>
void Array<_T, _Mutex, _Allocator>::Initialize(uint _count, ushort _delta, int _lb, ushort _flags)
{
    Flags      = _flags;
    LowerBound = _lb;
    Delta      = _delta;
    Count      = GetNextDelta(_count, GetDelta());
    Data       = null;
    //
    if(Count > 0)
    {
        try
        {
            Data = reinterpret_cast<_T*>(_Allocator::Allocate(sizeof(_T)*Count));
        }
        catch(...)
        {
            Data = null;
            throw;
        }

        if(IsInit())
        {
            SetZero(0, Count);
        }
    }
}

template <typename _T, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ bool Array<_T, _Mutex, _Allocator>::IsSorted() const
{
    return (Flags & Array::Sorted) != 0;
}

template <typename _T, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ bool Array<_T, _Mutex, _Allocator>::IsInit() const
{
    return (Flags & Array::Init) != 0;
}

template <typename _T, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ bool Array<_T, _Mutex, _Allocator>::IsAutoResize() const
{
    return (Flags & Array::AutoResize) != 0;
}

template <typename _T, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ bool Array<_T, _Mutex, _Allocator>::IsShouldDelete() const
{
    return StateObject::IsShouldDelete();
}

template <typename _T, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ StateObject::EState Array<_T, _Mutex, _Allocator>::SetState(StateObject::EState _state)
{
    return StateObject::SetState(_state);
}

template <typename _T, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ bool Array<_T, _Mutex, _Allocator>::IsEmpty() const
{
    return Count == 0;
}

template <typename _T, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ ushort Array<_T, _Mutex, _Allocator>::GetFlags() const
{
    return Flags;
}

template <typename _T, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ void Array<_T, _Mutex, _Allocator>::SetFlags(ushort _remove, ushort _add)
{
    Flags = (Flags & ~_remove) | _add;
}

template <typename _T, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ int Array<_T, _Mutex, _Allocator>::GetLowerBound() const
{
    return LowerBound;
}

template <typename _T, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ uint Array<_T, _Mutex, _Allocator>::GetCount() const
{
    return Count;
}

template <typename _T, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ ushort Array<_T, _Mutex, _Allocator>::GetDelta() const
{
    return Delta;
}

template <typename _T, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ void Array<_T, _Mutex, _Allocator>::SetDelta(ushort _delta)
{
    Delta = _delta;
}

template <typename _T, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ const _T* Array<_T, _Mutex, _Allocator>::GetData() const
{
    return reinterpret_cast<const _T*>(Data);
}

template <typename _T, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ _T* Array<_T, _Mutex, _Allocator>::GetData()
{
    return Data;
}

template <typename _T, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ void Array<_T, _Mutex, _Allocator>::SetData(_T* _data, uint _count)
{
    Destroy();
    //
#ifndef __NO_THREADS__
    Synchronization::Guard<_Mutex> guard(Mutex);
#endif
    //
    Count = _count;
    Data  = _data;
}

template <typename _T, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ bool Array<_T, _Mutex, _Allocator>::HasEntry(const _T& _entry) const
{
    return FindEntry(_entry) != ConstError32;
}

template <typename _T, typename _Mutex, typename _Allocator>
int Array<_T, _Mutex, _Allocator>::FindEntry(const _T& _entry) const
{
#ifndef __NO_THREADS__
    Synchronization::Guard<_Mutex> guard(Mutex);
#endif
    //
    if(IsSorted())
    {
        uint lower = 0;
        uint upper = Count-1;

        while(lower < upper && upper != UINT_MAX)
        {
            uint middle = (lower+upper)/2;
            
            if(reinterpret_cast<_T&>(Data[middle]) == reinterpret_cast<_T&>(_entry))
            {
                return middle;
            }

            if(reinterpret_cast<_T&>(Data[middle]) < reinterpret_cast<_T&>(_entry))
            {
                lower = middle+1;
            }
            else
            {
                upper = middle-1;
            }
        }

        if(lower == upper && reinterpret_cast<_T&>(Data[lower]) == reinterpret_cast<_T&>(_entry))
        {
            return lower;
        }
    }
    else
    {
        for(uint i = 0; i < Count; i++)
        {
            if(Data[i] == _entry)
            {
                return i;
            }
        }
    }
    return ConstError32;
}

template <typename _T, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ void Array<_T, _Mutex, _Allocator>::GetEntry(int _i, _T& _entry) const
{
#ifndef __NO_THREADS__
    Synchronization::Guard<_Mutex> guard(Mutex);
#endif
    //
    AssertRange(_i);
   _entry = Data[ZeroBase(_i)];
}

template <typename _T, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ void Array<_T, _Mutex, _Allocator>::SetEntry(int _i, const _T& _entry)
{
#ifndef __NO_THREADS__
    Synchronization::Guard<_Mutex> guard(Mutex);
#endif
    //
    AssertRange(_i);
    Data[ZeroBase(_i)] = _entry;
}

template <typename _T, typename _Mutex, typename _Allocator>
void Array<_T, _Mutex, _Allocator>::AddEntry(const _T& _entry)
{
#ifndef __NO_THREADS__
    Synchronization::Guard<_Mutex> guard(Mutex);
#endif
    //
    Resize(Count+1);

    if(IsSorted())
    {
        uint i = Count-1;

        while(i > 0 && _entry < Data[i-1])
        {
            Data[i] = Data[i-1];
            --i;
        }
        
        Data[i] = _entry;
    }
    else
    {
        Data[Count-1] = _entry;
    }
}

template <typename _T, typename _Mutex, typename _Allocator>
void Array<_T, _Mutex, _Allocator>::RemoveEntry(int _i)
{
#ifndef __NO_THREADS__
    Synchronization::Guard<_Mutex> guard(Mutex);
#endif
    //
    AssertRange(_i);
    SetZero(_i, _i+1);
}

template <typename _T, typename _Mutex, typename _Allocator>
void Array<_T, _Mutex, _Allocator>::RemoveAllEntries()
{
#ifndef __NO_THREADS__
    Synchronization::Guard<_Mutex> guard(Mutex);
#endif
    //
    SetZero(0, Count);
}

template <typename _T, typename _Mutex, typename _Allocator>
void Array<_T, _Mutex, _Allocator>::Insert(const Array<_T, _Mutex, _Allocator>& _array, int _i)
{
#ifndef __NO_THREADS__
    Synchronization::Guard<_Mutex> guard(Mutex);
#endif
    //
    AssertRange(_i);

    uint count = Count+GetNextDelta(_array.GetCount(), GetDelta());

   _T* tmp = reinterpret_cast<_T*>(_Allocator::Allocate(sizeof(_T)*count));

    try
    {
        // phaze I
        for(uint i = 0; i < _i; i++)
        {
            tmp[i] = Data[i];
        }

        // phaze II
        for(; i < _array.GetCount(); i++)
        {
            tmp[i] = _array[i];
        }

        // phaze III
        for(; i < count; i++)
        {
            tmp[i] = Data[i];
        }
    }
    catch(...)
    {
       _Allocator::Deallocate(tmp);
        throw;
    }

    Destroy();
    //
    Data  = tmp;
    Count = count;
}
template <typename _T, typename _Mutex, typename _Allocator>
void Array<_T, _Mutex, _Allocator>::Insert(const _T& _entry, int _count, int _i)
{
#ifndef __NO_THREADS__
    Synchronization::Guard<_Mutex> guard(Mutex);
#endif
    //
    AssertRange(_i);

    uint count = Count+GetNextDelta(_count-Count, GetDelta());

   _T* tmp = reinterpret_cast<_T*>(_Allocator::Allocate(sizeof(_T)*count));

    try
    {
        // phaze I
        for(uint i = 0; i < _i; i++)
        {
            tmp[i] = Data[i];
        }

        // phaze II
        for(; i < _count; i++)
        {
            tmp[i] = _entry;
        }

        // phaze III
        for(; i < count; i++)
        {
            tmp[i] = Data[i];
        }
    }
    catch(...)
    {
        _Allocator::Deallocate(tmp);
        throw;
    }

    Destroy();
    //
    Data  = tmp;
    Count = count;
}

template <typename _T, typename _Mutex, typename _Allocator>
void Array<_T, _Mutex, _Allocator>::Swap(Array<_T, _Mutex, _Allocator>& _array)
{
    ail::Swap<ushort>(Flags, _array.Flags);
    ail::Swap<int>(LowerBound, _array.LowerBound);
    ail::Swap<uint>(Count, _array.Count);
    ail::Swap<ushort>(Delta, _array.Delta);
    ail::Swap<_T*>(Data, _array.Data);
}

template <typename _T, typename _Mutex, typename _Allocator>
void Array<_T, _Mutex, _Allocator>::Resize(uint _count)
{
    if(GetDelta() == 0)
    {
        throw XArray(XArray::FixedSize);
    }

    if(_count <= Count)
    {
        return;
    }

#ifndef __NO_THREADS__
    Synchronization::Guard<_Mutex> guard(Mutex);
#endif
    //
    uint count = Count+GetNextDelta(_count-Count, GetDelta());

   _T* tmp = reinterpret_cast<_T*>(_Allocator::Allocate(sizeof(_T)*count));

    try
    {
        for(uint i = 0; i < Count; i++)
        {
            tmp[i] = Data[i];
        }
    }
    catch(...)
    {
        _Allocator::Deallocate(tmp);
        throw;
    }

    uint c = Count;
    Destroy();
    //
    Data = tmp;
    SetZero(c, count-c);
    Count = count;
}

template <typename _T, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ void Array<_T, _Mutex, _Allocator>::Destroy()
{
#ifndef __NO_THREADS__
    Synchronization::Guard<_Mutex> guard(Mutex);
#endif
    //
    RemoveAllEntries();
   _Allocator::Deallocate(Data);
    //
    Data  = null,
    Count = 0;
}
//
template <typename _T, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ bool operator == (const Array<_T, _Allocator>& _array1, const Array<_T, _Allocator>& _array2)
{
    if(_array1.GetCount() != _array2.GetCount())
    {
        return false;
    }
    //
    for(uint i = 0; i < _array1.GetCount(); i++)
    {
        if(!(_array1[i] == _array2[i]))
        {
            return false;
        }
    }

    return true;
}

template <typename _T, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ void Array<_T, _Mutex, _Allocator>::AssertRange(int _i) const
{
#ifdef _DEBUG
    if(ZeroBase(_i) < ZeroBase(LowerBound) || ZeroBase(_i) >= ZeroBase(LowerBound)+Count)
    {
        throw XArray(XArray::OutOfRange);
    }
#endif
}

template <typename _T, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ ushort Array<_T, _Mutex, _Allocator>::GetNextDelta(uint _count, uint _delta) const
{
    return _delta == 0 ? _count : ((_count%_delta) ? ((_count+_delta)/_delta)*_delta : _count);
}

template <typename _T, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ uint Array<_T, _Mutex, _Allocator>::ZeroBase(int _i) const
{
    return _i-LowerBound;
}

template <typename _T, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ void Array<_T, _Mutex, _Allocator>::SetZero(uint _start, uint _count)
{
#ifndef __NO_THREADS__
    Synchronization::Guard<_Mutex> guard(Mutex);
#endif
    //
    if(IsInit())
    {
        for(uint i = _start; i < _count; i++)
        {
            memset(&Data[i], 0, sizeof(_T));
        }
    }
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __ARRAY_INL__
