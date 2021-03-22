////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __INET_CONNECTION_INL__
#define __INET_CONNECTION_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class InetConnection
// ----- --------------
__INLINE__ const tchar* InetConnection::GetUsername() const
{
    return Username;
}

__INLINE__ void InetConnection::SetUsername(const tchar* _username)
{
    Username = StrClone(_username);
}

__INLINE__ const tchar* InetConnection::GetPassword() const
{
    return Password;
}

__INLINE__ void InetConnection::SetPassword(const tchar* _password)
{
    Password = StrClone(_password);
}

__INLINE__ const tchar* InetConnection::GetProxy() const
{
    return Proxy;
}

__INLINE__ void InetConnection::SetProxy(const tchar* _proxy)
{
    Proxy = StrClone(_proxy);
}

__INLINE__ const tchar* InetConnection::GetSocks() const
{
    return Socks;
}

__INLINE__ void InetConnection::SetSocks(const tchar* _socks)
{
    Socks = StrClone(_socks);
}

__INLINE__ short InetConnection::GetSocksVer() const
{
    return SocksVer;
}

__INLINE__ void InetConnection::SetSocksVer(short _ver)
{
    SocksVer = _ver;
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __INET_CONNECTION_INL__
