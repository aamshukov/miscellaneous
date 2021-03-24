////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __ECHO_CLIENT_INL__
#define __ECHO_CLIENT_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class EchoClient
// ----- ----------
const DatagramSocket& EchoClient::GetConnection() const
{
    return Connection;
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __ECHO_CLIENT_INL__
