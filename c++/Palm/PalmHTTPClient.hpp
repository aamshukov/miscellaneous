////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PALM_HTTP_CLIENT_H__
#define __PALM_HTTP_CLIENT_H__

#ifdef __PALM_OS__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
typedef bool (*__http_filter__)(byte*, uint16&);
////////////////////////////////////////////////////////////////////////////////////////
// class HTTPClient
// ----- ----------
class __DECLSPEC__ HTTPClient
{
    typedef PalmStreamSocket   _Socket;
    typedef AutoPtrArray<char> _array;

    private:
     HTTPURL                ProxyServer;
     HTTPURL                SOCKSServer;
     HTTPURL                Resource;
    _Socket                 Connection;
   __http_filter__          Filter;
     volatile bool          Terminated;
    _array                  Username;       // proxy/socks user name
    _array                  Password;       // proxy/socks passowrd
     uint16                 SocksVersion;   // SOCKS4/SOCKS5
    protected:
     void                   Write(PalmFile&, const byte*, uint16);
    public:
     // ctor/dtor
                            HTTPClient(const HTTPURL&);
                           ~HTTPClient();

     // access
     const HTTPURL&         GetProxyServer()                const;
     void                   SetProxyServer(const char*);

     const HTTPURL&         GetSOCKSServer()                const;
     void                   SetSOCKSServer(const char*);

     const HTTPURL&         GetResource()                   const;
     void                   SetResource(const char*);

     const _Socket&    		GetConnection()                 const;

   __http_filter__          GetFilter()                     const;
     void                   SetFileter(__http_filter__);

     void                   GetUsername(char*, uint16)      const;
     void                   SetUsername(const char*);
     void                   GetPassword(char*, uint16)      const;
     void                   SetPassword(const char*);

     uint16                 GetSocksVersion()               const;
     void                   SetSocksVersion(uint16);

     // protocol
     void                   Connect();
     void                   Disconnect();

     void                   Terminate();

     httpcode               CheckLink(HTTProtocol::HTTPContext&, uint16 = PalmSocket::eTimeout);
     static httpcode        CheckLink(const char*, const char* = null, const char* = null, uint16 = PalmSocket::eTimeout);

     httpcode               GetResource(PalmFile&, HTTProtocol::HTTPContext&, bool = true, uint16 = PalmSocket::eTimeout);
     static httpcode        GetResource(const char*, const char*, const char* = null, const char* = null, uint16 = PalmSocket::eTimeout);

    public:
    
    class __DECLSPEC__ XHTTPClient : public PalmError
    {
        public:

        enum EErrors
        {
            // appErrorClass+'http'
        };

        protected:
         virtual void LoadErrorDescriptions();
    };

    friend class XHTTPClient;
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__
#endif // __PALM_HTTP_CLIENT_H__
