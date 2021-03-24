////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __STREAM_SOCKET_H__
#define __STREAM_SOCKET_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class StreamSocket
// ----- ------------
class __DECLSPEC__ StreamSocket : public Socket
{
    private:
                    StreamSocket(const StreamSocket&);
     StreamSocket&  operator = (const StreamSocket&);
    public:
     // ctor/dtor
                    StreamSocket();
     explicit       StreamSocket(const IPv4Address&, const IPv4Address& = Socket::DummyIP);
     virtual       ~StreamSocket();

     // protocol
     long           GetAvailable();

     void           Connect(bool = true, int = 0, ushort = IPPROTO_IP);
     void           Disconnect();

     int            Send(const byte*, int, int = 0, int = 0);

     int            Receive(byte*, int, int = 0, int = 0);
     int            ReceiveCount(byte*, int, int = 0);
     int            ReceiveLine(byte*, int, int);

     void           Listen(int = 8);
     void           Accept(StreamSocket&, int = 8);

     void           Discard(int = 0, bool = true);

     void           DisableNagleAlgorithm(bool = true);
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __STREAM_SOCKET_H__
