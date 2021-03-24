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

#ifndef __RR_MEM_MANAGER_INC__
#   include <RRMemManager.inc>
#endif

__BEGIN_NAMESPACE__
__BEGIN_RRT_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class RRMemManager
// ----- ------------
RRMemManager::RRMemManager()
            : PAllocator(sizeof(RRTransaction::Packet), 32, 8),
              TAllocator(sizeof(RRTransaction), 16, 8)
{
}

RRMemManager::~RRMemManager()
{
}

RRTransaction::Packet* RRMemManager::ConstructPacket()
{
    void* p = PAllocator.Allocate(sizeof(RRTransaction::Packet));
    RRTransaction::Packet* packet = new (p) RRTransaction::Packet();
    return packet;
}

RRTransaction::Packet* RRMemManager::ConstructPacket(const RRTransaction::Packet& _packet)
{
    void* p = PAllocator.Allocate(sizeof(RRTransaction::Packet));
    RRTransaction::Packet* packet = new (p) RRTransaction::Packet(_packet);
    return packet;
}

void RRMemManager::DestroyPacket(RRTransaction::Packet* _p)
{
    if(_p == null)
    {
        return;
    }

   _p->~Packet();
    PAllocator.Deallocate(_p);
}

RRTransaction* RRMemManager::ConstructTransaction()
{
    void* p = TAllocator.Allocate(sizeof(RRTransaction));
    RRTransaction* transaction = new (p) RRTransaction();
    return transaction;
}

RRTransaction* RRMemManager::ConstructTransaction(const RRTransaction& _transaction)
{
    void* p = TAllocator.Allocate(sizeof(RRTransaction));
    RRTransaction* transaction = new (p) RRTransaction(_transaction);
    return transaction;
}

void RRMemManager::DestroyTransaction(RRTransaction* _p)
{
    if(_p == null)
    {
        return;
    }

   _p->~RRTransaction();
    TAllocator.Deallocate(_p);
}
////////////////////////////////////////////////////////////////////////////////////////
__END_RRT_NAMESPACE__
__END_NAMESPACE__
