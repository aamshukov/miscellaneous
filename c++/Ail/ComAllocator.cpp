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

#ifndef __COMALLOCATOR_INC__
#   include <ComAllocator.inc>
#endif

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class ComAllocator
// ----- ------------
ComAllocator::ComAllocator(bool _init) : Init(_init)
{
    HRESULT hr = ::CoGetMalloc(MEMCTX_TASK, &_Interface);

    if(FAILED(hr) || _Interface == null)
    {
        throw ComAllocator::XComAllocator(hr);
    }
}

ComAllocator::~ComAllocator()
{
}

ComAllocator& ComAllocator::GetComAllocator()
{
    static ComAllocator _allocator_;
    return _allocator_;
}

void* ComAllocator::Allocate(ulong count)
{
    Lock lock(this);

    if(count == 0)
    {
        throw ComAllocator::XComAllocator(E_INVALIDARG);
    }

    void* p = _Interface->Alloc(count);

    if(p == null)
    {
        throw ComAllocator::XComAllocator(E_OUTOFMEMORY);
    }

    if(Init)
    {
        InitMemory(p, count);
    }

    return p;
}

void* ComAllocator::Reallocate(void* _p, ulong count)
{
    Lock lock(this);

    if(count == 0 || IsAllocated(_p) < 1)
    {
        throw ComAllocator::XComAllocator(E_INVALIDARG);
    }

    void* p = _Interface->Realloc(_p, count);

    if(p == null)
    {
        throw ComAllocator::XComAllocator(E_OUTOFMEMORY);
    }

    if(Init)
    {
        InitMemory(p, count);
    }

    return p;
}

void ComAllocator::Free(void* _p)
{
    if(_p)
    {
        Lock lock(this);

        if(IsAllocated(_p) < 1)
        {
            throw ComAllocator::XComAllocator(E_INVALIDARG);
        }

        _Interface->Free(_p);

        _p = null;
    }
}

int ComAllocator::IsAllocated(void* _p)
{
    Lock lock(this);

    if(_p == null)
    {
        throw ComAllocator::XComAllocator(E_INVALIDARG);
    }

    // -1 - unknown, 0 - was not allocated by the Allocator, 1 - OK
    return _Interface->DidAlloc(_p);
}

ulong ComAllocator::GetSize(void* _p)
{
    Lock lock(this);

    if(IsAllocated(_p) < 1)
    {
        throw ComAllocator::XComAllocator(E_INVALIDARG);
    }

    return _Interface->GetSize(_p);
}

void ComAllocator::UpdateHeap()
{
    Lock lock(this);

    _Interface->HeapMinimize();
}

ComAllocator::XComAllocator::XComAllocator(HRESULT _hr) : XCOM(_hr)
{
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__
