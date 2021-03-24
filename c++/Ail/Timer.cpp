////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __AIL_H__
#   include <ail.hpp>
#endif

#ifndef __TIMER_INC__
#   include <Timer.inc>
#endif

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class Timer
// ----- -----
Timer::Timer()
{
    Started   = false;
    HWindow   = null;
    IdTimer   = 0;
    Delay     = 0;
    Procedure = null;
}

Timer::Timer(HWND hwnd, uint idtimer, uint delay, TIMERPROC procedure, bool start)
{
    Init(hwnd, idtimer, delay, procedure, start);
}

Timer::~Timer()
{
    Stop();
}

void Timer::Init(HWND hwnd, uint idtimer, uint delay, TIMERPROC procedure, bool start)
{
    HWindow   = hwnd;
    IdTimer   = idtimer;
    Delay     = delay;
    Procedure = procedure;

    if(start && !(RetValue = SetTimer(HWindow, IdTimer, Delay, Procedure)))
    {
        throw Timer::XTimer();
    }

    Started = start;
}

void Timer::IncreaseDelay(uint newdelay)
{
    Lock lock(this);

    if(!(RetValue = SetTimer(HWindow, IdTimer, Delay = newdelay, Procedure)))
    {
        throw Timer::XTimer(XTimer::ErrOpIncreaseDelay);
    }

    Started = true;
}

void Timer::Start()
{
    Lock lock(this);

    if(!(RetValue = SetTimer(HWindow, IdTimer, Delay, Procedure)))
    {
        throw Timer::XTimer(XTimer::ErrOpStart);
    }

    Started = true;
}

void Timer::Stop()
{
    Lock lock(this);

    if(!HWindow)
    {
        KillTimer(HWindow, RetValue);
    }
    else
    {
        KillTimer(HWindow, IdTimer);
    }

    Started  = false;
    RetValue = 0;
}

Timer::XTimer::XTimer(uint _error) : X(_error)
{
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__
