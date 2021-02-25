////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  Copyright © 1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PALM_RAW_SOCKET_H__
#define __PALM_RAW_SOCKET_H__

#ifdef __PALM_OS__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class PalmRawSocket
// ----- -------------
class __DECLSPEC__ PalmRawSocket : public PalmDatagramSocket
{
    private:
                    PalmRawSocket(const PalmRawSocket&);
     PalmRawSocket& operator = (const PalmRawSocket&);
    public:
     // ctor/dtor
                    PalmRawSocket();
     explicit       PalmRawSocket(const PalmIPv4&, const PalmIPv4& = PalmSocket::DummyIP);
     virtual       ~PalmRawSocket();

     // api
     void           Create(bool = true, uint16 = PalmSocket::eTimeout, int16 = netSocketOptLevelIP);
     void           Connect(bool = true, uint16 = PalmSocket::eTimeout, int16 = netSocketOptLevelIP);

    public:

    class __DECLSPEC__ XPalmRawSocket : public XPalmDatagramSocket
    {
        public:

        enum EErrors
        {
            // appErrorClass+'rwsc'
        };

        public:
         virtual void LoadErrorDescriptions();
    };

    friend class XPalmRawSocket;
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__
#endif // __PALM_RAW_SOCKET_H__
