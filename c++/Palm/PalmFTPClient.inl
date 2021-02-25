////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PALM_FTP_CLIENT_INL__
#define __PALM_FTP_CLIENT_INL__

#ifdef __PALM_OS__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class FTPClient
// ----- ---------
__INLINE__ const FTPURL& FTPClient::GetProxyServer() const
{
    return ProxyServer;
}

__INLINE__ void FTPClient::SetProxyServer(const char* _proxy)
{
    ProxyServer = _proxy;
}

__INLINE__ const FTPURL& FTPClient::GetSOCKSServer() const
{
    return SOCKSServer;
}

__INLINE__ void FTPClient::SetSOCKSServer(const char* _socks)
{
    SOCKSServer = _socks;
}

__INLINE__ const FTPURL& FTPClient::GetResource() const
{
    return Resource;
}

__INLINE__ void FTPClient::SetResource(const char* _url)
{
    Resource = _url;
}

__INLINE__ _string FTPClient::GetUsername() const
{
    return Username;
}

__INLINE__ void FTPClient::SetUsername(const _string& _username)
{
    Username = _username;
}

__INLINE__ _string FTPClient::GetPassword() const
{
    return Password;
}

__INLINE__ void FTPClient::SetPassword(const _string& _password)
{
    Password = _password;
}

__INLINE__ _string FTPClient::GetAccount() const
{
    return Account;
}

__INLINE__ void FTPClient::SetAccount(const _string& _account)
{
    Account = _account;
}

__INLINE__ uint16 FTPClient::GetSocksVersion() const
{
    return SocksVersion;
}

__INLINE__ void  FTPClient::SetSocksVersion(uint16 _ver)
{
    SocksVersion = _ver;
}

__INLINE__ const PalmStreamSocket& FTPClient::GetConnection() const
{
    return Connection;
}

__INLINE__ void FTPClient::Terminate()
{
    Terminated = true;
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__
#endif // __PALM_FTP_CLIENT_INL__
