////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PING_H__
#define __PING_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class Ping
// ----- ----
class __DECLSPEC__ Ping
{
    private:
    
    enum EConst
    {
        MinPacketSize = 32,
        MaxPacketSize = 1024,
        DefQueries    = 5
    };

    // the ip header
    class IpHeader
    {
        public:
         uint   HeaderCount:4;  // size of the header
         uint   Version:4;      // version of IP
         byte   Tos;            // type of service
         ushort TotalCount;     // total length of the packet
         ushort Id;             // unique identifier
         ushort Flags;          // flags
         byte   TTL;            // time to live
         byte   Protocol;       // protocol (TCP, UDP etc)
         ushort Checksum;       // IP checksum
         uint   SrcIP;
         uint   DstIP;
        public:
         // ctor/dtor
         IpHeader();
    };

    // ICMP header
    struct IcmpHeader
    {
        public:
         byte   Type;
         byte   Code;       // type sub code
         ushort Checksum;
         ushort Id;
         ushort SeqNumber;
         ulong  Timestamp;  // optional data - timestamp
        public:
         // ctor/dtor
         IcmpHeader();
    };

    private:
     RawSocket          Connection;
    protected:
     ushort             Checksum(ushort*, int);
    public:
     // ctor/dtor
                        Ping();
                       ~Ping();

     // access
     const RawSocket&   GetConnection() const;

     // protocol
     void               DoPing(const IPv4Address&, ushort = Ping::MinPacketSize, ushort = Ping::DefQueries);
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PING_H__
