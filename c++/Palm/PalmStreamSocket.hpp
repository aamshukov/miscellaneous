////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PALM_STREAM_SOCKET_H__
#define __PALM_STREAM_SOCKET_H__

#ifdef __PALM_OS__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class PalmStreamSocket
// ----- ----------------
class __DECLSPEC__ PalmStreamSocket : public PalmSocket
{
    private:
                        PalmStreamSocket(const PalmStreamSocket&);
     PalmStreamSocket&  operator = (const PalmStreamSocket&);
    public:
     // ctor/dtor
                        PalmStreamSocket();
     explicit           PalmStreamSocket(const PalmIPv4&, const PalmIPv4& = PalmSocket::DummyIP);
     virtual           ~PalmStreamSocket();

     // api
     void               Connect(bool = true, uint16 = PalmSocket::eTimeout, int16 = netSocketOptLevelIP);
     void               Disconnect(int16 = netSocketDirBoth, uint16 = PalmSocket::eTimeout);

     int16              Send(const byte*, uint16, uint16 = PalmSocket::eTimeout, uint16 = 0);

     int16              Receive(byte*, uint16, uint16 = PalmSocket::eTimeout, uint16 = 0);
     int16              ReceiveCount(byte*, uint16, uint16 = PalmSocket::eTimeout, uint16 = 0);
     int16              ReceiveLine(byte*, uint16, uint16 = PalmSocket::eTimeout);

     void               Listen(uint16 _count = 8, uint16 = PalmSocket::eTimeout);
     void               Accept(PalmStreamSocket&, uint16 = PalmSocket::eTimeout);

     uint32             GetAvailable(uint16 = PalmSocket::eTimeout);

     void               Discard(uint16 = PalmSocket::eTimeout, bool = false);
     void               DisableNagleAlgorithm(bool = true);

    public:

    class __DECLSPEC__ XPalmStreamSocket : public XPalmSocket
    {
        public:

        enum EErrors
        {
            // appErrorClass+'stsc'
        };

        public:
         virtual void LoadErrorDescriptions();
    };

    friend class XPalmStreamSocket;
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__
#endif // __PALM_STREAM_SOCKET_H__
