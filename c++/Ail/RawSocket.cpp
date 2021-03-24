////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __AIL_H__
#   include <ail.hpp>
#endif

#ifndef __RAW_SOCKET_INC__
#   include <RawSocket.inc>
#endif

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class RawSocket
// ----- ---------
RawSocket::RawSocket()
{
}

RawSocket::RawSocket(const IPv4Address& _remote_address, const IPv4Address& _local_address)
         : DatagramSocket(_remote_address, _local_address)
{
}

RawSocket::~RawSocket()
{
    Disconnect();
}

void RawSocket::Create(bool _bind, ushort _proto)
{
    // if a raw socket is created with protocol of 0, and neither bind() nor connect() is called,
    // then that socket receives a copy of EVRY raw datagram that the kernel passes to raw sockets
    Socket::xxassert(*this, State != Socket::Connected);
    Socket::xxassert(*this, (Socket_ = SocketModule::CreateSocket(AF_INET, SOCK_RAW, _proto)) != INVALID_SOCKET);
    // for SOCKS bind could be ignored
    if(_bind)
    {
        Socket::xxassert(*this, SocketModule::Bind(Socket_, LocalAddress, LocalAddress.GetSize()) == 0);
    }
    //
    State = Socket::Connected;
}

void RawSocket::Connect(bool _bind, int, ushort _proto)
{
    Socket::xxassert(*this, State != Socket::Connected);
    Socket::xxassert(*this, (Socket_ = SocketModule::CreateSocket(AF_INET, SOCK_RAW, _proto)) != INVALID_SOCKET);
    // for SOCKS bind could be ignored
    if(_bind)
    {
        Socket::xxassert(*this, SocketModule::Bind(Socket_, LocalAddress, LocalAddress.GetSize()) == 0);
    }
    Socket::xxassert(*this, SocketModule::Connect(Socket_, RemoteAddress, sizeof(RemoteAddress.GetInetAddress())) == 0);
    //
    int size = LocalAddress.GetSize();
    Socket::xxassert(*this, SocketModule::GetSocketName(Socket_, LocalAddress, &size) == 0);
    //
    State = Socket::Connected;
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__
