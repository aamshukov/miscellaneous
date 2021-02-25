////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  Copyright © 1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PALM_SOCKET_H__
#define __PALM_SOCKET_H__

#pragma once

#ifdef __PALM_OS__

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class PalmSocket
// ----- ----------
class __DECLSPEC__ PalmSocket
{
    public:

    static const PalmIPv4 DummyIP;

    enum EConst
    {
        eTimeout = 20 // in secs
    };

    enum EState
    {
        eUnknown      = 0, // unknown state, socket is not connected
        eConnected    = 1, // socket is connected
        eDisconnected = 2, // socket is disconnected
        eInvalid      = 3  // socket is in invalid state (throw)
    };

    enum EMode
    {
        eReadFD = 0,
        eWriteFD,
        eExceptFD
    };

    private:
                        PalmSocket(const PalmSocket&);
     PalmSocket&        operator = (const PalmSocket&);
    protected:
     PalmIPv4           LocalAddress;
     PalmIPv4           RemoteAddress;

     EState             State;
     socket_t           Socket;
    protected:
     virtual void       Connect(bool = true, uint16 = PalmSocket::eTimeout, int16 = netSocketProtoIPTCP)  = 0;
     virtual void       Disconnect(int16 = netSocketDirBoth, uint16 = PalmSocket::eTimeout)               = 0;
     virtual int16      Send(const byte*, uint16, uint16 = 0, uint16 = 0)                                 = 0;
     virtual int16      Receive(byte*, uint16 = 0, uint16 = 0, uint16 = 0)                                = 0;
    public:
     // ctor/dtor
                        PalmSocket();
     explicit           PalmSocket(const PalmIPv4&, const PalmIPv4& = PalmSocket::DummyIP);
     virtual           ~PalmSocket();

     // access
     bool               IsConnected()                                                               const;
     EState             GetState()                                                                  const;
     void               SetState(EState);

     PalmIPv4&          GetLocalAddress()                                                           const;
     void               SetLocalAddress(const PalmIPv4&);

     PalmIPv4&          GetRemoteAddress()                                                          const;
     void               SetRemoteAddress(const PalmIPv4&);

     socket_t           GetSocket()                                                                 const;
     void               SetSocket(socket_t);

     operator           socket_t ();

     // api
     void               GetOptions(uint16, uint16, byte*, uint16&, uint16 = PalmSocket::eTimeout)   const;
     void               SetOptions(uint16, uint16, byte*, uint16,  uint16 = PalmSocket::eTimeout);

     int16              SetTimeout(uint16, PalmSocket::EMode);
     uint16             SetBufferSize(uint16 = 16384, uint16 = netSocketOptSockRcvBufSize);

    public:

    class __DECLSPEC__ XPalmSocket : public PalmError
    {
        public:

        enum EErrors
        {
            eInvalidState = appErrorClass+'sckt'
        };

        public:
         virtual void LoadErrorDescriptions();
    };

    friend class XPalmSocket;
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__
#endif // __PALM_SOCKET_H__
