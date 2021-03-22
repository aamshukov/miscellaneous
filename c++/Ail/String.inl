////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __STRING_INL__
#define __STRING_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
#define TEMPLATESIZE       16

#ifdef _UNICODE
#   define INTTEMPLATE     L"%ld"
#   define DOUBLETEMPLATE  L"%f"
#else
#   define INTTEMPLATE     "%ld"
#   define DOUBLETEMPLATEA  "%f"
#endif
//
extern const ushort ConstTemplateSize;
extern const char*  ConstIntTemplateA;
extern const wchar* ConstIntTemplateW;
extern const char*  ConstDoubleTemplateA;
extern const wchar* ConstDoubleTemplateW;
////////////////////////////////////////////////////////////////////////////////////////
// class CharTraits
// ----- ----------
__INLINE__ uint CharTraits::StrLen(const tchar* _s)
{
    return ail::StrLen(_s);
}

__INLINE__ tchar* CharTraits::StrCopy(tchar* _dst, const tchar* _src)
{
    return ail::StrCopy(_dst, _src);
}

__INLINE__ tchar* CharTraits::StrSubstr(const tchar* _s, const tchar* _sub_str)
{
    return ail::StrSubstr(_s, _sub_str);
}

__INLINE__ int CharTraits::StrColl(const tchar* _s1, const tchar* _s2)
{
    return ail::StrColl(_s1, _s2);
}

__INLINE__ int CharTraits::StrIColl(const tchar* _s1, const tchar* _s2)
{
    return ail::StrIColl(_s1, _s2);
}

__INLINE__ int CharTraits::StrNColl(const tchar* _s1, const tchar* _s2, size_t _count)
{
    return ail::StrNColl(_s1, _s2, _count);
}

__INLINE__ int CharTraits::StrNIColl(const tchar* _s1, const tchar* _s2, size_t _count)
{
    return ail::StrNIColl(_s1, _s2, _count);
}

__INLINE__ int CharTraits::StrCompare(const tchar* _s1, const tchar* _s2)
{
    return ail::StrCompare(_s1, _s2);
}

__INLINE__ int CharTraits::StrICompare(const tchar* _s1, const tchar* _s2)
{
    return ail::StrICompare(_s1, _s2);
}

__INLINE__ int CharTraits::StrNCompare(const tchar* _s1, const tchar* _s2, size_t _count)
{
    return ail::StrNCompare(_s1, _s2, _count);
}

__INLINE__ int CharTraits::StrNICompare(const tchar* _s1, const tchar* _s2, size_t _count)
{
    return ail::StrNICompare(_s1, _s2, _count);
}

__INLINE__ tchar* CharTraits::StrUpper(tchar* _s)
{
    return ail::StrUpper(_s);
}

__INLINE__ tchar* CharTraits::StrLower(tchar* _s)
{
    return ail::StrLower(_s);
}

__INLINE__ int CharTraits::Format(tchar* _buffer, const tchar* _template, va_list& _arg)
{
    return _vstprintf(_buffer, _template, _arg);
}
////////////////////////////////////////////////////////////////////////////////////////
// class UniTraits
// ----- ---------
__INLINE__ uint UniTraits::StrLen(const wchar* _s)
{
    return ail::StrLenW(_s);
}

__INLINE__ wchar* UniTraits::StrCopy(wchar* _dst, const wchar* _src)
{
    return ail::StrCopyW(_dst, _src);
}

__INLINE__ wchar* UniTraits::StrSubstr(const wchar* _s, const wchar* _sub_str)
{
    return ail::StrSubstrW(_s, _sub_str);
}

__INLINE__ int UniTraits::StrColl(const wchar* _s1, const wchar* _s2)
{
    return ail::StrCollW(_s1, _s2);
}

__INLINE__ int UniTraits::StrIColl(const wchar* _s1, const wchar* _s2)
{
    return ail::StrICollW(_s1, _s2);
}

__INLINE__ int UniTraits::StrNColl(const wchar* _s1, const wchar* _s2, size_t _count)
{
    return ail::StrNCollW(_s1, _s2, _count);
}

__INLINE__ int UniTraits::StrNIColl(const wchar* _s1, const wchar* _s2, size_t _count)
{
    return ail::StrNICollW(_s1, _s2, _count);
}

__INLINE__ int UniTraits::StrCompare(const wchar* _s1, const wchar* _s2)
{
    return ail::StrCompareW(_s1, _s2);
}

__INLINE__ int UniTraits::StrICompare(const wchar* _s1, const wchar* _s2)
{
    return ail::StrICompareW(_s1, _s2);
}

__INLINE__ int UniTraits::StrNCompare(const wchar* _s1, const wchar* _s2, size_t _count)
{
    return ail::StrNCompareW(_s1, _s2, _count);
}

__INLINE__ int UniTraits::StrNICompare(const wchar* _s1, const wchar* _s2, size_t _count)
{
    return ail::StrNICompareW(_s1, _s2, _count);
}

__INLINE__ wchar* UniTraits::StrUpper(wchar* _s)
{
    return ail::StrUpperW(_s);
}

__INLINE__ wchar* UniTraits::StrLower(wchar* _s)
{
    return ail::StrLowerW(_s);
}

__INLINE__ int UniTraits::Format(wchar* _buffer, const wchar* _template, va_list& _arg)
{
    return vswprintf(_buffer, _template, _arg);
}
////////////////////////////////////////////////////////////////////////////////////////
// class StrRef
// ----- ------
template <typename _T, typename _Traits, typename _Allocator>
StrRef<_T, _Traits, _Allocator>::StrRef() : Data(null), Count(0)
{
    Reference = 1;
    Data = static_cast<_T*>(_Allocator::Allocate(RoundCapacity(0))), Data[Count] = 0;
}

template <typename _T, typename _Traits, typename _Allocator>
StrRef<_T, _Traits, _Allocator>::StrRef(const StrRef<_T, _Traits, _Allocator>& _other)
{
    operator = (_other);
}

template <typename _T, typename _Traits, typename _Allocator>
StrRef<_T, _Traits, _Allocator>::StrRef(_T _ch, uint _count) : Data(null), Count(_count)
{
    Reference = 1;
    Data = static_cast<_T*>(_Allocator::Allocate(RoundCapacity(0))), Data[Count] = 0;
    String<_T, _Traits, _Allocator>::MemSet(Data, Count, _ch*sizeof(_T));
}

template <typename _T, typename _Traits, typename _Allocator>
StrRef<_T, _Traits, _Allocator>::StrRef(const _T* _string, uint _begin, uint _extent) : Data(null), Count(0)
{
    Reference = 1;
    Count = _extent != -1 ? _extent : _Traits::StrLen(_string+_begin);
    Data  = static_cast<_T*>(_Allocator::Allocate(RoundCapacity(Count))), Data[Count] = 0;
    String<_T, _Traits, _Allocator>::MemMove(Data, _string+_begin, Count*sizeof(_T));
}

template <typename _T, typename _Traits, typename _Allocator>
StrRef<_T, _Traits, _Allocator>::~StrRef()
{
    Release();
}

