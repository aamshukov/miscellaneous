////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __AUTOPTR_INL__
#define __AUTOPTR_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class AutoPtrBase
// ----- -----------
template <typename _T> void* AutoPtrBase<_T>::operator new(size_t)
{
    return null;
}

template <typename _T> void AutoPtrBase<_T>::operator delete(void* _p)
{
    if(_p)
    {
        ((AutoPtrBase<_T>*)_p)->P = null;
    }
}

template <typename _T> AutoPtrBase<_T>::AutoPtrBase() : P(null)
{
}

template <typename _T> AutoPtrBase<_T>::AutoPtrBase(_T* _p) : P(_p)
{
}

template <typename _T> __INLINE_TEMPLATE__ _T* AutoPtrBase<_T>::GetP() const
{
    return P;
}

template <typename _T> __INLINE_TEMPLATE__ _T& AutoPtrBase<_T>::operator * () const
{
#ifndef __PALM_OS__
   _ASSERT(P != null);
#endif
    return *P; // P != null
}

template <typename _T> __INLINE_TEMPLATE__ _T** AutoPtrBase<_T>::operator & ()
{
    return &P; // P == null
}

template <typename _T> __INLINE_TEMPLATE__ AutoPtrBase<_T>::operator _T* () const
{
    return reinterpret_cast<_T*>(P);
}

template <typename _T> __INLINE_TEMPLATE__ bool AutoPtrBase<_T>::operator ! () const
{
    return P == null;
}

template <typename _T> __INLINE_TEMPLATE__ _T* AutoPtrBase<_T>::Relinquish()
{ 
   _T* p;
    p = P;
    P = null;
    return p;
}

template <typename _T> __INLINE_TEMPLATE__ _T* AutoPtrBase<_T>::Reset(_T* _p)
{
    _T* t = P;
        P = _p;
    return t;
}
////////////////////////////////////////////////////////////////////////////////////////
// class AutoPtr
// ----- -------
template <typename _T> AutoPtr<_T>::AutoPtr() : AutoPtrBase<_T>()
{
}

template <typename _T> AutoPtr<_T>::AutoPtr(_T* _p) : AutoPtrBase<_T>(_p)
{
}

template <typename _T> AutoPtr<_T>::~AutoPtr()
{
    if(P != null)
    {
        delete P, P = null;
    }
}

template <typename _T> __INLINE_TEMPLATE__ AutoPtr<_T>& AutoPtr<_T>::operator = (_T* _p)
{
    if(P != _p)
    {
        if(P != null)
        {
            delete P;
        }
        P = _p;
    } 
    return *this;
}

template <typename _T> __INLINE_TEMPLATE__ _T* AutoPtr<_T>::operator -> () const
{
    return P;
}
////////////////////////////////////////////////////////////////////////////////////////
// class AutoPtrArray
// ----- ------------
template <typename _T> AutoPtrArray<_T>::AutoPtrArray() : AutoPtrBase<_T>()
{
}

template <typename _T> AutoPtrArray<_T>::AutoPtrArray(ulong _count) : AutoPtrBase<_T>()
{
    P = new _T[_count];
}

template <typename _T> AutoPtrArray<_T>::AutoPtrArray(_T _array[]) : AutoPtrBase<_T>(_array)
{
}

template <typename _T> AutoPtrArray<_T>::~AutoPtrArray()
{
    if(P != null)
    {
        delete [] P, P = null;
    }
}

template <typename _T> __INLINE_TEMPLATE__ AutoPtrArray<_T>& AutoPtrArray<_T>::operator = (_T _p[])
{
    if(P != null)
    {
        delete [] P;
    }

    P = _p;
    return *this;
}

template <typename _T> __INLINE_TEMPLATE__ _T& AutoPtrArray<_T>::operator [] (int _i)
{
    return P[_i];
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __AUTOPTR_INL__
