////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __VIRTUALBUFFER_INL__
#define __VIRTUALBUFFER_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class VirtualBufferHelper
// ----- -------------------
template <typename T> __INLINE_TEMPLATE__ T* VirtualBufferHelper<T>::operator () (T* _current)
{
    return _current;
}
////////////////////////////////////////////////////////////////////////////////////////
// class VirtualBuffer
// ----- -------------
template <typename T, uint _MaxCount> VirtualBuffer<T, _MaxCount>::VirtualBuffer()
{
    Base = reinterpret_cast<T*>(VirtualAlloc(null, sizeof(T)*_MaxCount, MEM_RESERVE, PAGE_READWRITE));
    Top  = Current = Base;
    //
    VirtualAlloc(Base, sizeof(T), MEM_COMMIT, PAGE_READWRITE);
}

template <typename T, uint _MaxCount> VirtualBuffer<T, _MaxCount>::~VirtualBuffer()
{
    if(Base)
    {
        VirtualFree(Base, 0, MEM_RELEASE);
    }

    Top     = null;
    Base    = null;
    Current = null;
}

template <typename T, uint _MaxCount> __INLINE_TEMPLATE__ int VirtualBuffer<T, _MaxCount>::Except(EXCEPTION_POINTERS* _ep)
{
    if(_ep)
    {
        EXCEPTION_RECORD* except = _ep->ExceptionRecord;
        
        if(except->ExceptionCode != EXCEPTION_ACCESS_VIOLATION)
        {
            return EXCEPTION_CONTINUE_SEARCH;
        }

        byte* address = reinterpret_cast<byte*>(except->ExceptionInformation[1]);

        VirtualAlloc(address, (reinterpret_cast<byte*>(Top)-reinterpret_cast<byte*>(Base)), MEM_COMMIT, PAGE_READWRITE);

        return EXCEPTION_CONTINUE_EXECUTION;
    }

    return EXCEPTION_ACCESS_VIOLATION;
}

template <typename T, uint _MaxCount> __INLINE_TEMPLATE__ void VirtualBuffer<T, _MaxCount>::Seek(int _index)
{
    if(_index < _MaxCount)
    {
        Current = &Base[_index];
    }
}

template <typename T, uint _MaxCount> __INLINE_TEMPLATE__ void VirtualBuffer<T, _MaxCount>::SetAt(int _index, const T& _element)
{
    __try
    {
        if(index < _MaxCount)
        {
            T* p = &Base[_index]
              *p = _element;

            Top = p > Top ? p : Top;
        }
    }
    __except(Except(GetExceptionInformation()))
    {
    }
}

template <typename T, uint _MaxCount> __INLINE_TEMPLATE__ const T& VirtualBuffer<T, _MaxCount>::operator [] (int _index) const
{
    return Base[_index];
}

template <typename T, uint _MaxCount> __INLINE_TEMPLATE__ VirtualBuffer<T, _MaxCount>::operator T* ()
{
    return Base;
}

template <typename T, uint _MaxCount> __INLINE_TEMPLATE__ T& VirtualBuffer<T, _MaxCount>::Read()
{
    return *Current; // Current != null
}

template <typename T, uint _MaxCount> __INLINE_TEMPLATE__ void VirtualBuffer<T, _MaxCount>::Write(const T& _element)
{
    __try
    {
        if(Current)
        {
            *Current = _element;
            
            ++Current;
            
            Top = Current > Top ? Current : Top;
        }
    }
    __except(Except(GetExceptionInformation()))
    {
    }
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __VIRTUALBUFFER_INL__
