////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __RR_NET_MANAGER_H__
#define __RR_NET_MANAGER_H__

#pragma once

__BEGIN_NAMESPACE__
__BEGIN_RRT_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class RRNetManager
// ----- ------------
class __DECLSPEC__ RRNetManager : public ListNodeBase<RRNetManager, IPv4Address>, ObjectRef<>
{
    public:

    enum ESide
    {
        ClientSide = 1,
        ServerSide = 10
    };

    template <typename _T, typename _Key> struct KeyExtractor
    {
        const _Key& operator () (const _T& _val) const { return _val.GetKey(); }
    };

    template <typename _Key> struct Comparator
    {
        int operator () (const _Key& _k1, const _Key& _k2) const { return _k1 < _k2 ? -1 : _k1 > _k2 ? 1 : 0; }
    };
    //
    typedef KeyExtractor<RRTransaction::Packet, uint>                                             _KeyExtractor;
    typedef Comparator<uint>                                                                      _Comparator;
    typedef Synchronization::NullThreadMutex<>                                                    _NullMutex;
    typedef Synchronization::ThreadMutex<>                                                        _Mutex;
    typedef Synchronization::ETrigger                                                             _Trigger;
    typedef Allocator<_NullMutex, StandardAllocator>                                              _Allocator;
    typedef BinaryHeap<RRTransaction::Packet, uint, _KeyExtractor, _Comparator, true, _NullMutex> _PQ;

    class __DECLSPEC__ RRSender : public Thread
    {
        private:
         RRNetManager&  Manager;
        protected:
         virtual int    Run();
        public:
         // ctor/dtor
                        RRSender(RRNetManager&);
                       ~RRSender();
    };

    class __DECLSPEC__ RRReceiver : public Thread
    {
        private:
         RRNetManager&  Manager;
        protected:
         virtual int    Run();
        public:
         // ctor/dtor
                        RRReceiver(RRNetManager&);
                       ~RRReceiver();
    };

    friend class RRSender;
    friend class RRReceiver;

    private:
     byte               Key[64]; // 32 username + 31 password + 1 for '0'
     ushort             Interleave;
     uint               Timeout;
     ESide              Side;

     StreamSocket       Connection;

    _Allocator          Allocator;
    _KeyExtractor       KeyExtractor;
    _Comparator         Comparator;
    _PQ                 PQ; // holds out packets
     
    _Mutex              Mutex;
    _Mutex              SMutex;
    _Mutex              RMutex;
    _Trigger            STrigger;
    _Trigger            RTrigger;

     Decoder            Decoder_;

     RRSender           Sender;
     RRReceiver         Receiver;
    private:
                        RRNetManager(const RRNetManager&);
     RRNetManager&      operator = (const RRNetManager&);
     //
     const byte*        GetKeyData()            const;
    protected:
     virtual uint       AddReference();
     virtual uint       ReleaseReference();
    public:
     // ctor/dtor
                        RRNetManager();
                        RRNetManager(const IPv4Address&);
     virtual           ~RRNetManager();

     // access
     const IPv4Address& GetKey()                const;

     bool               IsClientSide()          const;
     StreamSocket&      GetConnection()         const;

     uint               GetTimeout()            const;
     void               SetTimeout(uint);

     ushort             GetInterleave()         const;
     void               SetInterleave(ushort);

     // protocol
     void               Connect();
     void               QueuePacket(const RRTransaction::Packet*);
};
////////////////////////////////////////////////////////////////////////////////////////
__END_RRT_NAMESPACE__
__END_NAMESPACE__

#endif // __RR_NET_MANAGER_H__
