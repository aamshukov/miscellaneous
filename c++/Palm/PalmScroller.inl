////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  Copyright © 1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PALM_SCROLLER_INL__
#define __PALM_SCROLLER_INL__

#ifdef __PALM_OS__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class PalmScroller
// ----- ------------
__INLINE__ PalmScroller::operator ScrollBarType* ()
{
    return static_cast<ScrollBarType*>(Control);
}

__INLINE__ PalmScroller::operator const ScrollBarType* () const
{
    return const_cast<const ScrollBarType*>(Control);
}

__INLINE__ void PalmScroller::GetScrollBar(int16& _value, int16& _min, int16& _max, int16& _page_size)
{
    palmxassert(Control != null, Error::eUninitialized, PalmScroller::XPalmScroller);
  ::SclGetScrollBar(static_cast<ScrollBarType*>(Control), &_value, &_min, &_max, &_page_size);
}

__INLINE__ void PalmScroller::SetScrollBar(int16 _value, int16 _min, int16 _max, int16 _page_size)
{
    palmxassert(Control != null, Error::eUninitialized, PalmScroller::XPalmScroller);
  ::SclSetScrollBar(static_cast<ScrollBarType*>(Control), _value, _min, _max, _page_size);
}

__INLINE__ void PalmScroller::DrawScrollBar()
{
    palmxassert(Control != null, Error::eUninitialized, PalmScroller::XPalmScroller);
  ::SclDrawScrollBar(static_cast<ScrollBarType*>(Control));
}

__INLINE__ bool PalmScroller::HandleEvent(const EventType& _event)
{
    palmxassert(Control != null, Error::eUninitialized, PalmScroller::XPalmScroller);
    return ::SclHandleEvent(static_cast<ScrollBarType*>(Control), &_event);
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__
#endif // __PALM_SCROLLER_INL__
