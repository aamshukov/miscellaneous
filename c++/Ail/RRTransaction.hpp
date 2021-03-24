////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __RR_TRANSACTION_H__
#define __RR_TRANSACTION_H__

#pragma once

//
#define __BEGIN_RRT_NAMESPACE__ namespace rrt {
#define __END_RRT_NAMESPACE__   }
//

__BEGIN_NAMESPACE__
__BEGIN_RRT_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class RRTransaction - request response transaction
// ----- ------------- - ------- -------- -----------
class __DECLSPEC__ RRTransaction : public TreeNodeBase<RRTransaction, uint>
{
    //////////////////////////////////////////////////////////
    // syntax is as follows:
    //  ------------------------------------------------------
    //  | id = 4 | type = 2 | err = 2 | size = 4 | flags = 4 |
    //  ------------------------------------------------------
    //  |                   ... data ...                     |
    //  ------------------------------------------------------
    //////////////////////////////////////////////////////////
    public:

    friend class RRManager;

    enum EConst
    {
        // header
        IDOffset    = 0,
        TypeOffset  = 4,
        ErrorOffset = 6,
        SizeOffset  = 8,
        FlagsOffset = 12,
        
        // packet
        MinPacketSize = 16,   // header+4
        MaxPacketSize = 1436, // header+1424

        // 
        TIDSize     = 4,
        TTypeSize   = 2,
        TErrSize    = 2,
        TSizeSize   = 4,
        TFlagsSize  = 4,

        PIDSize     = 4,
        PTIDSize    = 4,
        PSizeSize   = 4,
    };

    enum EPriority
    {
        LowPriority     = 10,   // file transfer
        NormalPriority  = 100,  // chat, message, news and so on
        HighPriority    = 1000  // urgent data, by symbol chat for ex.
    };

    enum EMessage
    {
        WM_NetworkError = WM_USER+0x1234, // or 0x4321
        WM_OutOfMemory,
        WM_DispatcherError,
    };

    class Packet : public ListNodeBase<Packet, uint>, public TreeNodeBase<Packet, uint>
    {
        //////////////////////////////////////
        // syntax is as follows:
        //  ----------------------------------
        //  | p_id = 4 | t_id = 4 | size = 4 |
        //  ----------------------------------
        //  |          ... data ...          | 
        //  ----------------------------------
        //////////////////////////////////////
        public:

        template <typename _T, typename _Key> struct KeyExtractor
        {
            const _Key& operator () (const _T& _val) const { return _val.GetKey(); }
        };

        template <typename _Key> struct Comparator
        {
            int operator () (const _Key& _k1, const _Key& _k2) const { return _k1 < _k2 ? -1 : _k1 > _k2 ? 1 : 0; }
        };

        friend class RRTransaction;

        private:
         uint                   Priority;       // key
         uint                   PacketID;       // Packet id
         uint                   TransactionID;  // transaction id
         uint                   DataSize;       // data size = packet size - packet's header size
         byte*                  Data;           // part of a transaction, DO NOT own
         mutable RRTransaction* Transaction;    // if not zero - delete, the last packet of the transaction will delete it
        public:
         // ctor/dtor
                                Packet();
                                Packet(uint, uint, uint, const byte*, uint, RRTransaction* = null);
                                Packet(const Packet&);
                               ~Packet();

         // operator
         Packet&                operator = (const Packet&);

         // access
         uint&                  GetKey()            const;
         uint                   GetPacketID()       const;
         uint                   GetTransactionID()  const;
         uint                   GetDataSize()       const;
         uint                   GetPacketSize()     const;
         const byte*            GetData()           const;

         // protocol
         void                   AssemblePacket(byte*);
         void                   DisassemblePacket(byte*);
    };

    template <typename _T, typename _Key> struct KeyExtractor
    {
        const _Key& operator () (const _T& _val) const { return _val.GetKey(); }
    };

    template <typename _Key> struct Comparator
    {
        int operator () (const _Key& _k1, const _Key& _k2) const { return _k1 < _k2 ? -1 : _k1 > _k2 ? 1 : 0; }
    };

    private:
     uint               ID;         // transaction id
     Time               Timestamp;  // create time stamp
     uint               PacketSize; // size of the packet = packet header + data size
     uint               Size;       // size of the transaction header+data
     uint               Offset;     // offset for splitting
     byte*              RawData;    // raw data any numbers are in network format
    protected:
     void               UpdateRawData(ushort, const byte*, ushort);
    public:
     // ctor/dtor
                        RRTransaction();
                        RRTransaction(const RRTransaction&);
                        RRTransaction(const byte*, uint);
     virtual           ~RRTransaction();

     // operator
     RRTransaction&     operator = (const RRTransaction&);

     // access
     virtual bool       IsValid()                   const;
     virtual ushort     GetPriority()               const;

     uint&              GetKey()                    const;
     uint               GetID()                     const;
     void               SetID(uint);

     Time               GetTimestamp()              const;
     uint               GetPaketSize()              const;
     uint               GetSize()                   const;
     uint               GetOffset()                 const;
     const byte*        GetRawData()                const;

     // protocol
     RRTransaction*     Clone(uint)                 const;

     virtual int        PopPacket(RRTransaction::Packet*);
     virtual int        PushPacket(const RRTransaction::Packet*);
};
////////////////////////////////////////////////////////////////////////////////////////
// class NullTransaction
// ----- ---------------
class __DECLSPEC__ NullTransaction : public RRTransaction
{
    private:
     byte           Data[4]; // contains "0000"
    public:
     // ctor/dtor
                    NullTransaction();
     virtual       ~NullTransaction();

     // access
     const byte*    GetData()   const;
};
////////////////////////////////////////////////////////////////////////////////////////
__END_RRT_NAMESPACE__
__END_NAMESPACE__

#endif // __RR_TRANSACTION_H__
