////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PALM_HTTP_CLIENT_INL__
#define __PALM_HTTP_CLIENT_INL__

#ifdef __PALM_OS__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class HTTPClient
// ----- ----------
__INLINE__ const HTTPURL& HTTPClient::GetProxyServer() const
{
    return ProxyServer;
}

__INLINE__ void HTTPClient::SetProxyServer(const char* _proxy)
{
    ProxyServer = _proxy;
}

__INLINE__ const HTTPURL& HTTPClient::GetSOCKSServer() const
{
    return SOCKSServer;
}

__INLINE__ void HTTPClient::SetSOCKSServer(const char* _socks)
{
    SOCKSServer = _socks;
}

__INLINE__ const HTTPURL& HTTPClient::GetResource() const
{
    return Resource;
}

__INLINE__ void HTTPClient::SetResource(const char* _url)
{
    Resource = _url;
}

__INLINE__ const PalmStreamSocket& HTTPClient::GetConnection() const
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

__INLINE__ void HTTPClient::GetUsername(char* _buffer, uint16 _count) const
{
    if(_buffer == null)
    {
        return;
    }
    PalmText::StrNCopy(_buffer, Username, static_cast<int16>(_count));
}

__INLINE__ void HTTPClient::SetUsername(const char* _username)
{
    Username = PalmText::StrClone(_username);
}

__INLINE__ void HTTPClient::GetPassword(char* _buffer, uint16 _count) const
{
    if(_buffer == null)
    {
        return;
    }
    PalmText::StrNCopy(_buffer, Password, static_cast<int16>(_count));
}

__INLINE__ void HTTPClient::SetPassword(const char* _password)
{
    Password = PalmText::StrClone(_password);
}

__INLINE__ uint16 HTTPClient::GetSocksVersion() const
{
    return SocksVersion;
}

__INLINE__ void  HTTPClient::SetSocksVersion(uint16 _ver)
{
    SocksVersion = _ver;
}

__INLINE__ void HTTPClient::Write(PalmFile& _file, const byte* _buffer, uint16 _count)
{
    if(Filter != null)
    {
        if(Filter(const_cast<byte*>(_buffer), _count))
        {
            _file.Write(_buffer, 1, _count);
        }
    }
    else
    {
        _file.Write(_buffer, 1, _count);
    }
}

__INLINE__ void HTTPClient::Terminate()
{
    Terminated = true;
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__
#endif // __PALM_HTTP_CLIENT_INL__
