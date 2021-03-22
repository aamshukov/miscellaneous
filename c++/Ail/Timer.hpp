////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __TIMER_H__
#define __TIMER_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class Timer
// ----- -----
class __DECLSPEC__ Timer : private SyncObject
{
    private:
     bool       Started;

     uint       Delay;
     uint       IdTimer;
     uint       RetValue;

     HWND       HWindow;

     TIMERPROC  Procedure;
    public:
                Timer();
                Timer(HWND, uint, uint = 100, TIMERPROC = null, bool = true);
     virtual   ~Timer();

     void       Init(HWND, uint, uint, TIMERPROC, bool = true);

     bool       IsStarted()                 const;
     bool       IsProcedure()               const;

     uint       GetDelay()                  const;
     void       SetDelay(uint);

     uint       GetIdTimer()                const;

     HWND       GetHWindow()                const;
     void       SetHWindow(HWND);

     void       IncreaseDelay(uint);

     void       Start();
     void       Stop();
    public:

    class __DECLSPEC__ XTimer : public X
    {
        public:

        enum EErorr
        {
            ErrOpIncreaseDelay = 0x00000100,
            ErrOpStart         = 0x00000200
        };

        public:
            XTimer(uint = X::Failure);
    };  

    friend class XTimer;
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __TIMER_H__
