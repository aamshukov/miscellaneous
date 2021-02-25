////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PALM_DATAGRAM_SOCKET_H__
#define __PALM_DATAGRAM_SOCKET_H__

#ifdef __PALM_OS__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class PalmDatagramSocket
// ----- ------------------
class __DECLSPEC__ PalmDatagramSocket : public PalmSocket
{
    private:
                            PalmDatagramSocket(const PalmDatagramSocket&);
     PalmDatagramSocket&    operator = (const PalmDatagramSocket&);
    public:
     // ctor/dtor
                            PalmDatagramSocket();
     explicit               PalmDatagramSocket(const PalmIPv4&, const PalmIPv4& = PalmSocket::DummyIP);
     virtual               ~PalmDatagramSocket();

     // api
     void                   Create(bool = true, uint16 = PalmSocket::eTimeout, int16 = netSocketOptLevelIP);

     void                   Connect(bool = true, uint16 = PalmSocket::eTimeout, int16 = netSocketOptLevelIP);
     void                   Disconnect(int16 = netSocketDirBoth, uint16 = PalmSocket::eTimeout);

     int16                  Send(const byte*, uint16, uint16 = PalmSocket::eTimeout, uint16 = 0);
     int16                  SendTo(NetIOParamType&, uint16 = PalmSocket::eTimeout, uint16 = 0);

     int16                  Receive(byte*, uint16, uint16 = PalmSocket::eTimeout, uint16 = 0);
     int16                  ReceiveFrom(NetIOParamType&, uint16 = PalmSocket::eTimeout, uint16 = 0);

    public:

    class __DECLSPEC__ XPalmDatagramSocket : public XPalmSocket
    {
        public:

        enum EErrors
        {
            // appErrorClass+'dtsc'
        };

        public:
         virtual void LoadErrorDescriptions();
    };

    friend class XPalmDatagramSocket;
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__
#endif // __PALM_DATAGRAM_SOCKET_H__
