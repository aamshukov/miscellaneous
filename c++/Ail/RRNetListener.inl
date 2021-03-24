////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __RR_NET_LISTENER_INL__
#define __RR_NET_LISTENER_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class RRNetListener
// ----- -------------
__INLINE__ ushort RRNetListener::GetPort()
{
    return Port;
}

__INLINE__ RRNetListener::SetPort(ushort _port)
{
    Port = _port;
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __RR_NET_LISTENER_INL__
