////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __RAW_SOCKET_H__
#define __RAW_SOCKET_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class RawSocket
// ----- ---------
class __DECLSPEC__ RawSocket : public DatagramSocket
{
    private:
                RawSocket(const RawSocket&);
     RawSocket& operator = (const RawSocket&);
    public:
     // ctor/dtor
                RawSocket();
     explicit   RawSocket(const IPv4Address&, const IPv4Address& = Socket::DummyIP);
     virtual   ~RawSocket();

     // protocol
     void       Create(bool = true, ushort = IPPROTO_IP);
     void       Connect(bool = true, int = 0, ushort = IPPROTO_IP);
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __RAW_SOCKET_H__
