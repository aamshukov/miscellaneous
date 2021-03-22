////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __DATAGRAM_SOCKET_H__
#define __DATAGRAM_SOCKET_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class DatagramSocket
// ----- --------------
class __DECLSPEC__ DatagramSocket : public Socket
{
    private:
                        DatagramSocket(const DatagramSocket&);
     DatagramSocket&    operator = (const DatagramSocket&);
    public:
     // ctor/dtor
                        DatagramSocket();
     explicit           DatagramSocket(const IPv4Address&, const IPv4Address& = Socket::DummyIP);
     virtual           ~DatagramSocket();

     // protocol
     void               Create(bool = true, ushort = IPPROTO_IP);

     void               Connect(bool = true, int = 0, ushort = IPPROTO_IP);
     void               Disconnect();

     int                Send(const byte*, int, int = 0, int = 0);
     int                SendTo(const byte*, int, const IPv4Address&, int = 0, int = 0);

     int                Receive(byte*, int, int = 0, int = 0);
     int                ReceiveFrom(byte*, int, IPv4Address&, int = 0, int = 0);
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __DATAGRAM_SOCKET_H__
