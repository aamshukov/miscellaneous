////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __AIL_H__
#   include <ail.hpp>
#endif

#ifndef __THREAD_INC__
#   include <Thread.inc>
#endif

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class Thread
// ----- ------
Thread::Thread()
      : Handle(0),
        State(Thread::Created),
        Attached(false),
        TerminationRequested(false)
{
}

Thread::Thread(byte)
      : Handle(0),
        State(Thread::Running),
        Attached(false),
        TerminationRequested(false)
{
    ::DuplicateHandle(::GetCurrentProcess(), ::GetCurrentThread(), ::GetCurrentProcess(), &Handle, 0, false, DUPLICATE_SAME_ACCESS);
}

Thread::~Thread()
{
    if(!Attached && (GetState() == Thread::Running || GetState() == Thread::Suspended))
    {
        throw Thread::XThread();
    }

    if(Handle != null)
    {
        ::CloseHandle(Handle), Handle = null;
    }
}

void Thread::Start()
{
    // if Start() has already been called for this _thread, release the
    // previously created system _thread object before launching a new one.
    if((GetState() != Thread::Created) && Handle != null)
    {
        ::CloseHandle(Handle);
    }

    ulong id = 0;

    Handle = ::CreateThread(0, 0, (LPTHREAD_START_ROUTINE)(&Thread::Execute), reinterpret_cast<void*>(this), 0, &id);

    if(Handle == 0)
    {
        State = Thread::Invalid;
        throw Thread::XThread();
    }
    State = Thread::Running;
}

uint Thread::Suspend()
{
    if(State == Thread::Created || State == Thread::Finished || Handle == 0)
    {
        throw Thread::XThread();
    }

    uint result = ::SuspendThread(Handle);

    if(result < MAXIMUM_SUSPEND_COUNT)
    {
        State = Thread::Suspended;
    }
    return result;
}

uint Thread::Resume()
{
    if(State == Thread::Created || State == Thread::Finished || Handle == 0)
    {
        throw Thread::XThread();
    }

    if(State != Thread::Running)
    {
        uint result = ::ResumeThread(Handle);

        if(result != static_cast<uint>(-1))
        {
            State = Thread::Running;
        }
        return result;
    }
    return 0; // ok
}

uint Thread::WaitForExit(uint _timeout)
{
    if(Handle != 0)
    {
        return ::WaitForSingleObject(Handle, _timeout);
    }
    return static_cast<uint>(-1);
}

uint Thread::TerminateAndWait(uint _timeout)
{
    Terminate();
    return WaitForExit(_timeout);
}

ulong Thread::Execute(void* _thread)
{
    if(_thread != null)
    {
        int code = static_cast<Thread*>(_thread)->Run();
        static_cast<Thread*>(_thread)->State = Thread::Finished;
        return code;
    }
    return 0;
}

byte Thread::CheckState() const
{
    if(Handle == 0)
    {
        return false;
    }

    ulong code;
  ::GetExitCodeThread(Handle, &code);
    return code == STILL_ACTIVE ? Thread::Running : Thread::Finished;
}

void Thread::Exit(uint _code)
{
    State = Thread::Finished;
  ::ExitThread(_code);
}
////////////////////////////////////////////////////////////////////////////////////////
// class XThread
// ----- -------
Thread::XThread::XThread(uint _error) : X(_error)
{
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__
