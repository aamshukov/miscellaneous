////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __COMPTR_H__
#define __COMPTR_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class _Stub
// ----- -----
template <typename T> class _Stub : public T
{
    private:
     virtual ulong STDMETHODCALLTYPE AddRef()   = 0;
     virtual ulong STDMETHODCALLTYPE Release()  = 0;
};
////////////////////////////////////////////////////////////////////////////////////////
// class ComPtr
// ----- ------
template <typename T> class ComPtr : public AutoPtrBase<T>
{
    private:
     IUnknown*  AssignPtr(IUnknown**, IUnknown*);
     IUnknown*  AssignPtrQI(IUnknown**, IUnknown*, IID&);
    public:
     // ctor/dtor
                ComPtr();
                ComPtr(T*);
                ComPtr(const ComPtr<T>&);
               ~ComPtr();

     // operators
    _Stub<T>*   operator -> ()              const;

     T*         operator = (T*);
     T*         operator = (const ComPtr<T>&);
     
     bool       operator < (T*)             const;
     bool       operator == (T*)            const;

     // protocol
     void       Release();

     bool       IsEqualObject(IUnknown*);

     void       Attach(T*);
     T*         Detach();

     HRESULT    CopyTo(T**);

     HRESULT    CoCreateInstance(CLSID&, IUnknown* = null, uint = CLSCTX_ALL);
     HRESULT    CoCreateInstance(const wchar*, IUnknown* = null, uint = CLSCTX_ALL);

     template <typename Q> HRESULT QueryInterface(Q** _pp) const
     {
        if(P && _pp && *_pp == null)
        {
            return P->QueryInterface(__uuidof(Q), reinterpret_cast<void**>(pp));
        }
        return E_POINTER;
     }
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __COMPTR_H__
