////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __COM_ICLASSFACTORYIMP_H__
#define __COM_ICLASSFACTORYIMP_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
class __DECLSPEC__ ComModule;
////////////////////////////////////////////////////////////////////////////////////////
// class IClassFactoryImp
// ----- ----------------
template <typename T> class IClassFactoryImp : public IUnknownImp, public IClassFactory
{
    public:
     // ctor/dtor
                        IClassFactoryImp(ComModule* = null);
     virtual           ~IClassFactoryImp();

     // IUnknownImp
     ULONG   __stdcall  AddRef();
     ULONG   __stdcall  Release();

     HRESULT            QueryObject(const IID&, void**);
     HRESULT __stdcall  QueryInterface(const IID&, void**);

     // IClassFactory
     HRESULT __stdcall  CreateInstance(IUnknown*, REFIID, void**);
     HRESULT __stdcall  LockServer(BOOL);
};

// implementation
template <typename T>
IClassFactoryImp<T>::IClassFactoryImp(ComModule* _module)
                   : IUnknownImp(_module)
{
}

template <typename T>
IClassFactoryImp<T>::~IClassFactoryImp()
{
}

template <typename T>
ULONG IClassFactoryImp<T>::AddRef()
{
    return GetOuter()->AddRef();
}

template <typename T>
ULONG IClassFactoryImp<T>::Release()
{
    return GetOuter()->Release();
}

template <typename T>
HRESULT IClassFactoryImp<T>::QueryInterface(const IID& _iid, void** _ppi)
{
    return GetOuter()->QueryInterface(_iid, _ppi);
}

template <typename T>
HRESULT IClassFactoryImp<T>::QueryObject(const IID& _iid, void** _ppi)
{
    if(_ppi == null)
    {
        return E_INVALIDARG;
    }

    *_ppi = null;

    if(_iid == IID_IClassFactory)
    {
        *_ppi = static_cast<IClassFactory*>(this);
    }

    if(*_ppi != null)
    {
        reinterpret_cast<IUnknown*>(*_ppi)->AddRef();
        return S_OK;
    }

    return E_NOINTERFACE;
}

template <typename T>
HRESULT __stdcall IClassFactoryImp<T>::CreateInstance(IUnknown* _outer, REFIID _iid, void** _ppi)
{
    HRESULT hr = E_NOINTERFACE;

    if(_ppi != null)
    {
        if(_outer != null)
        {
            hr = CLASS_E_NOAGGREGATION;
        }
        else
        {
            *_ppi = null;

            T* t;

            try
            {
                t = new T(Module);
            }
            catch(...)
            {
                return E_OUTOFMEMORY;
            }

            hr = t->QueryInterface(_iid, _ppi);

            t->Release();

            if(SUCCEEDED(hr) && *_ppi != null)
            {
                hr = S_OK;
            }
            else
            {
                delete t;
                hr = E_FAIL;
            }
        }
    }

    return hr;
}

template <typename T>
HRESULT __stdcall IClassFactoryImp<T>::LockServer(BOOL _lock)
{
    if(Module == null)
    {
        return E_FAIL;
    }

    if(_lock)
    {
        Module->Lock();
    }
    else
    {
        Module->Unlock();
    }

    return S_OK;
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __COM_ICLASSFACTORYIMP_H__
