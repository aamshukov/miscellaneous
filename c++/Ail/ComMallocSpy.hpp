////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __COMMALLOCSPY_H__
#define __COMMALLOCSPY_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class ComMallocSpyImp
// ----- ---------------
class __DECLSPEC__ ComMallocSpyImp : public IMallocSpy, private ObjectRef<>, private SyncObject
{
    public:
     // ctor/dtor
                                        ComMallocSpyImp();
                                       ~ComMallocSpyImp();

     // protocol
     virtual ulong STDMETHODCALLTYPE    AddRef();
     virtual ulong STDMETHODCALLTYPE    Release();
     virtual HRESULT STDMETHODCALLTYPE  QueryInterface(const IID&, void**);

     virtual ulong STDMETHODCALLTYPE    PreAlloc(ulong);
     virtual void* STDMETHODCALLTYPE    PostAlloc(void*);

     virtual void* STDMETHODCALLTYPE    PreFree(void*, BOOL);
     virtual void  STDMETHODCALLTYPE    PostFree(BOOL);

     virtual ulong STDMETHODCALLTYPE    PreRealloc(void*, ulong, void**, BOOL);
     virtual void* STDMETHODCALLTYPE    PostRealloc(void*, BOOL);

     virtual void* STDMETHODCALLTYPE    PreGetSize(void*, BOOL);
     virtual ulong STDMETHODCALLTYPE    PostGetSize(ulong, BOOL);

     virtual void* STDMETHODCALLTYPE    PreDidAlloc(void*, BOOL);
     virtual int   STDMETHODCALLTYPE    PostDidAlloc(void*, BOOL, int);

     virtual void  STDMETHODCALLTYPE    PreHeapMinimize();
     virtual void  STDMETHODCALLTYPE    PostHeapMinimize();
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __COMMALLOCSPY_H__
