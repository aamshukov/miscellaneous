////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __COMPTR_INL__
#define __COMPTR_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class ComPtr
// ----- ------
template <typename T> __INLINE_TEMPLATE__ ComPtr<T>::ComPtr()
{
    P = null;
}

template <typename T> __INLINE_TEMPLATE__ ComPtr<T>::ComPtr(T* _p)
{
    if((P = _p) != null)
    {
        P->AddRef();
    }
}

template <typename T> __INLINE_TEMPLATE__ ComPtr<T>::ComPtr(const ComPtr<T>& _other)
{
    if((P = _other.p) != null)
    {
        P->AddRef();
    }
}

template <typename T> __INLINE_TEMPLATE__ ComPtr<T>::~ComPtr()
{
    if(P != null)
    {
        P->Release(), P = null;
    }
}

template <typename T> __INLINE_TEMPLATE__ _Stub<T>* ComPtr<T>::operator -> () const
{
    __x_assert__(P != null);
    return reinterpret_cast<_Stub<T>*>(P); // P != null
}

template <typename T> __INLINE_TEMPLATE__ T* ComPtr<T>::operator = (T* _p)
{
    return reinterpret_cast<T*>(AssignPtr(reinterpret_cast<IUnknown**>(&P), _p));
}

template <typename T> __INLINE_TEMPLATE__ T* ComPtr<T>::operator = (const ComPtr<T>& other)
{
    return reinterpret_cast<T*>(AssignPtr(reinterpret_cast<IUnknown**>(&P), other.P));
}

template <typename T> __INLINE_TEMPLATE__ bool ComPtr<T>::operator < (T* _p) const
{
    return P < _p;
}

template <typename T> __INLINE_TEMPLATE__ bool ComPtr<T>::operator == (T* _p) const
{
    return P == _p;
}

template <typename T> __INLINE_TEMPLATE__ void ComPtr<T>::Release()
{
    IUnknown* p = P;

    if(p != null)
    {
        P = null;
        
        p->Release();
    }
}

template <typename T> __INLINE_TEMPLATE__ bool ComPtr<T>::IsEqualObject(IUnknown* _p)
{
    if(P == null && _p == null)
    {
        return true;
    }

    if(P == null || _p == null)
    {
        return false;
    }

    ComPtr<IUnknown> unk1;
    ComPtr<IUnknown> unk2;

    P->QueryInterface(IID_IUnknown, reinterpret_cast<void**>(&unk1));
   _p->QueryInterface(IID_IUnknown, reinterpret_cast<void**>(&unk2));

    return unk1 == unk2;
}

template <typename T> __INLINE_TEMPLATE__ void ComPtr<T>::Attach(T* _p)
{
    if(P != null)
    {
        P->Release();
    }

    P = _p;
}

template <typename T> __INLINE_TEMPLATE__ T* ComPtr<T>::Detach()
{
    T* p = P;
       P = null;

    return p;
}

template <typename T> __INLINE_TEMPLATE__ HRESULT ComPtr<T>::CopyTo(T** _pp)
{
    if(_pp != null)
    {
        *_pp = P;

        if(P != null)
        {
            P->AddRef();
        }
        
        return S_OK;
    }

    return E_POINTER;
}

template <typename T> __INLINE_TEMPLATE__ HRESULT ComPtr<T>::CoCreateInstance(CLSID& _clsid, IUnknown* _outer, uint _context)
{
    // P == null
    return ::CoCreateInstance(_clsid, _outer, _context, __uuidof(T), reinterpret_cast<void**>(&P));
}

template <typename T> __INLINE_TEMPLATE__ HRESULT ComPtr<T>::CoCreateInstance(const wchar* _prog_id, IUnknown* _outer, uint _context)
{
    CLSID clsid;
    
    HRESULT hr = CLSIDFromProgID(_prog_id, &_clsid);

    // P == null
    if(SUCCEEDED(hr))
    {
        hr = ::CoCreateInstance(_clsid, _outer, context, __uuidof(T), reinterpret_cast<void**>(&P));
    }

    return hr;
}

template <typename T> __INLINE_TEMPLATE__ IUnknown* ComPtr<T>::AssignPtr(IUnknown** _pp, IUnknown* _p)
{
    if(_p != null)
    {
        _p->AddRef();
    }

    if(*_pp != null)
    {
        (*_pp)->Release();
    }

    *_pp = _p;

    return _p;
}

template <typename T> __INLINE_TEMPLATE__ IUnknown* ComPtr<T>::AssignPtrQI(IUnknown** _pp, IUnknown* _p, IID& iid)
{
    IUnknown* p = *_pp;

    *_pp = null;

    if(_p != null)
    {
        _p->QueryInterface(iid, reinterpret_cast<void**>(_pp));
    }

    if(p != null)
    {
        p->Release();
    }

    return *_pp;
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __COMPTR_INL__
