////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __ALLOCATOR_INL__
#define __ALLOCATOR_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class Allocator
// ----- ---------
template <typename _Mutex, typename _Allocator> Allocator<_Mutex, _Allocator>::Allocator(uint _size, uint _count, uint _alignment, uint _flags, const tchar* _mutex_name, uint _timeout) : FreeList(null), Mutex(_mutex_name, _timeout), Chunks(KeyExtractor, Comparator)
{
    Chunks.SetState(StateObject::eNoDelete);
    //
    Flags     = _flags;
    SlotSize  = ALIGN(_size, 8);
    SlotCount = ALIGN(_count, _alignment);
}

template <typename _Mutex, typename _Allocator> Allocator<_Mutex, _Allocator>::~Allocator()
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    //
    register _Chunk* chunk;

    while((chunk = const_cast<_Chunk*>(reinterpret_cast<const _Chunk*>(Chunks.GetHead()))) != null)
    {
        Chunks.UnlinkHead();
        chunk->~_Chunk();
       _Allocator::Deallocate(chunk);
    }

    FreeList = null;
}

template <typename _Mutex, typename _Allocator> __INLINE_TEMPLATE__ uint Allocator<_Mutex, _Allocator>::GetFlags() const
{
    return Flags;
}

template <typename _Mutex, typename _Allocator> void* Allocator<_Mutex, _Allocator>::Allocate(uint)
{
    ////////////////////////////////////////////
    //  Schema:
    //      ------------------------------------
    //      | ---> |      |      |      |      |
    //      | <--  |      |      |      |      |
    //      | .... |->1   |->1   |->1   |->1   |
    //      ------------------------------------
    ////////////////////////////////////////////
    Synchronization::Guard<_Mutex> guard(Mutex);
    //
    if(FreeList != null)
    {
        register byte* p = FreeList+sizeof(pvoid);
        *(reinterpret_cast<address_t*>(FreeList)) |= Allocator::Mask; // mark as allocated
        FreeList = reinterpret_cast<byte*>(*(reinterpret_cast<address_t*>(FreeList)) & ~Allocator::Mask);
        return p;
    }
    else
    {
        // phase I (allocate)
        register uint    size  = sizeof(_Chunk)+(SlotSize+sizeof(pvoid))*SlotCount;
        register void*   pp    = _Allocator::Allocate(size);
        register _Chunk* chunk = new (pp) _Chunk();
        register byte*   p     = reinterpret_cast<byte*>(chunk)+sizeof(_Chunk);

        if(Flags & Allocator::ZeroFill)
        {
            InitMemory(p, (SlotSize+sizeof(pvoid))*SlotCount);
        }

        // phase II (link)
        for(register uint i = 0; i < SlotCount-1; i++)
        {
            *(reinterpret_cast<address_t*>(p+(SlotSize+sizeof(pvoid))*i)) = reinterpret_cast<address_t>(p+(SlotSize+sizeof(pvoid))*(i+1));
        }
        *(reinterpret_cast<address_t*>(p+(SlotSize+sizeof(pvoid))*i)) = 0;

        *(reinterpret_cast<address_t*>(p)) |= Allocator::Mask;  // mark as allocated
        p += sizeof(pvoid), FreeList = p+SlotSize;              // points to the next slot
        Chunks.LinkHead(chunk);
        return p;
    }
}

template <typename _Mutex, typename _Allocator> void Allocator<_Mutex, _Allocator>::Deallocate(void* _p)
{
    if(_p == null)
    {
        return;
    }
    //
    Synchronization::Guard<_Mutex> guard(Mutex);
    //
    *(reinterpret_cast<address_t*>(reinterpret_cast<byte*>(_p)-sizeof(pvoid))) &= ~Allocator::Mask; // mark as free
    *(reinterpret_cast<address_t*>(reinterpret_cast<byte*>(_p)-sizeof(pvoid)))  = reinterpret_cast<address_t>(FreeList == null ? 0 : FreeList); // link to head

    if(Flags & Allocator::ZeroFill)
    {
        InitMemory(_p, SlotSize);
    }

    FreeList = reinterpret_cast<byte*>(_p)-sizeof(pvoid);

    if(Flags & Allocator::FreeExtra)
    {
        Compact(); // time consume ! ...
    }
}

template <typename _Mutex, typename _Allocator> void Allocator<_Mutex, _Allocator>::Compact()
{
    if(FreeList != null)
    {
        Synchronization::Guard<_Mutex> guard(Mutex);
        //
        if(FreeList != null)
        {
            ListIterator<_Chunk, pvoid> iter(Chunks.GetHead());
            //
            for(; iter;)
            {
                // phase I (check chunk)
                register byte* p = reinterpret_cast<byte*>(&iter.Current())+sizeof(_Chunk);

                for(register uint i = 0, k = 0; i < SlotCount; i++, k++)
                {
                    if(*(reinterpret_cast<address_t*>(p+(SlotSize+sizeof(pvoid))*i)) & Allocator::Mask)
                    {
                        break;
                    }
                }

                if(k < SlotCount)
                {
                    ++iter;
                    continue;
                }

                // phase II (clean up FreeList)
                {
                    register byte* pslot = FreeList;
                    register byte* prev  = null;

                    while(pslot != null)
                    {
                        if(pslot >= p && pslot <= p+(SlotSize+sizeof(pvoid))*SlotCount)
                        {
                            if(pslot == FreeList)
                            {
                                FreeList = reinterpret_cast<byte*>(*(reinterpret_cast<address_t*>(pslot)));
                            }
                            else
                            {
                                *(reinterpret_cast<address_t*>(prev)) = *(reinterpret_cast<address_t*>(pslot));
                            }
                        }
                        
                        prev  = pslot;
                        pslot = reinterpret_cast<byte*>(*(reinterpret_cast<address_t*>(pslot)));
                    }
                }

                // phase III (release chunk)
                register _Chunk*    chunk   = &iter.Current();
                register _Chunk*    prev    = reinterpret_cast<_Chunk*>(chunk->Prev);
                register  address_t address = reinterpret_cast<address_t>(chunk); 
                
                Chunks.Unlink(chunk);
                chunk->~_Chunk();
               _Allocator::Deallocate(chunk);

                iter.Restart(prev == null ? Chunks.GetHead() : prev);

                if(reinterpret_cast<address_t>(iter.GetCurrentNode()) < address)
                {
                    // cut iteration
                    break;
                }
            }

            if(Chunks.GetCount() == 0)
            {
                FreeList = null;
            }
        }
    }
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __ALLOCATOR_INL__

