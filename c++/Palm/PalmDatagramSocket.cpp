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

#ifndef __PALM_DATAGRAM_SOCKET_INC__
#   include <PalmDatagramSocket.inc>
#endif

#ifdef __PALM_OS__

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class PalmDatagramSocket
// ----- ------------------
PalmDatagramSocket::PalmDatagramSocket()
{
}

PalmDatagramSocket::PalmDatagramSocket(const PalmIPv4& _remote_address, const PalmIPv4& _local_address)
                  : PalmSocket(_remote_address, _local_address)
{
}

PalmDatagramSocket::~PalmDatagramSocket()
{
    Disconnect();
}

void PalmDatagramSocket::Create(bool _bind, uint16 _timeout, int16 _proto)
{
    palmxassert(State != PalmSocket::eConnected, XPalmSocket::eInvalidState, PalmDatagramSocket::XPalmDatagramSocket);
    Socket = PalmSocketModule::CreateSocket(netSocketAddrINET, netSocketTypeDatagram, _proto);
    palmxassert(Socket != INVALID_SOCKET, Error::eOperationFailure, PalmDatagramSocket::XPalmDatagramSocket);

    uint16 flag = 1;
    palmxassert(PalmSocketModule::SetSocketOption(Socket, netSocketOptLevelSocket, netSocketOptSockReuseAddr, &flag, sizeof(flag)) == errNone, Error::eOperationFailure, PalmDatagramSocket::XPalmDatagramSocket);

    // for SOCKS bind could be ignored
    if(_bind)
    {
        palmxassert(PalmSocketModule::Bind(Socket, LocalAddress, LocalAddress.GetSize(), _timeout) == errNone, Error::eOperationFailure, PalmDatagramSocket::XPalmDatagramSocket);
    }
    //
    State = PalmSocket::eConnected;
}

void PalmDatagramSocket::Connect(bool _bind, uint16 _timeout, int16 _proto)
{
    palmxassert(State != PalmSocket::eConnected, XPalmSocket::eInvalidState, PalmDatagramSocket::XPalmDatagramSocket);
    Socket = PalmSocketModule::CreateSocket(netSocketAddrINET, netSocketTypeDatagram, _proto);
    palmxassert(Socket != INVALID_SOCKET, Error::eOperationFailure, PalmDatagramSocket::XPalmDatagramSocket);

    uint16 flag = 1;
    palmxassert(PalmSocketModule::SetSocketOption(Socket, netSocketOptLevelSocket, netSocketOptSockReuseAddr, &flag, sizeof(flag)) == errNone, Error::eOperationFailure, PalmDatagramSocket::XPalmDatagramSocket);

    // for SOCKS bind could be ignored
    if(_bind)
    {
        palmxassert(PalmSocketModule::Bind(Socket, LocalAddress, LocalAddress.GetSize(), _timeout) == errNone, Error::eOperationFailure, PalmDatagramSocket::XPalmDatagramSocket);
    }

    palmxassert(PalmSocketModule::Connect(Socket, RemoteAddress, RemoteAddress.GetSize(), _timeout) == errNone, Error::eOperationFailure, PalmDatagramSocket::XPalmDatagramSocket);

    int16 size = LocalAddress.GetSize();
    palmxassert(PalmSocketModule::GetSocketName(Socket, LocalAddress, size, _timeout) == errNone, Error::eOperationFailure, PalmDatagramSocket::XPalmDatagramSocket);
    //
    State = PalmSocket::eConnected;
}

void PalmDatagramSocket::Disconnect(int16, uint16 _timeout)
{
    if(State == PalmSocket::eConnected)
    {
        palmxassert(PalmSocketModule::CloseSocket(Socket, _timeout) == errNone, Error::eOperationFailure, PalmDatagramSocket::XPalmDatagramSocket);
        //
        State  = PalmSocket::eDisconnected;
        Socket = INVALID_SOCKET;
    }
}

int16 PalmDatagramSocket::Send(const byte* _data, uint16 _count, uint16 _timeout, uint16 _flags)
{
    palmxassert(State == PalmSocket::eConnected, XPalmSocket::eInvalidState, PalmDatagramSocket::XPalmDatagramSocket);
    palmxassert(_data != null && _count > 0, Error::eInvalidArg, PalmDatagramSocket::XPalmDatagramSocket);
    return PalmSocketModule::Send(Socket, const_cast<byte*>(_data), _count, _flags, null, _timeout);
}

int16 PalmDatagramSocket::SendTo(NetIOParamType& _io_param, uint16 _timeout, uint16 _flags)
{
    palmxassert(State == PalmSocket::eConnected, XPalmSocket::eInvalidState, PalmDatagramSocket::XPalmDatagramSocket);
    return PalmSocketModule::SendTo(Socket, _io_param, _flags, _timeout);
}

int16 PalmDatagramSocket::Receive(byte* _buffer, uint16 _count, uint16 _timeout, uint16 _flags)
{
    palmxassert(State == PalmSocket::eConnected, XPalmSocket::eInvalidState, PalmDatagramSocket::XPalmDatagramSocket);
    palmxassert(_buffer != null && _count > 0, Error::eInvalidArg, PalmDatagramSocket::XPalmDatagramSocket);
    return PalmSocketModule::Receive(Socket, _buffer, _count, _flags, null, _timeout);
}

int16 PalmDatagramSocket::ReceiveFrom(NetIOParamType& _io_param, uint16 _timeout, uint16 _flags)
{
    palmxassert(State == PalmSocket::eConnected, XPalmSocket::eInvalidState, PalmDatagramSocket::XPalmDatagramSocket);
    return PalmSocketModule::ReceiveFrom(Socket, _io_param, _flags, _timeout);
}
////////////////////////////////////////////////////////////////////////////////////////
// class XPalmDatagramSocket
// ----- -------------------
void PalmDatagramSocket::XPalmDatagramSocket::LoadErrorDescriptions()
{
    // base class
    XPalmSocket::LoadErrorDescriptions();
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__
