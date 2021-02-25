////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __AIL_H__
#   include <ail.hpp>
#endif

#ifndef __PALM_BROADCAST_SOCKET_INC__
#   include <PalmBroadcastSocket.inc>
#endif

#ifdef __PALM_OS__

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class PalmBroadcastSocket
// ----- -------------------
PalmBroadcastSocket::PalmBroadcastSocket()
{
}

PalmBroadcastSocket::PalmBroadcastSocket(const PalmIPv4& _remote_address, const PalmIPv4& _local_address)
                   : PalmDatagramSocket(_remote_address, _local_address)
{
}

PalmBroadcastSocket::~PalmBroadcastSocket()
{
    Disconnect();
}

void PalmBroadcastSocket::Create(bool _bind, uint16 _timeout, int16 _proto)
{
    PalmDatagramSocket::Create(_bind, _timeout, _proto);
    //
    uint16 on = 1;
    palmxassert(PalmSocketModule::SetSocketOption(Socket, netSocketOptLevelIP, netSocketOptSockBroadcast, &on, sizeof(on)) == errNone, Error::eOperationFailure, PalmBroadcastSocket::XPalmBroadcastSocket);
}

void PalmBroadcastSocket::Connect(bool _bind, uint16 _timeout, int16 _proto)
{
    PalmDatagramSocket::Connect(_bind, _timeout, _proto);
    //
    uint16 on = 1;
    palmxassert(PalmSocketModule::SetSocketOption(Socket, netSocketOptLevelIP, netSocketOptSockBroadcast, &on, sizeof(on)) == errNone, Error::eOperationFailure, PalmBroadcastSocket::XPalmBroadcastSocket);
}
////////////////////////////////////////////////////////////////////////////////////////
// class XPalmBroadcastSocket
// ----- --------------------
void PalmBroadcastSocket::XPalmBroadcastSocket::LoadErrorDescriptions()
{
    // base class
    XPalmDatagramSocket::LoadErrorDescriptions();
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__
