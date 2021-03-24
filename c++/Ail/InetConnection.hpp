////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __INET_CONNECTION_H__
#define __INET_CONNECTION_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class InetConnection
// ----- --------------
class __DECLSPEC__ InetConnection
{
    typedef AutoPtrArray<tchar> _Array;

    private:
    _Array          Username; // proxy/socks
    _Array          Password; // proxy/socks
    _Array          Proxy;
    _Array          Socks;
     short          SocksVer;
    public:
     // ctor/dtor
                    InetConnection();
                   ~InetConnection();

     // access
     const tchar*   GetUsername()                   const;
     void           SetUsername(const tchar*);

     const tchar*   GetPassword()                   const;
     void           SetPassword(const tchar*);

     const tchar*   GetProxy()                      const;
     void           SetProxy(const tchar*);

     const tchar*   GetSocks()                      const;
     void           SetSocks(const tchar*);

     short          GetSocksVer()                   const;
     void           SetSocksVer(short = 5);

     // protocol
     void           Connect(StreamSocket&, const tchar*, uint = 20);
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __INET_CONNECTION_H__
