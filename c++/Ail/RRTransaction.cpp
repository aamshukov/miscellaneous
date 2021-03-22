////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __AIL_H__
#   include <ail.hpp>
#endif

#ifndef __RR_TRANSACTION_INC__
#   include <RRTransaction.inc>
#endif

__BEGIN_NAMESPACE__
__BEGIN_RRT_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class Packet
// ----- ------
RRTransaction::Packet::Packet()
    : Priority(0), PacketID(0), TransactionID(0), DataSize(0), Data(null), Transaction(null)
{
}

RRTransaction::Packet::Packet(uint _priority, uint _p_id, uint _t_id, const byte* _data, uint _size, RRTransaction* _tr)
    : Priority(_priority), PacketID(_p_id), TransactionID(_t_id), DataSize(_size), Data(const_cast<byte*>(_data)), Transaction(_tr)
{
}

RRTransaction::Packet::Packet(const Packet& _other)
{
    operator = (_other);
}

RRTransaction::Packet::~Packet()
{
}

RRTransaction::Packet& RRTransaction::Packet::operator = (const RRTransaction::Packet& _other)
{
    if(this != &_other)
    {
        Priority      = _other.Priority;
        PacketID      = _other.PacketID;
        TransactionID = _other.TransactionID;
        DataSize      = _other.DataSize;
        Data          = _other.Data;

        if(_other.Transaction != null)
        {
            Transaction = _other.Transaction;
           _other.Transaction = null; // pass ownership
        }
    }
    return *this;
}

void RRTransaction::Packet::AssemblePacket(byte* _buffer)
{
    if(_buffer == null)
    {
        return;
    }
    //
    EndianOrder eo;

    eo.Arrange(_buffer+0, reinterpret_cast<const byte*>(&PacketID), sizeof(PacketID));
    eo.Arrange(_buffer+4, reinterpret_cast<const byte*>(&TransactionID), sizeof(TransactionID));
    eo.Arrange(_buffer+8, reinterpret_cast<const byte*>(&DataSize), sizeof(DataSize));

    memcpy(_buffer+12, Data, DataSize);
}

void RRTransaction::Packet::DisassemblePacket(byte* _buffer)
{
    if(_buffer == null)
    {
        return;
    }
    //
    EndianOrder eo;

    eo.Arrange(reinterpret_cast<byte*>(&PacketID), _buffer+0, sizeof(PacketID));
    eo.Arrange(reinterpret_cast<byte*>(&TransactionID), _buffer+4, sizeof(TransactionID));
    eo.Arrange(reinterpret_cast<byte*>(&TransactionID), _buffer+8, sizeof(DataSize));
    Data = _buffer+12;
}
////////////////////////////////////////////////////////////////////////////////////////
// class RRTransaction
// ----- -------------
RRTransaction::RRTransaction()
    : ID(0), Timestamp(Time::GetCurrentTime()), Size(0), Offset(0), RawData(null)
{
}

RRTransaction::RRTransaction(const RRTransaction& _other)
{
    if(this != &_other)
    {
        ID          = _other.ID;
        Timestamp   = _other.Timestamp;
        PacketSize  = _other.PacketSize;
        Size        = _other.Size;
        Offset      = _other.Offset;
        RawData     = new byte[Size];
        memcpy(RawData, _other.RawData, Size);
    }
}

RRTransaction::RRTransaction(const byte* _data, uint _size)
    : ID(0), Timestamp(Time::GetCurrentTime()), Size(_size), Offset(0), RawData(null)
{
    if(_data != null)
    {
        RawData = new byte[_size];
        memcpy(RawData, _data, _size);
    }
}

RRTransaction::~RRTransaction()
{
    if(RawData != null)
    {
        delete [] RawData, RawData = null;
    }
}

RRTransaction& RRTransaction::operator = (const RRTransaction& _other)
{
    if(this != &_other)
    {
        if(RawData != null)
        {
            delete [] RawData;
        }

        ID          = _other.ID;
        Timestamp   = _other.Timestamp;
        PacketSize  = _other.PacketSize;
        Size        = _other.Size;
        Offset      = _other.Offset;
        RawData     = new byte[Size];
        memcpy(RawData, _other.RawData, Size);
    }
    return *this;
}

