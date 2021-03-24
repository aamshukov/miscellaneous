////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __RR_TRANSACTION_INL__
#define __RR_TRANSACTION_INL__

#pragma once

__BEGIN_NAMESPACE__
__BEGIN_RRT_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class Packet
// ----- ------
__INLINE__ uint& RRTransaction::Packet::GetKey() const
{
    return (uint&)Priority;
}

__INLINE__ uint RRTransaction::Packet::GetPacketID() const
{
    return PacketID;
}

__INLINE__ uint RRTransaction::Packet::GetTransactionID() const
{
    return TransactionID;
}

__INLINE__ uint RRTransaction::Packet::GetDataSize() const
{
    return DataSize;
}

__INLINE__ uint RRTransaction::Packet::GetPacketSize() const
{
    return sizeof(PacketID)+sizeof(TransactionID)+DataSize;
}

__INLINE__ const byte* RRTransaction::Packet::GetData() const
{
    return Data;
}
////////////////////////////////////////////////////////////////////////////////////////
// class RRTransaction
// ----- -------------
__INLINE__ uint& RRTransaction::GetKey() const
{
    return (uint&)ID;
}

__INLINE__ uint RRTransaction::GetID() const
{
    return ID;
}

__INLINE__ void RRTransaction::SetID(uint _id)
{
    ID = _id;
    UpdateRawData(RRTransaction::IDOffset, reinterpret_cast<byte*>(&ID), sizeof(ID));
}

__INLINE__ Time RRTransaction::GetTimestamp() const
{
    return Timestamp;
}

__INLINE__ uint RRTransaction::GetPaketSize() const
{
    return PacketSize;
}

__INLINE__ uint RRTransaction::GetSize() const
{
    return Size;
}

__INLINE__ uint RRTransaction::GetOffset() const
{
    return Offset;
}

__INLINE__ const byte* RRTransaction::GetRawData() const
{
    return RawData;
}

__INLINE__ bool RRTransaction::IsValid() const
{
    return false;
}

__INLINE__ ushort RRTransaction::GetPriority() const
{
    return RRTransaction::NormalPriority; // default
}
////////////////////////////////////////////////////////////////////////////////////////
// class NullTransaction
// ----- ---------------
__INLINE__ const byte* NullTransaction::GetData() const
{
    return reinterpret_cast<const byte*>(&Data);
}
////////////////////////////////////////////////////////////////////////////////////////
__END_RRT_NAMESPACE__
__END_NAMESPACE__

#endif // __RR_TRANSACTION_INL__
