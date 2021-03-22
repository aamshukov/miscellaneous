////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __HTTP_CLIENT_H__
#define __HTTP_CLIENT_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
typedef bool (*__http_filter__)(byte*, uint&);
////////////////////////////////////////////////////////////////////////////////////////
// class HTTPClient
// ----- ----------
class __DECLSPEC__ HTTPClient
{
    typedef AutoPtrArray<tchar> _Array;

    private:
     HTTPURL                ProxyServer;
     HTTPURL                SOCKSServer;
     HTTPURL                Resource;
     StreamSocket           Connection;
   __http_filter__          Filter;
     volatile bool          Terminated;
    _Array                  Username;       // proxy/socks user name
    _Array                  Password;       // proxy/socks passowrd
     short                  SocksVersion;   // SOCKS4/SOCKS5
    protected:
     void                   Write(File<>&, const byte*, uint);
    public:
     // ctor/dtor
                            HTTPClient(const HTTPURL&);
                           ~HTTPClient();

     // access
     const HTTPURL&         GetProxyServer()                const;
     void                   SetProxyServer(const tchar*);

     const HTTPURL&         GetSOCKSServer()                const;
     void                   SetSOCKSServer(const tchar*);

     const HTTPURL&         GetResource()                   const;
     void                   SetResource(const tchar*);

     const StreamSocket&    GetConnection()                 const;

   __http_filter__          GetFilter()                     const;
     void                   SetFileter(__http_filter__);

     void                   GetUsername(tchar*, ushort)     const;
     void                   SetUsername(const tchar*);
     void                   GetPassword(tchar*, ushort)     const;
     void                   SetPassword(const tchar*);

     short                  GetSocksVersion()               const;
     void                   SetSocksVersion(short);

     // protocol
     void                   Connect();
     void                   Disconnect();

     void                   Terminate();

     httpcode               CheckLink(HTTProtocol::HTTPContext&, uint = 20);
     static httpcode        CheckLink(const tchar*, const tchar* = null, const tchar* = null, uint = 20);

     httpcode               GetResource(File<>&, HTTProtocol::HTTPContext&, bool = true, uint = 20);
     static httpcode        GetResource(const tchar*, const tchar*, const tchar* = null, const tchar* = null, uint = 20);
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __HTTP_CLIENT_H__
