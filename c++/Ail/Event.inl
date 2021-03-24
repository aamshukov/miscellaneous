////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __EVENT_INL__
#define __EVENT_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class Event
// ----- -----
__INLINE__ void Event::Set()
{
    Assert();
    ::SetEvent(*this);
}

__INLINE__ void Event::Reset()
{
    Assert();
    ::ResetEvent(*this);
}

__INLINE__ void Event::Pulse()
{
    Assert();
    ::PulseEvent(*this);
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __EVENT_INL__
