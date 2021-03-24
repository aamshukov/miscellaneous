////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __LISTENER_INL__
#define __LISTENER_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class Listener
// ----- ----------
__INLINE__ HWND Listener::GetListener() const
{
    return HListener;
}

__INLINE__ void Listener::SetListener(HWND _listener)
{
    HListener = _listener;
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __LISTENER_INL__
