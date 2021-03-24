////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __HTTP_CLIENT_INL__
#define __HTTP_CLIENT_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class HTTPClient
// ----- ----------
__INLINE__ const HTTPURL& HTTPClient::GetProxyServer() const
{
    return ProxyServer;
}

__INLINE__ void HTTPClient::SetProxyServer(const tchar* _proxy)
{
    ProxyServer = _proxy;
}

__INLINE__ const HTTPURL& HTTPClient::GetSOCKSServer() const
{
    return SOCKSServer;
}

__INLINE__ void HTTPClient::SetSOCKSServer(const tchar* _socks)
{
    SOCKSServer = _socks;
}

__INLINE__ const HTTPURL& HTTPClient::GetResource() const
{
    return Resource;
}

__INLINE__ void HTTPClient::SetResource(const tchar* _url)
{
    Resource = _url;
}

__INLINE__ const StreamSocket& HTTPClient::GetConnection() const
{
    return Connection;
}

__INLINE__ __http_filter__ HTTPClient::GetFilter() const
{
    return Filter;
}

__INLINE__ void HTTPClient::SetFileter(__http_filter__ _filter)
{
    Filter = _filter;
}

__INLINE__ void HTTPClient::GetUsername(tchar* _buffer, ushort _count) const
{
    if(_buffer == null)
    {
        return;
    }
    StrNCopy(_buffer, Username, _count);
}

__INLINE__ void HTTPClient::SetUsername(const tchar* _username)
{
    Username = StrClone(_username);
}

__INLINE__ void HTTPClient::GetPassword(tchar* _buffer, ushort _count) const
{
    if(_buffer == null)
    {
        return;
    }
    StrNCopy(_buffer, Password, _count);
}

__INLINE__ void HTTPClient::SetPassword(const tchar* _password)
{
    Password = StrClone(_password);
}

__INLINE__ short HTTPClient::GetSocksVersion() const
{
    return SocksVersion;
}

__INLINE__ void  HTTPClient::SetSocksVersion(short _ver)
{
    SocksVersion = _ver;
}

__INLINE__ void HTTPClient::Write(File<>& _file, const byte* _buffer, uint _count)
{
    if(Filter != null)
    {
        if(Filter(const_cast<byte*>(_buffer), _count))
        {
            _file.Write(_buffer, _count);
        }
    }
    else
    {
        _file.Write(_buffer, _count);
    }
}

__INLINE__ void HTTPClient::Terminate()
{
    Terminated = true;
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __HTTP_CLIENT_INL__
