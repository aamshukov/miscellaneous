////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __RR_DISPATCHER_H__
#define __RR_DISPATCHER_H__

#pragma once

__BEGIN_NAMESPACE__
__BEGIN_RRT_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class RRDispatcher
// ----- ------------
class __DECLSPEC__ RRDispatcher : public Singleton<RRDispatcher>
{
    class DEntry : public ListNodeBase<DEntry, uint>
    {
        public:
         const RRTransaction*   Transaction;
         const RRNetManager*    Manager;
        public:
         // ctor/dtor
                                DEntry();
                                DEntry(const DEntry&);
                                DEntry(const RRTransaction*, const RRNetManager*);

         // operator
         DEntry&                operator = (const DEntry&);

         // access
         uint&                  GetKey()    const;
    };

    template <typename _T, typename _Key> struct KeyExtractor
    {
        const _Key& operator () (const _T& _val) const { return _val.GetKey(); }
    };

    template <typename _Key> struct Comparator
    {
        int operator () (const _Key& _k1, const _Key& _k2) const { return _k1 < _k2 ? -1 : _k1 > _k2 ? 1 : 0; }
    };

    template <typename _Key> struct Comparator2
    {
        int operator () (const _Key& _k1, const _Key& _k2) const { return _k1.GetIPv4Address() == _k2.GetIPv4Address() && _k1.GetPort() == _k2.GetPort() ? 0 : -1; }
    };
    //
    typedef Synchronization::NullThreadMutex<>                                          _NullMutex;
    typedef Synchronization::ThreadMutex<>                                              _Mutex;
    typedef Synchronization::ETrigger                                                   _Trigger;
    typedef Allocator<_NullMutex, StandardAllocator>                                    _Allocator;

    typedef RRDispatcher::KeyExtractor<DEntry, uint>                                    _DKeyExtractor;
    typedef RRDispatcher::Comparator<uint>                                              _DComparator;
    typedef List<DEntry, uint, _DKeyExtractor, _DComparator, _NullMutex>                _DList;

    typedef RRTransaction::Packet::KeyExtractor<RRTransaction::Packet, uint>            _PKeyExtractor;
    typedef RRTransaction::Packet::Comparator<uint>                                     _PComparator;
    typedef List<RRTransaction::Packet, uint, _PKeyExtractor, _PComparator, _NullMutex> _PList;

    typedef RRTransaction::KeyExtractor<RRTransaction, uint>                            _TKeyExtractor;
    typedef RRTransaction::Comparator<uint>                                             _TComparator;
    typedef AVLTree<RRTransaction, uint, _TKeyExtractor, _TComparator, _NullMutex>      _TTree;

    typedef RRDispatcher::KeyExtractor<RRNetManager, IPv4Address>                       _NKeyExtractor;
    typedef RRDispatcher::Comparator2<IPv4Address>                                      _NComparator;
    typedef List<RRNetManager, IPv4Address, _NKeyExtractor, _NComparator, _NullMutex>   _NList;

    typedef Array<RRManager*, _NullMutex>                                               _Array;
    //
    class DSender : public Thread
    {
        protected:
         virtual int    Run();
        public:
         // ctor/dtor
                        DSender();
                       ~DSender();
    };
    
    class DReceiver : public Thread
    {
        protected:
         virtual int    Run();
        public:
         // ctor/dtor
                        DReceiver();
                       ~DReceiver();
    };

    friend class DSender;
    friend class DReceiver;

    private:
     ushort         Interleave;

    _Allocator      DAllocator;
    _DKeyExtractor  DKeyExtractor;
    _DComparator    DComparator;

    _PKeyExtractor  PKeyExtractor;
    _PComparator    PComparator;

    _TKeyExtractor  TKeyExtractor;
    _TComparator    TComparator;

    _DList          OutQueue;           // holds out transactions
    _PList          InQueue;            // holds in transactions
    _TTree          TransQueue;         // transaction queue

    _NKeyExtractor  NKeyExtractor;
    _NComparator    NComparator;
    _NList          NetManagers;        // holds network connections
     uint           MaxConnections;     // how many connections are open

    _Array          Managers;           // holds chat, ft, message, news managers

    _Mutex          Mutex;              // dispatcher mutex
    _Mutex          SMutex;             // sender mutex
    _Mutex          RMutex;             // receiver mutex

    _Trigger        STrigger;     
    _Trigger        RTrigger;     

     DSender        Sender;
     DReceiver      Receiver;
    private:
                    RRDispatcher(const RRDispatcher&);
     RRDispatcher&  operator = (const RRDispatcher&);
    protected:
     void           Register(RRManager*);
     void           Unregister(RRManager*);
    public:
     // ctor/dtor
                    RRDispatcher();
                   ~RRDispatcher();

     // access
     ushort         GetInterleave()             const;
     void           SetInterleave(ushort);

     uint           GetConnectionCount()        const;
     uint           GetMaxConnections()         const;
     void           SetMaxConnections(uint);

     // protocol
     void           QueueTransaction(const RRTransaction*, const RRNetManager*);
     void           QueuePacket(const RRTransaction::Packet*);

     void           RegisterNetManager(RRNetManager*);
     void           UnregisterNetManager(RRNetManager*);

     void           CleanUp();
};
////////////////////////////////////////////////////////////////////////////////////////
__END_RRT_NAMESPACE__
__END_NAMESPACE__

#endif // __RR_DISPATCHER_H__
