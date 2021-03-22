////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __RR_MEM_MANAGER_H__
#define __RR_MEM_MANAGER_H__

#pragma once

__BEGIN_NAMESPACE__
__BEGIN_RRT_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class RRMemManager
// ----- ------------
class __DECLSPEC__ RRMemManager : public Singleton<RRMemManager>
{
    typedef RRTransaction::Packet::KeyExtractor<RRTransaction::Packet, uint>    _PKeyExtractor;
    typedef RRTransaction::Packet::Comparator<uint>                             _PComparator;
    typedef RRTransaction::KeyExtractor<RRTransaction, uint>                    _TKeyExtractor;
    typedef RRTransaction::Comparator<uint>                                     _TComparator;
    typedef Synchronization::NullThreadMutex<>                                  _NullMutex;
    typedef Synchronization::ThreadMutex<>                                      _Mutex;
    typedef Allocator<_NullMutex, StandardAllocator>                            _Allocator;

    private:
    _Allocator              PAllocator;
    _PKeyExtractor          PKeyExtractor;
    _PComparator            PComparator;

    _Allocator              TAllocator;
    _TKeyExtractor          TKeyExtractor;
    _TComparator            TComparator;
    public:
     // ctor/dtor
                            RRMemManager();
                           ~RRMemManager();
     // protocol
     RRTransaction::Packet* ConstructPacket();
     RRTransaction::Packet* ConstructPacket(const RRTransaction::Packet&);
     void                   DestroyPacket(RRTransaction::Packet*);

     RRTransaction*         ConstructTransaction();
     RRTransaction*         ConstructTransaction(const RRTransaction&);
     void                   DestroyTransaction(RRTransaction*);
};
////////////////////////////////////////////////////////////////////////////////////////
__END_RRT_NAMESPACE__
__END_NAMESPACE__

#endif // __RR_MEM_MANAGER_H__
