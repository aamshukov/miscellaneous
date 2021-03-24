////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __BROADCAST_SOCKET_H__
#define __BROADCAST_SOCKET_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class BroadcastSocket
// ----- ---------------
class __DECLSPEC__ BroadcastSocket : public DatagramSocket
{
    private:
                        BroadcastSocket(const BroadcastSocket&);
     BroadcastSocket&   operator = (const BroadcastSocket&);
    public:
     // ctor/dtor
                        BroadcastSocket();
     explicit           BroadcastSocket(const IPv4Address&, const IPv4Address& = Socket::DummyIP);
     virtual           ~BroadcastSocket();

     // protocol
     void               Create(bool = true, ushort = IPPROTO_IP);
     void               Connect(bool = true, int = 0, ushort = IPPROTO_IP);
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __BROADCAST_SOCKET_H__
