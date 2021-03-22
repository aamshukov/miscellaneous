////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __TIMER_INL__
#define __TIMER_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class Timer
// ----- -----
__INLINE__ bool Timer::IsStarted() const
{
    return Started;
}

__INLINE__ bool Timer::IsProcedure() const
{
    return Procedure != null;
}

__INLINE__ uint Timer::GetDelay() const
{
    return Delay;
}

__INLINE__ VOID Timer::SetDelay(uint delay)
{
    Delay = delay;
}

__INLINE__ uint Timer::GetIdTimer() const
{
    return IdTimer;
}

__INLINE__ HWND Timer::GetHWindow() const
{
    return (HWND)HWindow;
}

__INLINE__ void Timer::SetHWindow(HWND hwnd)
{
    HWindow = hwnd;
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __TIMER_INL__