void RRTransaction::UpdateRawData(ushort _offset, const byte* _data, ushort _size)
{
    if(_data == null)
    {
        return;
    }
    //
    STACK_BUFFER(_size, byte)
    //
    EndianOrder eo;
    eo.Arrange(buffer, _data, _size);
    memcpy(RawData+_offset, buffer, _size);
}

RRTransaction* RRTransaction::Clone(uint _id) const
{
    RRTransaction* t = RRMemManager::Instance().ConstructTransaction(*this);
    
    if(_id != 0)
    {
        t->SetID(_id);
    }
    return t;
}

int RRTransaction::PopPacket(RRTransaction::Packet* _packet)
{
    // default implementation,
    // which will have a transaction, except the big one
    if(_packet == null || RawData == null)
    {
        return 0; // discard
    }
    
    EndianOrder eo;

   _packet->Priority = GetPriority();

    uint tmp = Offset/RRTransaction::PacketSize;
    eo.Arrange(reinterpret_cast<byte*>(&_packet->PacketID), reinterpret_cast<const byte*>(&tmp), RRTransaction::PIDSize);

    eo.Arrange(reinterpret_cast<byte*>(&_packet->TransactionID), reinterpret_cast<const byte*>(&ID), RRTransaction::PTIDSize);

    tmp = Size-Offset >= RRTransaction::PacketSize ? RRTransaction::PacketSize : Size-Offset;
    eo.Arrange(reinterpret_cast<byte*>(&_packet->DataSize), reinterpret_cast<const byte*>(&tmp), RRTransaction::PSizeSize);

   _packet->Data        = RawData+Offset;
   _packet->Transaction = null;
    
    Offset += Size;

    if(Size-Offset <= RRTransaction::PacketSize)
    {
        // the last packet is responsible for deleting the transaction
       _packet->Transaction = this;
        Offset = 0;
        return 1; // complete
    }
    return 2; // continue
}

int RRTransaction::PushPacket(const RRTransaction::Packet* _packet)
{
    if(_packet == null)
    {
        return 0; // discard
    }

    EndianOrder eo;

    uint datasize;
    eo.Arrange(reinterpret_cast<byte*>(&datasize), reinterpret_cast<const byte*>(&_packet->DataSize), RRTransaction::PSizeSize);

    if(datasize > RRTransaction::PacketSize)
    {
        return 0; // discard
    }

    if(RawData == null)
    {
        // first packet initializes the transaction
        eo.Arrange(reinterpret_cast<byte*>(&ID), reinterpret_cast<const byte*>(&_packet->TransactionID), RRTransaction::PTIDSize);
        eo.Arrange(reinterpret_cast<byte*>(&Size), reinterpret_cast<const byte*>(&_packet->Data[0]), RRTransaction::TSizeSize);
        Offset += datasize;
        Timestamp = Time::GetCurrentTime();
        RawData   = new byte[datasize];
        memcpy(RawData, _packet->Data, datasize);
    }
    else
    {
        STACK_BUFFER(Offset+datasize, byte)
        memcpy(buffer, RawData, Offset);
        memcpy(buffer+Offset, _packet->Data, datasize);
        Offset += datasize;
    }

    if(Offset == Size)
    {
        // the transaction is complete, update offset
        Offset = 0;
        return 1; // complete
    }
    return 2; // continue
}
////////////////////////////////////////////////////////////////////////////////////////
// class NullTransaction
// ----- ---------------
NullTransaction::NullTransaction()
{
    Data[0] = '0';
    Data[1] = '0';
    Data[2] = '0';
    Data[3] = '0';
}

NullTransaction::~NullTransaction()
{
}
////////////////////////////////////////////////////////////////////////////////////////
__END_RRT_NAMESPACE__
__END_NAMESPACE__
