////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __THREAD_H__
#define __THREAD_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class Thread
// ----- ------
class __DECLSPEC__ Thread
{
    public:

    enum ETimeout
    {
        NoLimit = INFINITE
    };

    enum ECurrent
    {
        Current
    };

    enum EState
    {
        Created    = 1,
        Running    = 2,
        Suspended  = 3,
        Finished   = 4,
        Invalid    = 5,
        Terminated = 6
    };

    enum EPriority
    {
        Idle         = THREAD_PRIORITY_IDLE,          // -15
        Lowest       = THREAD_PRIORITY_LOWEST,        //  -2
        BelowNormal  = THREAD_PRIORITY_BELOW_NORMAL,  //  -1
        Normal       = THREAD_PRIORITY_NORMAL,        //   0
        AboveNormal  = THREAD_PRIORITY_ABOVE_NORMAL,  //   1
        Highest      = THREAD_PRIORITY_HIGHEST,       //   2
        TimeCritical = THREAD_PRIORITY_TIME_CRITICAL, //  15
    };

    private:
     bool           Attached;
     volatile bool  TerminationRequested;
     HANDLE         Handle;
    private:
                    Thread(const Thread&);
     const Thread&  operator = (const Thread&);
     //
     static ulong   Execute(void*);
    protected:
     volatile byte  State;
    protected:
     byte           CheckState()                    const;
     void           Exit(uint);
     //
     virtual int    Run()                           = 0;
    public:
     // ctor/dtor
                    Thread();
                    Thread(byte);
     virtual       ~Thread();

     // operator
                    operator HANDLE ();

     // access
     byte           GetState();
     uint           GetExitCode()                   const;

     int            GetPriority()                   const;
     int            SetPriority(int);

     // protocol
     bool           ShouldTerminate()               const;
     virtual void   Terminate();

     void           Start();
     uint           Suspend();
     uint           Resume();
     bool           Sleep(uint, bool = false);

     uint           WaitForExit(uint = Thread::NoLimit);
     uint           TerminateAndWait(uint = Thread::NoLimit);
    public:

    class __DECLSPEC__ XThread : public X
    {
        public:
            XThread(uint = X::Failure);
    };

    friend class XThread;
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __THREAD_H__
