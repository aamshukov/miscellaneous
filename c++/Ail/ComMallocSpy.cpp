////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __AIL_H__
#   include <ail.hpp>
#endif

#ifndef __COMMALLOCSPY_INC__
#   include <ComMallocSpy.inc>
#endif

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class ComMallocSpyImp
// ----- ---------------
ComMallocSpyImp::ComMallocSpyImp()
{
}

ComMallocSpyImp::~ComMallocSpyImp()
{
}

ulong ComMallocSpyImp::AddRef()
{
    Lock lock(this);
    return ++Reference;
}

ulong ComMallocSpyImp::Release()
{
    Lock lock(this);

    if(--Reference == 0)
    {
        delete this;
        return 0;
    }

    return Reference;
}

HRESULT ComMallocSpyImp::QueryInterface(const IID& iid, void** _pp)
{
    Lock lock(this);

    if(_pp)
    {
        *_pp = null;

        if(iid == IID_IUnknown)
        {
            *_pp = static_cast<IMallocSpy*>(this);
        }
        else if(iid == IID_IMallocSpy)
        {
            *_pp = static_cast<IMallocSpy*>(this);
        }
        else
        {
            return ResultFromScode(E_NOINTERFACE);
        }

        reinterpret_cast<IUnknown*>(*_pp)->AddRef();

        return NOERROR;
    }

    return ResultFromScode(E_INVALIDARG);
}

ulong ComMallocSpyImp::PreAlloc(ulong count)
{
    // do nothing
    return count;
}

void* ComMallocSpyImp::PostAlloc(void* _p)
{
    // do nothing
    return _p;
}

void* ComMallocSpyImp::PreFree(void* _p, BOOL)
{
    // do nothing
    return _p;
}

void ComMallocSpyImp::PostFree(BOOL)
{
    // do nothing
}

ulong ComMallocSpyImp::PreRealloc(void*, ulong count, void**, BOOL)
{
    // do nothing
    return count;
}

void* ComMallocSpyImp::PostRealloc(void* _p, BOOL)
{
    // do nothing
    return _p;
}

void* ComMallocSpyImp::PreGetSize(void* _p, BOOL)
{
    // do nothing
    return _p;
}

ulong ComMallocSpyImp::PostGetSize(ulong count, BOOL)
{
    // do nothing
    return count;
}

void* ComMallocSpyImp::PreDidAlloc(void* _p, BOOL)
{
    // do nothing
    return _p;
}

int ComMallocSpyImp::PostDidAlloc(void*, BOOL, int _int)
{
    // do nothing
    return _int;
}

void ComMallocSpyImp::PreHeapMinimize()
{
    // do nothing
}

void ComMallocSpyImp::PostHeapMinimize()
{
    // do nothing
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__
