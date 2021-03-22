////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PALM_SOCKET_INL__
#define __PALM_SOCKET_INL__

#pragma once

#ifdef __PALM_OS__

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class PalmSocket
// ----- ----------
__INLINE__ bool PalmSocket::IsConnected() const
{
    return State == PalmSocket::eConnected;
}

__INLINE__ PalmSocket::EState PalmSocket::GetState() const
{
    return State;
}

__INLINE__ void PalmSocket::SetState(PalmSocket::EState _state)
{
    State = _state;
}

__INLINE__ PalmIPv4& PalmSocket::GetLocalAddress() const
{
    return const_cast<PalmIPv4&>(LocalAddress);
}

__INLINE__ void PalmSocket::SetLocalAddress(const PalmIPv4& _address)
{
    LocalAddress = _address;
}

__INLINE__ PalmIPv4& PalmSocket::GetRemoteAddress() const
{
    return const_cast<PalmIPv4&>(RemoteAddress);
}

__INLINE__ void PalmSocket::SetRemoteAddress(const PalmIPv4& _address)
{
    RemoteAddress = _address;
}

__INLINE__ socket_t PalmSocket::GetSocket() const
{
    return Socket;
}

__INLINE__ void PalmSocket::SetSocket(socket_t _socket)
{
    Socket = _socket;
}

__INLINE__ PalmSocket::operator socket_t ()
{
    return Socket;
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__
#endif // __PALM_SOCKET_INL__
