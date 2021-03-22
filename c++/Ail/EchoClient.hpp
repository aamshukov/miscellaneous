////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __ECHO_CLIENT_H__
#define __ECHO_CLIENT_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class EchoClient
// ----- ----------
class __DECLSPEC__ EchoClient
{
    private:
     DatagramSocket         Connection;
    public:
     // ctor/dtor
                            EchoClient();
                            EchoClient(const IPv4Address&);
                           ~EchoClient();

     // access
     const DatagramSocket&  GetConnection() const;

     // protocol
     bool                   Echo(const byte*, int, int = 20, int = 0);
     bool                   Echo(const byte*, int, IPv4Address&, int = 20, int = 0);
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __ECHO_CLIENT_H__
