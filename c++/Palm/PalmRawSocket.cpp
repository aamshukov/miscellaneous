////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  Copyright © 1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __AIL_H__
#   include <ail.hpp>
#endif

#ifndef __PALM_RAW_SOCKET_INC__
#   include <PalmRawSocket.inc>
#endif

#ifdef __PALM_OS__

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class PalmRawSocket
// ----- -------------
PalmRawSocket::PalmRawSocket()
{
}

PalmRawSocket::PalmRawSocket(const PalmIPv4& _remote_address, const PalmIPv4& _local_address)
             : PalmDatagramSocket(_remote_address, _local_address)
{
}

PalmRawSocket::~PalmRawSocket()
{
    Disconnect();
}

void PalmRawSocket::Create(bool _bind, uint16 _timeout, int16 _proto)
{
    // if a raw socket is created with protocol of 0, and neither bind() nor connect() is called,
    // then that socket receives a copy of EVRY raw datagram that the kernel passes to raw sockets
    palmxassert(State != PalmSocket::eConnected, XPalmSocket::eInvalidState, PalmRawSocket::XPalmRawSocket);
    Socket = PalmSocketModule::CreateSocket(netSocketAddrINET, netSocketTypeRaw, _proto);
    palmxassert(Socket != INVALID_SOCKET, Error::eOperationFailure, PalmRawSocket::XPalmRawSocket);

    uint16 flag = 1;
    palmxassert(PalmSocketModule::SetSocketOption(Socket, netSocketOptLevelSocket, netSocketOptSockReuseAddr, &flag, sizeof(flag)) == errNone, Error::eOperationFailure, PalmRawSocket::XPalmRawSocket);

    // for SOCKS bind could be ignored
    if(_bind)
    {
        palmxassert(PalmSocketModule::Bind(Socket, LocalAddress, LocalAddress.GetSize(), _timeout) == errNone, Error::eOperationFailure, PalmRawSocket::XPalmRawSocket);
    }
    //
    State = PalmSocket::eConnected;
}

void PalmRawSocket::Connect(bool _bind, uint16 _timeout, int16 _proto)
{
    palmxassert(State != PalmSocket::eConnected, XPalmSocket::eInvalidState, PalmRawSocket::XPalmRawSocket);
    Socket = PalmSocketModule::CreateSocket(netSocketAddrINET, netSocketTypeRaw, _proto);
    palmxassert(Socket != INVALID_SOCKET, Error::eOperationFailure, PalmRawSocket::XPalmRawSocket);

    uint16 flag = 1;
    palmxassert(PalmSocketModule::SetSocketOption(Socket, netSocketOptLevelSocket, netSocketOptSockReuseAddr, &flag, sizeof(flag)) == errNone, Error::eOperationFailure, PalmRawSocket::XPalmRawSocket);

    // for SOCKS bind could be ignored
    if(_bind)
    {
        palmxassert(PalmSocketModule::Bind(Socket, LocalAddress, LocalAddress.GetSize(), _timeout) == errNone, Error::eOperationFailure, PalmRawSocket::XPalmRawSocket);
    }

    palmxassert(PalmSocketModule::Connect(Socket, RemoteAddress, RemoteAddress.GetSize(), _timeout) == errNone, Error::eOperationFailure, PalmRawSocket::XPalmRawSocket);

    int16 size = LocalAddress.GetSize();
    palmxassert(PalmSocketModule::GetSocketName(Socket, LocalAddress, size, _timeout) == errNone, Error::eOperationFailure, PalmRawSocket::XPalmRawSocket);
    //
    State = PalmSocket::eConnected;
}
////////////////////////////////////////////////////////////////////////////////////////
// class XPalmRawSocket
// ----- --------------
void PalmRawSocket::XPalmRawSocket::LoadErrorDescriptions()
{
    // base class
    XPalmRawSocket::LoadErrorDescriptions();
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__
