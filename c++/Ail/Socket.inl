////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __SOCKET_INL__
#define __SOCKET_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class Socket
// ----- ------
__INLINE__ bool Socket::IsConnected() const
{
    return State == Socket::Connected;
}

__INLINE__ Socket::EState Socket::GetState() const
{
    return State;
}

__INLINE__ void Socket::SetState(Socket::EState _state)
{
    State = _state;
}

__INLINE__ IPv4Address& Socket::GetLocalAddress() const
{
    return const_cast<IPv4Address&>(LocalAddress);
}

__INLINE__ void Socket::SetLocalAddress(const IPv4Address& _address)
{
    LocalAddress = _address;
}

__INLINE__ IPv4Address& Socket::GetRemoteAddress() const
{
    return const_cast<IPv4Address&>(RemoteAddress);
}

__INLINE__ void Socket::SetRemoteAddress(const IPv4Address& _address)
{
    RemoteAddress = _address;
}

__INLINE__ SOCKET Socket::GetSocket() const
{
    return Socket_;
}

__INLINE__ void Socket::SetSocket(SOCKET _socket)
{
    Socket_ = _socket;
}

__INLINE__ Socket::operator SOCKET ()
{
    return Socket_;
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __SOCKET_INL__
