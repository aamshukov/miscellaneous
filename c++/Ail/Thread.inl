////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __THREAD_INL__
#define __THREAD_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class Thread
// ----- ------
__INLINE__ Thread::operator HANDLE ()
{
    return Handle;
}

__INLINE__ byte Thread::GetState()
{
    if(State == Thread::Running)
    {
        State = CheckState();
    }
    return State;
}

__INLINE__ uint Thread::GetExitCode() const
{
    ulong code;
  ::GetExitCodeThread(Handle, &code);
    return code;
}

__INLINE__ int Thread::GetPriority() const
{
    return ::GetThreadPriority(Handle);
}

__INLINE__ int Thread::SetPriority(int _priority)
{
    return ::SetThreadPriority(Handle, _priority);
}

__INLINE__ bool Thread::ShouldTerminate() const
{
    return TerminationRequested;
}

__INLINE__ void Thread::Terminate()
{
    State = Thread::Terminated;
    TerminationRequested = true;
}

__INLINE__ bool Thread::Sleep(uint _time, bool _alertable)
{
    return ::SleepEx(_time, _alertable) == WAIT_IO_COMPLETION;
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __THREAD_INL__
