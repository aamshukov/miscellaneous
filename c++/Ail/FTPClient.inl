////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __FTP_CLIENT_INL__
#define __FTP_CLIENT_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class FTPClient
// ----- ---------
__INLINE__ const FTPURL& FTPClient::GetProxyServer() const
{
    return ProxyServer;
}

__INLINE__ void FTPClient::SetProxyServer(const tchar* _proxy)
{
    ProxyServer = _proxy;
}

__INLINE__ const FTPURL& FTPClient::GetSOCKSServer() const
{
    return SOCKSServer;
}

__INLINE__ void FTPClient::SetSOCKSServer(const tchar* _socks)
{
    SOCKSServer = _socks;
}

__INLINE__ const FTPURL& FTPClient::GetResource() const
{
    return Resource;
}

__INLINE__ void FTPClient::SetResource(const tchar* _url)
{
    Resource = _url;
}

__INLINE__ String<> FTPClient::GetUsername() const
{
    return Username;
}

__INLINE__ void FTPClient::SetUsername(const String<>& _username)
{
    Username = _username;
}

__INLINE__ String<> FTPClient::GetPassword() const
{
    return Password;
}

__INLINE__ void FTPClient::SetPassword(const String<>& _password)
{
    Password = _password;
}

__INLINE__ String<> FTPClient::GetAccount() const
{
    return Account;
}

__INLINE__ void FTPClient::SetAccount(const String<>& _account)
{
    Account = _account;
}

__INLINE__ short FTPClient::GetSocksVersion() const
{
    return SocksVersion;
}

__INLINE__ void  FTPClient::SetSocksVersion(short _ver)
{
    SocksVersion = _ver;
}

__INLINE__ const StreamSocket& FTPClient::GetConnection() const
{
    return Connection;
}

__INLINE__ void FTPClient::Terminate()
{
    Terminated = true;
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __FTP_CLIENT_INL__