template <typename _T, typename _Traits, typename _Allocator>
const StrRef<_T, _Traits, _Allocator>& StrRef<_T, _Traits, _Allocator>::operator = (const StrRef<_T, _Traits, _Allocator>& _other)
{
    if(this != &_other)
    {
        Reference = 1;
        Count     = _other.Count;
        Data      = static_cast<_T*>(_Allocator::Allocate(RoundCapacity(Count))), Data[Count] = 0;
        //
        String<_T, _Traits, _Allocator>::MemMove(Data, _other.Data, Count*sizeof(_T));
    }
    return *this;
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ _T* StrRef<_T, _Traits, _Allocator>::GetData() const
{
    // for internal use only ! ...
    return Data;
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ uint StrRef<_T, _Traits, _Allocator>::GetCount() const
{
    return Count;
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ uint StrRef<_T, _Traits, _Allocator>::RoundCapacity(uint _count) const
{
    //
    const ushort _delta_ = 16;
    //
   _count += 1;  // +1 for '0'
    return sizeof(_T)*((_count/_delta_)*_delta_+(_count%_delta_ ? _delta_ : 0));
}

template <typename _T, typename _Traits, typename _Allocator>
void StrRef<_T, _Traits, _Allocator>::Assign(const _T* _string, uint _count)
{
    Resize(_count);

    if(Data != null)
    {
        if(_string != null)
        {
            String<_T, _Traits, _Allocator>::MemMove(Data, _string, _count*sizeof(_T));
        }
        else
        {
            String<_T, _Traits, _Allocator>::MemSet(Data, _count*sizeof(_T));
        }

        Data[Count = _count] = 0;
    }
}

template <typename _T, typename _Traits, typename _Allocator>
void StrRef<_T, _Traits, _Allocator>::Append(const _T* _string, uint _count)
{
    uint l = Count;

    Resize(Count+_count);

    if(Data != null)
    {
        if(_string != null)
        {
            String<_T, _Traits, _Allocator>::MemMove(Data+l, _string, _count*sizeof(_T));
        }
        else
        {
            String<_T, _Traits, _Allocator>::MemSet(Data+l, _count*sizeof(_T));
        }

        Data[Count += _count] = 0;
    }
}

template <typename _T, typename _Traits, typename _Allocator>
void StrRef<_T, _Traits, _Allocator>::Insert(uint _pos, const _T* _string, uint _count, bool _use_set)
{
    if(Count == 0)
    {
        Assign(_string, _count);
    }
    else if(_pos < Count)
    {
        uint count2 = Count;

        Resize(Count+_count);

        if(Data != null)
        {
            // split ! ...
            String<_T, _Traits, _Allocator>::MemMove(Data+_pos+_count, Data+_pos, (count2-_pos)*sizeof(_T));

            // insert ! ...
            if(_use_set && _string != null)
            {
                String<_T, _Traits, _Allocator>::MemSet(Data+_pos, _count*sizeof(_T), *_string);
            }
            else
            {
                if(_string != null)
                {
                    String<_T, _Traits, _Allocator>::MemMove(Data+_pos, _string, _count);
                }
                else
                {
                    String<_T, _Traits, _Allocator>::MemSet(Data+_pos, _count*sizeof(_T));
                }
            }

            Data[Count] = 0;
        }
    }
    else
    {
        Append(_string, _count);
    }
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ void StrRef<_T, _Traits, _Allocator>::TrimSpace(ushort _level)
{
    ail::TrimSpace(Data, _level);
    Count = _Traits::StrLen(Data);
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ void StrRef<_T, _Traits, _Allocator>::Remove(uint _pos, uint _count)
{
    if(_pos < Count && Data)
    {
        uint count2 = _count > Count-_pos ? Count-_pos : _count;
        String<_T, _Traits, _Allocator>::MemMove(Data+_pos, Data+_pos+count2, (Count-_pos-count2)*sizeof(_T));
        Data[Count = count2] = 0;
    }
}

template <typename _T, typename _Traits, typename _Allocator>
void StrRef<_T, _Traits, _Allocator>::Resize(uint _count)
{
    uint capacity  = RoundCapacity(_count);
    uint capacity2 = RoundCapacity(Count);
    bool grow      = _count > Count;

    bool condition = grow ? (capacity > capacity2) : (capacity2 < capacity2);

    if(condition)
    {
       _T* data = static_cast<_T*>(_Allocator::Allocate(capacity));
        String<_T, _Traits, _Allocator>::MemMove(data, Data, (grow ? Count : _count)*sizeof(_T));

        if(Data != null)
        {
            _Allocator::Deallocate(Data);
        }

        Data = data;
    }

    if(_count < Count)
    {
        Data[Count = _count] = 0;
    }
    else if(condition)
    {
        Data[Count] = 0;
    }
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ void StrRef<_T, _Traits, _Allocator>::Reserve(uint _count)
{
    Resize(_count);
}

template <typename _T, typename _Traits, typename _Allocator>
void StrRef<_T, _Traits, _Allocator>::Release()
{
    if(Data != null)
    {
        // do not change Reference ! ...
        _Allocator::Deallocate(Data), Data = null, Count = 0;
    }
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ void StrRef<_T, _Traits, _Allocator>::FreeExtraMemory()
{
    if(Data != null)
    {
        Resize(_Traits::StrLen(Data));
    }
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ uint StrRef<_T, _Traits, _Allocator>::AddReference()
{
    return ++Reference;
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ uint StrRef<_T, _Traits, _Allocator>::ReleaseReference()
{
    return --Reference;
}
////////////////////////////////////////////////////////////////////////////////////////
// class String
// ----- ------
template <typename _T, typename _Traits, typename _Allocator>
String<_T, _Traits, _Allocator>::String()
{
    try
    {
        Flags = String<_T, _Traits, _Allocator>::None;
        void* p = static_cast<_T*>(_Allocator::Allocate(sizeof(StrRef<_T, _Traits, _Allocator>)));
        Ref = new (p) StrRef<_T, _Traits, _Allocator>();
    }
    catch(...)
    {
        throw XString();
    }
}

template <typename _T, typename _Traits, typename _Allocator>
String<_T, _Traits, _Allocator>::String(const String<_T, _Traits, _Allocator>& _other)
{
    try
    {
        if(this != &_other)
        {
            Flags = _other.Flags;
            Ref   = _other.Ref;

            if(Ref != null)
            {
                Ref->AddReference();
            }
        }
    }
    catch(...)
    {
        throw XString();
    }
}

template <typename _T, typename _Traits, typename _Allocator>
String<_T, _Traits, _Allocator>::String(_T _ch, uint _count, uint _flags) : Flags(_flags)
{
    try
    {
        // _ch != _istlead
        void* p = static_cast<_T*>(_Allocator::Allocate(sizeof(StrRef<_T, _Traits, _Allocator>)));
        Ref = new (p) StrRef<_T, _Traits, _Allocator>(_ch, _count);
    }
    catch(...)
    {
        throw XString();
    }
}

template <typename _T, typename _Traits, typename _Allocator>
String<_T, _Traits, _Allocator>::String(int _number, uint _flags) : Flags(_flags)
{
    try
    {
       _T buffer[TEMPLATESIZE];
        compose(buffer, INTTEMPLATE, _number);
        void* p = static_cast<_T*>(_Allocator::Allocate(sizeof(StrRef<_T, _Traits, _Allocator>)));
        Ref = new (p) StrRef<_T, _Traits, _Allocator>(_buffer);
    }
    catch(...)
    {
        throw XString();
    }
}

template <typename _T, typename _Traits, typename _Allocator>
String<_T, _Traits, _Allocator>::String(double _number, const _T* _template, uint _flags) : Flags(_flags)
{
    try
    {
       _T buffer[TEMPLATESIZE];
        compose(buffer, _template != null ? _template : DOUBLETEMPLATE, _number);
        void* p = static_cast<_T*>(_Allocator::Allocate(sizeof(StrRef<_T, _Traits, _Allocator>)));
        Ref = new (p) StrRef<_T, _Traits, _Allocator>(_buffer);
    }
    catch(...)
    {
        throw XString();
    }
}

template <typename _T, typename _Traits, typename _Allocator>
String<_T, _Traits, _Allocator>::String(const _T* _string, uint _begin, uint _extent, uint _flags) : Flags(_flags)
{
    try
    {
        if(_string != null)
        {
            // correct extent
            _extent = _extent != -1 ? _extent : _Traits::StrLen(_string+_begin);

            if(_begin+_extent > static_cast<uint>(_Traits::StrLen(_string)))
            {
                throw XString(X::OutOfRange);
            }

            void* p = static_cast<_T*>(_Allocator::Allocate(sizeof(StrRef<_T, _Traits, _Allocator>)));
            Ref = new (p) StrRef<_T, _Traits, _Allocator>(_string, _begin, _extent);
        }
        else
        {
            void* p = static_cast<_T*>(_Allocator::Allocate(sizeof(StrRef<_T, _Traits, _Allocator>)));
            Ref = new (p) StrRef<_T, _Traits, _Allocator>();
        }
    }
    catch(...)
    {
        throw XString();
    }
}

template <typename _T, typename _Traits, typename _Allocator>
String<_T, _Traits, _Allocator>::String(HINSTANCE _hmodule, uint _id, uint _flags)
{
    try
    {
        Flags = _flags|String<_T, _Traits, _Allocator>::FromResource;
        //
        const ushort _count_ = 4096;
        AutoPtrArray<_T> buffer = new _T[_count_];
        //
        if(!StringFromResource(buffer, _count_, _id, _hmodule))
        {
            throw XString();
        }

        void* p = static_cast<_T*>(_Allocator::Allocate(sizeof(StrRef<_T, _Traits, _Allocator>)));
        Ref = new (p) StrRef<_T, _Traits, _Allocator>(buffer, _begin, _extent);
    }
    catch(...)
    {
        throw XString();
    }
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ String<_T, _Traits, _Allocator>::~String()
{
    try
    {
        if(Ref != null)
        {
            if(Ref->ReleaseReference() == 0)
            {
                _Allocator::Deallocate(Ref);
            }
            Ref = null;
        }
    }
    catch(...)
    {
    }
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ const String<_T, _Traits, _Allocator>& String<_T, _Traits, _Allocator>::operator = (_T _ch)
{
    return Assign(_ch);
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ const String<_T, _Traits, _Allocator>& String<_T, _Traits, _Allocator>::operator = (int _number)
{
    return Assign(_number);
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ const String<_T, _Traits, _Allocator>& String<_T, _Traits, _Allocator>::operator = (double _number)
{
    return Assign(_number);
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ const String<_T, _Traits, _Allocator>& String<_T, _Traits, _Allocator>::operator = (const _T* _string)
{
    return Assign(_string);
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ const String<_T, _Traits, _Allocator>& String<_T, _Traits, _Allocator>::operator = (const String<_T, _Traits, _Allocator>& _string)
{
    return Assign(_string);
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ const String<_T, _Traits, _Allocator>& String<_T, _Traits, _Allocator>::operator += (_T _ch)
{
    return Append(_ch);
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ const String<_T, _Traits, _Allocator>& String<_T, _Traits, _Allocator>::operator += (int _number)
{
    return Append(_number);
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ const String<_T, _Traits, _Allocator>& String<_T, _Traits, _Allocator>::operator += (double _number)
{
    return Append(_number);
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ const String<_T, _Traits, _Allocator>& String<_T, _Traits, _Allocator>::operator += (const _T* _string)
{
    return Append(_string);
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ const String<_T, _Traits, _Allocator>& String<_T, _Traits, _Allocator>::operator += (const String<_T, _Traits, _Allocator>& _string)
{
    return Append(_string);
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ const _T& String<_T, _Traits, _Allocator>::operator [] (uint _index)
{
    AssertIndex(_index);
    return GetAt(_index);
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ String<_T, _Traits, _Allocator>::operator const _T* () const
{
    return reinterpret_cast<const _T*>(Ref->GetData());
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ String<_T, _Traits, _Allocator>::operator _T* ()
{
    return Ref->GetData();
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ uint String<_T, _Traits, _Allocator>::GetFlags() const
{
    return Flags;
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ void String<_T, _Traits, _Allocator>::SetFlags(uint _remove, uint _add)
{
    Flags = (Flags & ~_remove) | _add;
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ const _T* String<_T, _Traits, _Allocator>::GetData() const
{
    return reinterpret_cast<const _T*>(Ref->GetData());
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ uint String<_T, _Traits, _Allocator>::GetCount() const
{
    return Ref->GetCount();
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ uint String<_T, _Traits, _Allocator>::GetCapacity() const
{
    return Ref->RoundCapacity(Ref->GetCount());
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ uint String<_T, _Traits, _Allocator>::GetHashValue() const
{
    return HashPJW(reinterpret_cast<const byte*>(Ref->GetData()));
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ bool String<_T, _Traits, _Allocator>::IsEmpty() const
{
    return Ref->GetCount() == 0;
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ void String<_T, _Traits, _Allocator>::SetEmpty()
{
    AssertFlag(String<_T, _Traits, _Allocator>::ReadOnly);
    COW();
    Ref->Resize(0);
    //
  *(Ref->GetData()) = 0;
    Ref->Count      = 0;
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ const _T& String<_T, _Traits, _Allocator>::GetAt(uint _index) const
{
    AssertIndex(_index);
    return *(Ref->GetData()+_index);
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ void String<_T, _Traits, _Allocator>::SetAt(uint _index, const _T& _ch)
{
    AssertFlag(String<_T, _Traits, _Allocator>::ReadOnly);
    AssertIndex(_index);
    COW();
    //
    *(Ref->GetData()+_index) = _ch;
}

template <typename _T, typename _Traits, typename _Allocator>
String<_T, _Traits, _Allocator> String<_T, _Traits, _Allocator>::GetFirstTerm(_T** _p_curr, _T _delimiter) const
{
    String<_T, _Traits, _Allocator> str;

    _T* p = Ref->GetData();

    if(p != null && *p != 0)
    {
        while(*p != 0 && *p == _delimiter)
        {
            ++p;
        }

        while(*p != 0 && *p != _delimiter)
        {
            str += *p++;
        }

        while(*p != 0 && *p == _delimiter)
        {
            ++p;
        }

        *_p_curr = p;
    }

    return str;
}

template <typename _T, typename _Traits, typename _Allocator>
String<_T, _Traits, _Allocator> String<_T, _Traits, _Allocator>::GetNextTerm(_T** _p_curr, _T _delimiter) const
{
    String<_T, _Traits, _Allocator> str;

    _T* p = *_p_curr ? *_p_curr : Ref->GetData();

    if(p != null && *p != 0)
    {
        while(*p != 0 && *p == _delimiter)
        {
            ++p;
        }

        while(*p != 0 && *p != _delimiter)
        {
            str += *p++;
        }

        while(*p != 0 && *p == _delimiter)
        {
            ++p;
        }

        *_p_curr = p;
    }

    return str;
}

template <typename _T, typename _Traits, typename _Allocator>
String<_T, _Traits, _Allocator> String<_T, _Traits, _Allocator>::GetPrevTerm(_T** _p_curr, _T _delimiter) const
{
    String<_T, _Traits, _Allocator> str;

    _T* p = *_p_curr;

    if(p == null)
    {
        return GetFirstTerm(_p_curr, _delimiter);
    }
    else
    {
        while(p != Ref->GetData() && *p == _delimiter)
        {
            --p;
        }

        while(p != Ref->GetData() && *p != _delimiter)
        {
            --p;
        }

        ++p;

        while(*p != 0 && *p != _delimiter)
        {
            str += *p++;
        }
    }

    return str;
}

template <typename _T, typename _Traits, typename _Allocator>
String<_T, _Traits, _Allocator> String<_T, _Traits, _Allocator>::GetLastTerm(_T** _p_curr, _T _delimiter) const
{
    String<_T, _Traits, _Allocator> str;

    _T* p = Ref->GetData();

    if(p != null && *p != 0)
    {
        p += Ref->GetCount()-1;

        while(p != Ref->GetData() && *p == _delimiter)
        {
            --p;
        }

        while(p != Ref->GetData() && *p != _delimiter)
        {
            --p;
        }

        ++p;

        while(*p && *p != _delimiter)
        {
            str += *p++;
        }
    }

    return str;
}

template <typename _T, typename _Traits, typename _Allocator>
String<_T, _Traits, _Allocator> String<_T, _Traits, _Allocator>::GetLeftPart(uint _count) const
{
    String<_T, _Traits, _Allocator> str;

    if(_count > Ref->GetCount())
    {
        _count = Ref->GetCount();
    }

    for(uint i = 0; i < _count; i++)
    {
        str += GetAt(i);
    }

    return str;
}

template <typename _T, typename _Traits, typename _Allocator>
String<_T, _Traits, _Allocator> String<_T, _Traits, _Allocator>::GetMidPart(uint _begin) const
{
    return GetMidPart(_begin, Ref->GetCount()-_begin);
}

template <typename _T, typename _Traits, typename _Allocator>
String<_T, _Traits, _Allocator> String<_T, _Traits, _Allocator>::GetMidPart(uint _begin, uint _count) const
{
    String<_T, _Traits, _Allocator> str;

    if(_begin+_count > Ref->GetCount())
    {
        _count = Ref->GetCount()-_begin;
    }

    if(_begin > Ref->GetCount())
    {
        _count = 0;
    }

    for(uint i = _begin; i < _count; i++)
    {
        str += GetAt(i);
    }

    return str;
}

template <typename _T, typename _Traits, typename _Allocator>
String<_T, _Traits, _Allocator> String<_T, _Traits, _Allocator>::GetRightPart(uint _count) const
{
    String<_T, _Traits, _Allocator> str;

    if(_count > Ref->GetCount())
    {
        _count = Ref->GetCount();
    }

    for(uint i = Ref->GetCount()-_count; i < Ref->GetCount(); i++)
    {
        str += GetAt(i);
    }

    return str;
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ String<_T, _Traits, _Allocator> String<_T, _Traits, _Allocator>::SpanIncluding(const _T* _string) const
{
    return GetLeftPart(StrSpan(Ref->GetData(), _string));
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ String<_T, _Traits, _Allocator> String<_T, _Traits, _Allocator>::SpanExcluding(const _T* _string) const
{
    return GetLeftPart(StrCSpan(Ref->GetData(), _string));
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ bool String<_T, _Traits, _Allocator>::Contains(_T _ch) const
{
    return Find(_ch) != -1;
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ bool String<_T, _Traits, _Allocator>::Contains(int _number) const
{
    return Find(_number) != -1;
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ bool String<_T, _Traits, _Allocator>::Contains(double _number, const _T* _format) const
{
    return Find(_number, _format) != -1;
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ bool String<_T, _Traits, _Allocator>::Contains(const _T* _sample) const
{
    return Find(_sample) != -1;
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ bool String<_T, _Traits, _Allocator>::Contains(const String<_T, _Traits, _Allocator>& _sample)
{
    return Find(_sample) != -1;
}

template <typename _T, typename _Traits, typename _Allocator>
uint String<_T, _Traits, _Allocator>::Find(_T _ch, uint _count) const
{
   _T* p = StrChar(Ref->GetData(), _ch);
    uint n = 0;

    while(p != null && n < _count)
    {
        p = StrChar(p+1, _ch), --n;
    }
    return p == null ? -1 : p-Ref->GetData();
}

template <typename _T, typename _Traits, typename _Allocator>
uint String<_T, _Traits, _Allocator>::Find(int _number, uint _count) const
{
   _T> buffer[TEMPLATESIZE];
    compose(buffer, INTTEMPLATE, _number);
    return FindInternal(buffer, _count);
}

template <typename _T, typename _Traits, typename _Allocator>
uint String<_T, _Traits, _Allocator>::Find(double _number, const _T* _template, uint _count) const
{
   _T buffer[TEMPLATESIZE];
    compose(buffer, _template != null ? _template : DOUBLETEMPLATE, _number);
    return FindInternal(buffer, _count);
}

template <typename _T, typename _Traits, typename _Allocator>
uint String<_T, _Traits, _Allocator>::Find(const _T* _sample, uint _count) const
{
    return FindInternal(_sample, _count);
}

template <typename _T, typename _Traits, typename _Allocator>
uint String<_T, _Traits, _Allocator>::Find(const String<_T, _Traits, _Allocator>& _sample, uint _count) const
{
    return FindInternal(_sample.Ref->GetData(), _count);
}

template <typename _T, typename _Traits, typename _Allocator>
uint String<_T, _Traits, _Allocator>::ReverseFind(_T _ch, uint _count) const
{
   _T* p  = Ref->GetData();
   _T* p2 = Ref->GetData()+Ref->GetCount();

    uint n = 0;

    while(p < p2--)
    {
        if(*p2 == _ch && n++ >= _count)
        {
            return p2-Ref->GetData();
        }
    }

    return -1;
}

template <typename _T, typename _Traits, typename _Allocator>
uint String<_T, _Traits, _Allocator>::ReverseFind(int _number, uint _count) const
{
   _T buffer[TEMPLATESIZE];
    compose(buffer, INTTEMPLATE, _number);
    return ReverseFindInternal(buffer, _count);
}

template <typename _T, typename _Traits, typename _Allocator>
uint String<_T, _Traits, _Allocator>::ReverseFind(double _number, const _T* _template, uint _count) const
{
   _T buffer[TEMPLATESIZE];
    compose(buffer, _template != null ? _template : DOUBLETEMPLATE, _number);
    return ReverseFindInternal(buffer, _count);
}

template <typename _T, typename _Traits, typename _Allocator>
uint String<_T, _Traits, _Allocator>::ReverseFind(const _T* _sample, uint _count) const
{
    return ReverseFindInternal(_sample, _count);
}

template <typename _T, typename _Traits, typename _Allocator>
uint String<_T, _Traits, _Allocator>::ReverseFind(const String<_T, _Traits, _Allocator>& _sample, uint _count) const
{
    return ReverseFindInternal(_sample.Ref->GetData(), _count);
}

template <typename _T, typename _Traits, typename _Allocator>
uint String<_T, _Traits, _Allocator>::FindOneOf(const _T* _sample) const
{
   _T* p = String<_T, _Traits, _Allocator>::Strpbrk(Ref->GetData(), _sample);
    return p == null ? -1 : p-Ref->GetData();
}

template <typename _T, typename _Traits, typename _Allocator>
short String<_T, _Traits, _Allocator>::Compare(_T _ch) const
{
    if(Flags & String<_T, _Traits, _Allocator>::CaseSensitive)
    {
        if(Flags & String<_T, _Traits, _Allocator>::NLS)
        {
            return String<_T, _Traits, _Allocator>::StrNColl(Ref->GetData(), reinterpret_cast<_T*>(&_ch), 1);
        }
        else
        {
            return String<_T, _Traits, _Allocator>::StrNCompare(Ref->GetData(), reinterpret_cast<_T*>(&_ch), 1);
        }
    }
    else
    {
        if(Flags & String<_T, _Traits, _Allocator>::NLS)
        {
            return String<_T, _Traits, _Allocator>::StrNIColl(Ref->GetData(), reinterpret_cast<_T*>(&_ch), 1);
        }
        else
        {
            return String<_T, _Traits, _Allocator>::StrNICompare(Ref->GetData(), reinterpret_cast<_T*>(&_ch), 1);
        }
    }
}

template <typename _T, typename _Traits, typename _Allocator>
short String<_T, _Traits, _Allocator>::Compare(int _number) const
{
   _T buffer[TEMPLATESIZE];
    compose(buffer, INTTEMPLATE, _number);
    return CompareInternal(buffer);
}

template <typename _T, typename _Traits, typename _Allocator>
short String<_T, _Traits, _Allocator>::Compare(double _number, const _T* _template) const
{
   _T buffer[TEMPLATESIZE];
    compose(buffer, _template != null ? _template : DOUBLETEMPLATE, _number);
    return CompareInternal(buffer);
}

template <typename _T, typename _Traits, typename _Allocator>
short String<_T, _Traits, _Allocator>::Compare(const _T* _sample) const
{
    return CompareInternal(_sample);
}

template <typename _T, typename _Traits, typename _Allocator>
short String<_T, _Traits, _Allocator>::Compare(const String<_T, _Traits, _Allocator>& _sample) const
{
    return CompareInternal(_sample.Ref->GetData());
}

template <typename _T, typename _Traits, typename _Allocator>
const String<_T, _Traits, _Allocator>& String<_T, _Traits, _Allocator>::Assign(_T _ch)
{
    AssertFlag(String<_T, _Traits, _Allocator>::ReadOnly);
    COW();
    Ref->Assign(reinterpret_cast<const _T*>(&_ch), 1);
    FreeExtraMemory();
    return *this;
}

template <typename _T, typename _Traits, typename _Allocator>
const String<_T, _Traits, _Allocator>& String<_T, _Traits, _Allocator>::Assign(int _number)
{
    AssertFlag(String<_T, _Traits, _Allocator>::ReadOnly);
    COW();
   _T buffer[TEMPLATESIZE];
    compose(buffer, INTTEMPLATE, _number);
    Ref->Assign(buffer, _Traits::StrLen(buffer));
    FreeExtraMemory();
    return *this;
}

template <typename _T, typename _Traits, typename _Allocator>
const String<_T, _Traits, _Allocator>& String<_T, _Traits, _Allocator>::Assign(double _number, const _T* _template)
{
    AssertFlag(String<_T, _Traits, _Allocator>::ReadOnly);
    COW();
   _T buffer[TEMPLATESIZE];
    compose(buffer, _template != null ? _template : DOUBLETEMPLATE, _number);
    Ref->Assign(buffer, _Traits::StrLen(buffer));
    FreeExtraMemory();
    return *this;
}

template <typename _T, typename _Traits, typename _Allocator>
const String<_T, _Traits, _Allocator>& String<_T, _Traits, _Allocator>::Assign(const _T* _string)
{
    AssertFlag(String<_T, _Traits, _Allocator>::ReadOnly);
    COW();
    Ref->Assign(_string, _Traits::StrLen(_string));
    FreeExtraMemory();
    return *this;
}

template <typename _T, typename _Traits, typename _Allocator>
const String<_T, _Traits, _Allocator>& String<_T, _Traits, _Allocator>::Assign(const String<_T, _Traits, _Allocator>& _other)
{
    AssertFlag(String<_T, _Traits, _Allocator>::ReadOnly);

    if(this != &_other)
    {
        Flags = _other.Flags;
        Ref   = _other.Ref;

        if(Ref)
        {
            Ref->AddReference();
        }
    }

    FreeExtraMemory();
    return *this;
}

template <typename _T, typename _Traits, typename _Allocator>
const String<_T, _Traits, _Allocator>& String<_T, _Traits, _Allocator>::Append(_T _ch)
{
    AssertFlag(String<_T, _Traits, _Allocator>::ReadOnly);
    COW();
    Ref->Append(reinterpret_cast<const _T*>(&_ch), 1);
    FreeExtraMemory();
    return *this;
}

template <typename _T, typename _Traits, typename _Allocator>
const String<_T, _Traits, _Allocator>& String<_T, _Traits, _Allocator>::Append(int _number)
{
    AssertFlag(String<_T, _Traits, _Allocator>::ReadOnly);
   _T buffer[TEMPLATESIZE];
    compose(buffer, INTTEMPLATE, _number);
    COW();
    Ref->Append(buffer, _Traits::StrLen(buffer));
    FreeExtraMemory();
    return *this;
}

template <typename _T, typename _Traits, typename _Allocator>
const String<_T, _Traits, _Allocator>& String<_T, _Traits, _Allocator>::Append(double _number, const _T* _template)
{
    AssertFlag(String<_T, _Traits, _Allocator>::ReadOnly);
   _T buffer[TEMPLATESIZE];
    compose(buffer, _template != null ? _template : DOUBLETEMPLATE, _number);
    COW();
    Ref->Append(buffer, _Traits::StrLen(buffer));
    FreeExtraMemory();
    return *this;
}

template <typename _T, typename _Traits, typename _Allocator>
const String<_T, _Traits, _Allocator>& String<_T, _Traits, _Allocator>::Append(const _T* _string, uint _orig, uint _count)
{
    AssertFlag(String<_T, _Traits, _Allocator>::ReadOnly);

    if(_string)
    {
        COW();
        Ref->Append(_string+_orig, _count == -1 ? _Traits::StrLen(_string) : _count);
    }

    FreeExtraMemory();
    return *this;
}

template <typename _T, typename _Traits, typename _Allocator>
const String<_T, _Traits, _Allocator>& String<_T, _Traits, _Allocator>::Append(const String<_T, _Traits, _Allocator>& _string, uint _orig, uint _count)
{
    AssertFlag(String<_T, _Traits, _Allocator>::ReadOnly);
    COW();
    Ref->Append(_string.Ref->GetData()+_orig, _count == -1 ? _string.GetCount() : _count);
    FreeExtraMemory();
    return *this;
}

template <typename _T, typename _Traits, typename _Allocator>
const String<_T, _Traits, _Allocator>& String<_T, _Traits, _Allocator>::Insert(uint _pos, _T _ch, uint _count)
{
    AssertFlag(String<_T, _Traits, _Allocator>::ReadOnly);
    COW();
    Ref->Insert(_pos, reinterpret_cast<const _T*>(&_ch), _count, true);
    FreeExtraMemory();
    return *this;
}

template <typename _T, typename _Traits, typename _Allocator>
const String<_T, _Traits, _Allocator>& String<_T, _Traits, _Allocator>::Insert(uint _pos, int _number)
{
    AssertFlag(String<_T, _Traits, _Allocator>::ReadOnly);
   _T buffer[TEMPLATESIZE];
    compose(buffer, INTTEMPLATE, _number);
    COW();
    Ref->Insert(_pos, buffer, _Traits::StrLen(buffer));
    FreeExtraMemory();
    return *this;
}

template <typename _T, typename _Traits, typename _Allocator>
const String<_T, _Traits, _Allocator>& String<_T, _Traits, _Allocator>::Insert(uint _pos, double _number, const _T* _template)
{
    AssertFlag(String<_T, _Traits, _Allocator>::ReadOnly);
   _T buffer[TEMPLATESIZE];
    compose(buffer, _template != null ? _template : DOUBLETEMPLATE, _number);
    COW();
    Ref->Insert(_pos, buffer, _Traits::StrLen(buffer));
    FreeExtraMemory();
    return *this;
}

template <typename _T, typename _Traits, typename _Allocator>
const String<_T, _Traits, _Allocator>& String<_T, _Traits, _Allocator>::Insert(uint _pos, const _T* _string, uint _orig, uint _count)
{
    AssertFlag(String<_T, _Traits, _Allocator>::ReadOnly);
    COW();
    Ref->Insert(_pos, _string+_orig, _count == -1 ? _Traits::StrLen(_string) : _count);
    FreeExtraMemory();
    return *this;
}

template <typename _T, typename _Traits, typename _Allocator>
const String<_T, _Traits, _Allocator>& String<_T, _Traits, _Allocator>::Insert(uint _pos, const String<_T, _Traits, _Allocator>& _string, uint _orig, uint _count)
{
    AssertFlag(String<_T, _Traits, _Allocator>::ReadOnly);
    COW();
    Ref->Insert(_pos, _string.Ref->GetData()+_orig, _count == -1 ? _string.GetCount() : _count);
    FreeExtraMemory();
    return *this;
}

template <typename _T, typename _Traits, typename _Allocator>
const String<_T, _Traits, _Allocator>& String<_T, _Traits, _Allocator>::Remove(uint _pos, uint _count)
{
    AssertFlag(String<_T, _Traits, _Allocator>::ReadOnly);
    COW();
    Ref->Remove(_pos, _count == -1 ? GetCount() : _count);
    FreeExtraMemory();
    return *this;
}

template <typename _T, typename _Traits, typename _Allocator>
void String<_T, _Traits, _Allocator>::MakeUpper(uint _begin, uint _count)
{
    AssertFlag(String<_T, _Traits, _Allocator>::ReadOnly);
    COW();

    if(AssertRange(_begin, _count))
    {
        _Traits::StrUpper(const_cast<_T*>(Ref->GetData()));
    }
    else
    {
        _T buffer[2];

        for(uint i = _begin; i < _begin+_count; i++)
        {
            if(i < GetCount())
            {
                buffer[0] = GetAt(i);
                buffer[1] = 0;
                //
               _Traits::StrUpper(buffer);
                SetAt(i, buffer[0]);
                continue;
            }
            break;
        }
    }

    Flags &= ~String<_T, _Traits, _Allocator>::LowerCase;
    Flags |= String<_T, _Traits, _Allocator>::UpperCase;
}

template <typename _T, typename _Traits, typename _Allocator>
void String<_T, _Traits, _Allocator>::MakeLower(uint _begin, uint _count)
{
    AssertFlag(String<_T, _Traits, _Allocator>::ReadOnly);
    COW();

    if(AssertRange(_begin, _count))
    {
        _Traits::StrLower(const_cast<_T*>(Ref->GetData()));
    }
    else
    {
        _T buffer[2];

        for(uint i = _begin; i < _begin+_count; i++)
        {
            if(i < GetCount())
            {
                buffer[0] = GetAt(i);
                buffer[1] = 0;

               _Traits::StrLower(buffer);
                SetAt(i, buffer[0]);
                continue;
            }
            break;
        }
    }

    Flags &= ~String<_T, _Traits, _Allocator>::UpperCase;
    Flags |= String<_T, _Traits, _Allocator>::LowerCase;
}

template <typename _T, typename _Traits, typename _Allocator>
void String<_T, _Traits, _Allocator>::MakeReverse()
{
    AssertFlag(String<_T, _Traits, _Allocator>::ReadOnly);

    if(GetCount() > 1)
    {
        COW();

       _T* data = Ref->GetData();

        for(uint i = 0; i < GetCount()/2; i++)
        {
           _T tmp = *(data+i);
            *(data+i) = *(data+GetCount()-i-1);
            *(data+GetCount()-i-1) = tmp;
        }
    
        SetFlags((Flags & String<_T, _Traits, _Allocator>::Reverse) ? String<_T, _Traits, _Allocator>::Reverse,
                !(Flags & String<_T, _Traits, _Allocator>::Reverse) ? String<_T, _Traits, _Allocator>::Reverse);
    }
}

template <typename _T, typename _Traits, typename _Allocator>
void String<_T, _Traits, _Allocator>::Format(const _T* _template, ...)
{
    SetEmpty();
    Reserve(256); // should be enough ! ...

    va_list arg;
    va_start(arg, _template);

    if(_Traits::Format(Ref->GetData(), _template, arg) < 0)
    {
        va_end(arg);
        throw XString(X::OutOfRange);
    }

    va_end(arg);
}

template <typename _T, typename _Traits, typename _Allocator>
void String<_T, _Traits, _Allocator>::Format(HINSTANCE _hmodule, uint _id, ...)
{
    String<_T, _Traits, _Allocator> format(_hmodule, _id);

    SetEmpty();
    Reserve(256); // should be enough ! ...

    va_list arg;
    va_start(arg, _id);

    if(_Traits::Format(Ref->GetData(), format, arg) < 0)
    {
        va_end(arg);
        throw XString(X::OutOfRange);
    }

    va_end(arg);
}

template <typename _T, typename _Traits, typename _Allocator>
void String<_T, _Traits, _Allocator>::TrimLeft()
{
    AssertFlag(String<_T, _Traits, _Allocator>::ReadOnly);
    COW();
    Ref->TrimSpace(0);
}

template <typename _T, typename _Traits, typename _Allocator>
void String<_T, _Traits, _Allocator>::TrimRight()
{
    AssertFlag(String<_T, _Traits, _Allocator>::ReadOnly);
    COW();
    Ref->TrimSpace(1);
}

template <typename _T, typename _Traits, typename _Allocator>
void String<_T, _Traits, _Allocator>::TrimLeftRight()
{
    AssertFlag(String<_T, _Traits, _Allocator>::ReadOnly);
    COW();
    Ref->TrimSpace(2);
}

template <typename _T, typename _Traits, typename _Allocator>
const String<_T, _Traits, _Allocator>& String<_T, _Traits, _Allocator>::Resize(uint _count)
{
    if(_count > 0)
    {
        AssertFlag(String<_T, _Traits, _Allocator>::ReadOnly);
        COW();
        Ref->Resize(_count);
    }
    return *this;
}

template <typename _T, typename _Traits, typename _Allocator>
const String<_T, _Traits, _Allocator>& String<_T, _Traits, _Allocator>::Reserve(uint _count)
{
    if(_count > 0)
    {
        AssertFlag(String<_T, _Traits, _Allocator>::ReadOnly);
        COW();
        Ref->Reserve(_count);
    }
    return *this;
}

template <typename _T, typename _Traits, typename _Allocator>
const String<_T, _Traits, _Allocator>& String<_T, _Traits, _Allocator>::FreeExtraMemory()
{
    if(!(Flags & String<_T, _Traits, _Allocator>::MemoryReserve))
    {
        AssertFlag(String<_T, _Traits, _Allocator>::ReadOnly);
        COW();
        Ref->FreeExtraMemory();
    }
    return *this;
}

template <typename _T, typename _Traits, typename _Allocator>
void String<_T, _Traits, _Allocator>::LoadString(HINSTANCE _hmodule, uint _id)
{
    SetEmpty();
    Reserve(4096-1);

    if(!StringFromResource(Ref->GetData(), GetCapacity(), _id, _hmodule))
    {
        throw XString();
    }

    FreeExtraMemory();
}

#ifndef _UNICODE
template <typename _T, typename _Traits, typename _Allocator>
void String<_T, _Traits, _Allocator>::ANSI2OEM()
{
    COW();
  ::CharToOem(Ref->GetData(), Ref->GetData());
}

template <typename _T, typename _Traits, typename _Allocator>
void String<_T, _Traits, _Allocator>::OEM2ANSI()
{
    COW();
  ::OemToChar(Ref->GetData(), Ref->GetData());
}
#endif

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ bool String<_T, _Traits, _Allocator>::AssertRange(uint _begin, uint _count) const
{
    return _begin == 0 && _count == -1; 
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ void String<_T, _Traits, _Allocator>::AssertIndex(uint _index) const
{
    if(_index > Ref->Count-1)
    {
        throw XString(X::OutOfRange);
    }
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ void String<_T, _Traits, _Allocator>::AssertFlag(uint _flag) const
{
    if(Flags & _flag)
    {
        throw XString(X::OutOfRange);
    }
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ void String<_T, _Traits, _Allocator>::COW()
{
    if(Ref->GetReference() > 1)
    {
        Clone();
    }
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ void String<_T, _Traits, _Allocator>::Clone()
{
    Ref->ReleaseReference();
    void* p = static_cast<_T*>(_Allocator::Allocate(sizeof(StrRef<_T, _Traits, _Allocator>)));
    Ref = new (p) StrRef<_T, _Traits, _Allocator>(Ref->GetData());
}

template <typename _T, typename _Traits, typename _Allocator>
short String<_T, _Traits, _Allocator>::CompareInternal(const _T* _sample) const
{
    if(Flags & String<_T, _Traits, _Allocator>::CaseSensitive)
    {
        if(Flags & String<_T, _Traits, _Allocator>::NLS)
        {
            return _Traits::StrColl(Ref->GetData(), _sample);
        }
        else
        {
            return _Traits::StrCompare(Ref->GetData(), _sample);
        }
    }
    else
    {
        if(Flags & String<_T, _Traits, _Allocator>::NLS)
        {
            return _Traits::StrIColl(Ref->GetData(), _sample);
        }
        else
        {
            return _Traits::StrICompare(Ref->GetData(), _sample);
        }
    }
}

template <typename _T, typename _Traits, typename _Allocator>
uint String<_T, _Traits, _Allocator>::FindInternal(const _T* _sample, uint _count) const
{
   _T* p = _Traits::StrSubstr(Ref->GetData(), _sample);
    uint n = 0;

    while(p != null && n < _count)
    {
        p = _Traits::StrSubstr(p+1, _sample), ++n;
    }

    return p == null ? -1 : p-Ref->GetData();
}

template <typename _T, typename _Traits, typename _Allocator>
uint String<_T, _Traits, _Allocator>::ReverseFindInternal(const _T* _sample, uint _count) const
{
    // in future ! ...
    return -1;
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ void String<_T, _Traits, _Allocator>::MemMove(_T* _dst, const _T* _src, uint _count)
{
    if(_dst != null && _src != null && _dst != _src && _count > 0)
    {
        memmove(_dst, _src, _count*sizeof(_T));
    }
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ void String<_T, _Traits, _Allocator>::MemSet(_T* _dst, uint _count, _T _sample)
{
    if(_dst != null && _count > 0)
    {
        memset(_dst, _sample, _count*sizeof(_T));
    }
}

// operators
template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ bool operator == (const String<_T, _Traits, _Allocator>& _s1, const String<_T, _Traits, _Allocator>& _s2)
{
    return _s1.Compare(_s2) == 0;
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ bool operator == (const String<_T, _Traits, _Allocator>& _s, const _T* _sample)
{
    return _s.Compare(_sample) == 0;
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ bool operator == (const String<_T, _Traits, _Allocator>& _s, _T _ch)
{
    return _s.Compare(_ch) == 0;
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ bool operator == (const String<_T, _Traits, _Allocator>& _s, int _number)
{
    return _s.Compare(_number) == 0;
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ bool operator == (const String<_T, _Traits, _Allocator>& _s, double _number)
{
    return _s.Compare(_number) == 0;
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ bool operator == (const _T* _sample, const String<_T, _Traits, _Allocator>& _s)
{
    return _s.Compare(_sample) == 0;
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ bool operator == (_T _ch, const String<_T, _Traits, _Allocator>& _s)
{
    return _s.Compare(_ch) == 0;
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ bool operator == (int _number, const String<_T, _Traits, _Allocator>& _s)
{
    return _s.Compare(_number) == 0;
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ bool operator == (double _number, const String<_T, _Traits, _Allocator>& _s)
{
    return _s.Compare(_number) == 0;
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ bool operator != (const String<_T, _Traits, _Allocator>& _s1, const String<_T, _Traits, _Allocator>& _s2)
{
    return _s1.Compare(_s2) != 0;
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ bool operator != (const String<_T, _Traits, _Allocator>& _s, const _T* _sample)
{
    return _s.Compare(_sample) != 0;
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ bool operator != (const String<_T, _Traits, _Allocator>& _s, _T _ch)
{
    return _s.Compare(_ch) != 0;
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ bool operator != (const String<_T, _Traits, _Allocator>& _s, int _number)
{
    return _s.Compare(_number) != 0;
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ bool operator != (const String<_T, _Traits, _Allocator>& _s, double _number)
{
    return _s.Compare(_number) != 0;
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ bool operator != (const _T* _sample, const String<_T, _Traits, _Allocator>& _s)
{
    return _s.Compare(_sample) != 0;
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ bool operator != (_T _ch, const String<_T, _Traits, _Allocator>& _s)
{
    return _s.Compare(_ch) != 0;
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ bool operator != (int _number, const String<_T, _Traits, _Allocator>& _s)
{
    return _s.Compare(_number) != 0;
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ bool operator != (double _number, const String<_T, _Traits, _Allocator>& _s)
{
    return _s.Compare(_number) != 0;
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ bool operator < (const String<_T, _Traits, _Allocator>& _s1, const String<_T, _Traits, _Allocator>& _s2)
{
    return _s1.Compare(_s2) < 0;
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ bool operator < (const String<_T, _Traits, _Allocator>& _s, const _T* _sample)
{
    return _s.Compare(_sample) < 0;
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ bool operator < (const String<_T, _Traits, _Allocator>& _s, _T _ch)
{
    return _s.Compare(_ch) < 0;
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ bool operator < (const String<_T, _Traits, _Allocator>& _s, int _number)
{
    return _s.Compare(_number) < 0;
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ bool operator < (const String<_T, _Traits, _Allocator>& _s, double _number)
{
    return _s.Compare(_number) < 0;
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ bool operator < (const _T* _sample, const String<_T, _Traits, _Allocator>& _s)
{
    return _s.Compare(_sample) < 0;
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ bool operator < (_T _ch, const String<_T, _Traits, _Allocator>& _s)
{
    return _s.Compare(_ch) < 0;
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ bool operator < (int _number, const String<_T, _Traits, _Allocator>& _s)
{
    return _s.Compare(_number) < 0;
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ bool operator < (double _number, const String<_T, _Traits, _Allocator>& _s)
{
    return _s.Compare(_number) < 0;
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ bool operator <= (const String<_T, _Traits, _Allocator>& _s1, const String<_T, _Traits, _Allocator>& _s2)
{
    return _s1.Compare(_s2) <= 0;
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ bool operator <= (const String<_T, _Traits, _Allocator>& _s, const _T* _sample)
{
    return _s.Compare(_sample) <= 0;
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ bool operator <= (const String<_T, _Traits, _Allocator>& _s, _T _ch)
{
    return _s.Compare(_ch) <= 0;
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ bool operator <= (const String<_T, _Traits, _Allocator>& _s, int _number)
{
    return _s.Compare(_number) <= 0;
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ bool operator <= (const String<_T, _Traits, _Allocator>& _s, double _number)
{
    return _s.Compare(_number) <= 0;
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ bool operator <= (const _T* _sample, const String<_T, _Traits, _Allocator>& _s)
{
    return _s.Compare(_sample) <= 0;
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ bool operator <= (_T _ch, const String<_T, _Traits, _Allocator>& _s)
{
    return _s.Compare(_ch) <= 0;
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ bool operator <= (int _number, const String<_T, _Traits, _Allocator>& _s)
{
    return _s.Compare(_number) <= 0;
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ bool operator <= (double _number, const String<_T, _Traits, _Allocator>& _s)
{
    return _s.Compare(_number) <= 0;
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ bool operator > (const String<_T, _Traits, _Allocator>& _s1, const String<_T, _Traits, _Allocator>& _s2)
{
    return _s1.Compare(_s2) > 0;
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ bool operator > (const String<_T, _Traits, _Allocator>& _s, const _T* _sample)
{
    return _s.Compare(_sample) > 0;
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ bool operator > (const String<_T, _Traits, _Allocator>& _s, _T _ch)
{
    return _s.Compare(_ch) > 0;
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ bool operator > (const String<_T, _Traits, _Allocator>& _s, int _number)
{
    return _s.Compare(_number) > 0;
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ bool operator > (const String<_T, _Traits, _Allocator>& _s, double _number)
{
    return _s.Compare(_number) > 0;
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ bool operator > (const _T* _sample, const String<_T, _Traits, _Allocator>& _s)
{
    return _s.Compare(_sample) > 0;
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ bool operator > (_T _ch, const String<_T, _Traits, _Allocator>& _s)
{
    return _s.Compare(_ch) > 0;
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ bool operator > (int _number, const String<_T, _Traits, _Allocator>& _s)
{
    return _s.Compare(_number) > 0;
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ bool operator > (double _number, const String<_T, _Traits, _Allocator>& _s)
{
    return _s.Compare(_number) > 0;
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ bool operator >= (const String<_T, _Traits, _Allocator>& _s1, const String<_T, _Traits, _Allocator>& _s2)
{
    return _s1.Compare(_s2) >= 0;
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ bool operator >= (const String<_T, _Traits, _Allocator>& _s, const _T* _sample)
{
    return _s.Compare(_sample) >= 0;
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ bool operator >= (const String<_T, _Traits, _Allocator>& _s, _T _ch)
{
    return _s.Compare(_ch) >= 0;
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ bool operator >= (const String<_T, _Traits, _Allocator>& _s, int _number)
{
    return _s.Compare(_number) >= 0;
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ bool operator >= (const String<_T, _Traits, _Allocator>& _s, double _number)
{
    return _s.Compare(_number) >= 0;
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ bool operator >= (const _T* _sample, const String<_T, _Traits, _Allocator>& _s)
{
    return _s.Compare(_sample) >= 0;
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ bool operator >= (_T _ch, const String<_T, _Traits, _Allocator>& _s)
{
    return _s.Compare(_ch) >= 0;
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ bool operator >= (int _number, const String<_T, _Traits, _Allocator>& _s)
{
    return _s.Compare(_number) >= 0;
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ bool operator >= (double _number, const String<_T, _Traits, _Allocator>& _s)
{
    return _s.Compare(_number) >= 0;
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ String<_T, _Traits, _Allocator> operator + (const String<_T, _Traits, _Allocator>& _s1, const String<_T, _Traits, _Allocator>& _s2)
{
    String<>_T, _Allocator> string(_s1);
    string += _s2;
    return string;
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ String<_T, _Traits, _Allocator> operator + (const String<_T, _Traits, _Allocator>& _s, const _T* _sample)
{
    String<>_T, _Allocator> string(_s);
    string += _sample;
    return string;
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ String<_T, _Traits, _Allocator> operator + (const String<_T, _Traits, _Allocator>& _s, _T _ch)
{
    String<>_T, _Allocator> string(_s);
    string += _ch;
    return string;
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ String<_T, _Traits, _Allocator> operator + (const String<_T, _Traits, _Allocator>& _s, int _number)
{
    String<>_T, _Allocator> string(_s);
    string += _number;
    return string;
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ String<_T, _Traits, _Allocator> operator + (const String<_T, _Traits, _Allocator>& _s, double _number)
{
    String<>_T, _Allocator> string(_s);
    string += _number;
    return string;
}
////////////////////////////////////////////////////////////////////////////////////////
// Functions
// ---------
__INLINE__ tchar* StrClone(const tchar* _s)
{
    if(_s)
    {
        return StrCopy(new tchar[StrLen(_s)+1], _s);
    }
    return null;
}

__INLINE__ int StrLen(const tchar* _s)
{
    if(_s)
    {
        return (int)_tcslen(_s);
    }
    return 0;
}

__INLINE__ int StrCompare(const tchar* _s1, const tchar* _s2)
{
    if(_s1 && _s2)
    {
        return *_s1 != *_s2 ? *_s1-*_s2 : _tcscmp(_s1, _s2);
    }
    return ConstError32;
}

__INLINE__ int StrICompare(const tchar* _s1, const tchar* _s2)
{
    if(_s1 && _s2)
    {
        return _tcsicmp(_s1, _s2);
    }
    return ConstError32;
}

__INLINE__ int StrNCompare(const tchar* _s1, const tchar* _s2, size_t _count)
{
    if(_s1 && _s2 && _count > 0)
    {
        return _tcsncmp(_s1, _s2, _count);
    }
    return ConstError32;
}

__INLINE__ int StrNICompare(const tchar* _s1, const tchar* _s2, size_t _count)
{
    if(_s1 && _s2 && _count > 0)
    {
        return _tcsnicmp(_s1, _s2, _count);
    }
    return ConstError32;
}

__INLINE__ int StrColl(const tchar* _s1, const tchar* _s2)
{
    if(_s1 && _s2)
    {
        return _tcscoll(_s1, _s2);
    }
    return ConstError32;
}

__INLINE__ int StrIColl(const tchar* _s1, const tchar* _s2)
{
    if(_s1 && _s2)
    {
        return _tcsicoll(_s1, _s2);
    }
    return ConstError32;
}

__INLINE__ int StrNColl(const tchar* _s1, const tchar* _s2, size_t _count)
{
    if(_s1 && _s2 && _count > 0)
    {
        return _tcsncoll(_s1, _s2, _count);
    }
    return ConstError32;
}

__INLINE__ int StrNIColl(const tchar* _s1, const tchar* _s2, size_t _count)
{
    if(_s1 && _s2 && _count > 0)
    {
        return _tcsnicoll(_s1, _s2, _count);
    }
    return ConstError32;
}

__INLINE__ tchar* StrCopy(tchar* _s1, const tchar* _s2)
{
    if(_s1 && _s2)
    {
        return _tcscpy(_s1, _s2);
    }
    return null;
}

__INLINE__ tchar* StrNCopy(tchar* _s1, const tchar* _s2, size_t _count)
{
    if(_s1 && _s2 && _count > 0)
    {
        return _tcsncpy(_s1, _s2, _count);
    }
    return null;
}

__INLINE__ tchar* StrCaten(tchar* _s1, const tchar* _s2)
{
    if(_s1 && _s2)
    {
        return _tcscat(_s1, _s2);
    }
    return null;
}

__INLINE__ tchar* StrNCaten(tchar* _s1, const tchar* _s2, size_t _count)
{
    if(_s1 && _s2 && _count > 0)
    {
        return _tcsncat(_s1, _s2, _count);
    }
    return null;
}

__INLINE__ tchar* StrChar(const tchar* _s, int _ch)
{
    if(_s)
    {
        return (tchar*)_tcschr(_s, _ch);
    }
    return null;
}

__INLINE__ tchar* StrRChar(const tchar* _s, int _ch)
{
    if(_s)
    {
        return (tchar*)_tcsrchr(_s, _ch);
    }
    return null;
}

__INLINE__ tchar* StrSubstr(const tchar* _s, const tchar* _sub_str)
{
    if(_s && _sub_str)
    {
        return (tchar*)_tcsstr(_s, _sub_str);
    }
    return null;
}

__INLINE__ tchar* StrUpper(tchar* _s)
{
    if(_s)
    {
        return _tcsupr(_s);
    }
    return null;
}

__INLINE__ tchar* StrLower(tchar* _s)
{
    if(_s)
    {
        return _tcslwr(_s);
    }
    return null;
}

__INLINE__ tchar* Strpbrk(const tchar* _s, const tchar* _charset)
{
    if(_s && _charset)
    {
        return (tchar*)_tcspbrk(_s, _charset);
    }
    return null;
}

__INLINE__ int StrSpan(const tchar* _s, const tchar* _charset)
{
    if(_s && _charset)
    {
        return (int)_tcsspn(_s, _charset);
    }
    return ConstError32;
}

__INLINE__ int StrCSpan(const tchar* _s, const tchar* _charset)
{
    if(_s && _charset)
    {
        return (int)_tcscspn(_s, _charset);
    }
    return ConstError32;
}

__INLINE__ long StrToInteger(const tchar* _nptr, tchar** _endptr, int _base)
{
    if(_nptr)
    {
        return _tcstol(_nptr, _endptr, _base);
    }
    return ConstError32;
}

__INLINE__ double StrToDouble(const tchar* _nptr, tchar** _endptr)
{
    if(_nptr)
    {
        return _tcstod(_nptr, _endptr);
    }
    return 0.0;
}

__INLINE__ int StrLenW(const wchar* _s)
{
    if(_s)
    {
        return (int)wcslen(_s);
    }
    return 0;
}

__INLINE__ int StrCompareW(const wchar* _s1, const wchar* _s2)
{
    if(_s1 && _s2)
    {
        return wcscmp(_s1, _s2);
    }
    return ConstError32;
}

__INLINE__ int StrICompareW(const wchar* _s1, const wchar* _s2)
{
    if(_s1 && _s2)
    {
        return wcsicmp(_s1, _s2);
    }
    return ConstError32;
}

__INLINE__ int StrNCompareW(const wchar* _s1, const wchar* _s2, size_t _count)
{
    if(_s1 && _s2 && _count > 0)
    {
        return wcsncmp(_s1, _s2, _count);
    }
    return ConstError32;
}

__INLINE__ int StrNICompareW(const wchar* _s1, const wchar* _s2, size_t _count)
{
    if(_s1 && _s2 && _count > 0)
    {
        return wcsnicmp(_s1, _s2, _count);
    }
    return ConstError32;
}

__INLINE__ int StrCollW(const wchar* _s1, const wchar* _s2)
{
    if(_s1 && _s2)
    {
        return wcscoll(_s1, _s2);
    }
    return ConstError32;
}

__INLINE__ int StrICollW(const wchar* _s1, const wchar* _s2)
{
    if(_s1 && _s2)
    {
        return wcsicoll(_s1, _s2);
    }
    return ConstError32;
}

__INLINE__ int StrNCollW(const wchar* _s1, const wchar* _s2, size_t _count)
{
    if(_s1 && _s2 && _count > 0)
    {
        return _wcsncoll(_s1, _s2, _count);
    }
    return ConstError32;
}

__INLINE__ int StrNICollW(const wchar* _s1, const wchar* _s2, size_t _count)
{
    if(_s1 && _s2 && _count > 0)
    {
        return _wcsnicoll(_s1, _s2, _count);
    }
    return ConstError32;
}

__INLINE__ wchar* StrCopyW(wchar* _s1, const wchar* _s2)
{
    if(_s1 && _s2)
    {
        return wcscpy(_s1, _s2);
    }
    return null;
}

__INLINE__ wchar* StrNCopyW(wchar* _s1, const wchar* _s2, size_t _count)
{
    if(_s1 && _s2 && _count > 0)
    {
        return wcsncpy(_s1, _s2, _count);
    }
    return null;
}

__INLINE__ wchar* StrCatenW(wchar* _s1, const wchar* _s2)
{
    if(_s1 && _s2)
    {
        return wcscat(_s1, _s2);
    }
    return null;
}

__INLINE__ wchar* StrNCatenW(wchar* _s1, const wchar* _s2, size_t _count)
{
    if(_s1 && _s2 && _count > 0)
    {
        return wcsncat(_s1, _s2, _count);
    }
    return null;
}

__INLINE__ wchar* StrCharW(const wchar* _s, int character)
{
    if(_s)
    {
        return (wchar*)wcschr(_s, character);
    }
    return null;
}

__INLINE__ wchar* StrSubstrW(const wchar* _s, const wchar* _sub_str)
{
    if(_s && _sub_str)
    {
        return (wchar*)wcsstr(_s, _sub_str);
    }
    return null;
}

__INLINE__ wchar* StrUpperW(wchar* _s)
{
    if(_s)
    {
        return wcsupr(_s);
    }
    return null;
}

__INLINE__ wchar* StrLowerW(wchar* _s)
{
    if(_s)
    {
        return wcslwr(_s);
    }
    return null;
}

__INLINE__ wchar* StrpbrkW(const wchar* _s, const wchar* _charset)
{
    if(_s && _charset)
    {
        return (wchar*)wcspbrk(_s, _charset);
    }
    return null;
}

__INLINE__ int StrSpanW(const wchar* _s, const wchar* _charset)
{
    if(_s && _charset)
    {
        return (int)wcsspn(_s, _charset);
    }
    return ConstError32;
}

__INLINE__ int StrCSpanW(const wchar* _s, const wchar* _charset)
{
    if(_s && _charset)
    {
        return (int)wcscspn(_s, _charset);
    }
    return ConstError32;
}

__INLINE__ long StrToIntegerW(const wchar* _nptr, wchar** _endptr, int _base)
{
    if(_nptr)
    {
        return wcstol(_nptr, _endptr, _base);
    }
    return ConstError32;
}

__INLINE__ double StrToDoubleW(const wchar* _nptr, wchar** _endptr)
{
    if(_nptr)
    {
        return wcstod(_nptr, _endptr);
    }
    return 0.0;
}

__INLINE__ int MultiByteToWideChar(const char* _string, int _count, wchar* _wstring, int _wcount, uint _codepage, uint _flags)
{
    if(_string != null && _wstring != null)
    {
       _wstring[0] = 0;
        return ::MultiByteToWideChar(_codepage, _flags, _string, _count, _wstring, _wcount);
    }

    return ConstError32;
}

__INLINE__ int WideCharToMultiByte(const wchar* _wstring, int _wcount, char* _string, int _count, uint _codepage, uint _flags, const char* _unmappable, BOOL* _default_ch)
{
    if(_wstring && _string)
    {
       _string[0] = 0;
        return ::WideCharToMultiByte(_codepage, _flags, _wstring, _wcount, _string, _count, _unmappable, _default_ch);
    }

    return ConstError32;
}

template <typename _T, typename _Traits, typename _Allocator>
__INLINE_TEMPLATE__ bool StringFromResource(String<_T, _Traits, _Allocator>& _string, uint _idres, HINSTANCE _hmodule)
{
   _string.LoadString(_hmodule, _idres);
    return true;
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __STRING_INL__
