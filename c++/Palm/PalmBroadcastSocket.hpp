////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __BROADCAST_SOCKET_H__
#define __BROADCAST_SOCKET_H__

#ifdef __PALM_OS__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class PalmBroadcastSocket
// ----- -------------------
class __DECLSPEC__ PalmBroadcastSocket : public PalmDatagramSocket
{
    private:
                            PalmBroadcastSocket(const PalmBroadcastSocket&);
     PalmBroadcastSocket&   operator = (const PalmBroadcastSocket&);
    public:
     // ctor/dtor
                            PalmBroadcastSocket();
     explicit               PalmBroadcastSocket(const PalmIPv4&, const PalmIPv4& = PalmSocket::DummyIP);
     virtual               ~PalmBroadcastSocket();

     // api
     void                   Create(bool = true, uint16 = PalmSocket::eTimeout, int16 = netSocketOptLevelIP);
     void                   Connect(bool = true, uint16 = PalmSocket::eTimeout, int16 = netSocketOptLevelIP);

    public:

    class __DECLSPEC__ XPalmBroadcastSocket : public XPalmDatagramSocket
    {
        public:

        enum EErrors
        {
            // appErrorClass+'brsc'
        };

        public:
         virtual void LoadErrorDescriptions();
    };

    friend class XPalmBroadcastSocket;
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__
#endif // __BROADCAST_SOCKET_H__
