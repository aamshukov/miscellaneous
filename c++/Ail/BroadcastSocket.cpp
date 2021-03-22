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

#ifndef __BROADCAST_SOCKET_INC__
#   include <BroadcastSocket.inc>
#endif

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class BroadcastSocket
// ----- ---------------
BroadcastSocket::BroadcastSocket()
{
}

BroadcastSocket::BroadcastSocket(const IPv4Address& _remote_address, const IPv4Address& _local_address)
               : DatagramSocket(_remote_address, _local_address)
{
}

BroadcastSocket::~BroadcastSocket()
{
    Disconnect();
}

void BroadcastSocket::Create(bool _bind, ushort _proto)
{
    DatagramSocket::Create(_bind, _proto);
    //
    int on = 1;
    SetOptions(SOL_SOCKET, SO_BROADCAST, reinterpret_cast<byte*>(&on), sizeof(on));
}

void BroadcastSocket::Connect(bool _bind, int _timeout, ushort _proto)
{
    DatagramSocket::Connect(_bind, _timeout, _proto);
    //
    int on = 1;
    SetOptions(SOL_SOCKET, SO_BROADCAST, reinterpret_cast<byte*>(&on), sizeof(on));
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__
