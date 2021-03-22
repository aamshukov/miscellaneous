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

#ifndef __NTSERVICE_INC__
#   include <NTService.inc>
#endif

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class NTService
// ----- ---------
NTService::NTService(const tchar* _sysname, const tchar* _dspname, uint _type)
         : Type(_type)
{
    xassertv(_sysname != null && _dspname != null)

    SysName     = StrClone(_sysname);
    DisplayName = StrClone(_dspname);
    //
    Handle           = 0;
    State            = 0;
    ControlsAccepted = 0;
    Checkpoint       = 0;
    WaitHint         = 0;
    Type             = 0;
    Monitor          = 0;
}

NTService::~NTService()
{
}

void NTService::ServiceMain(uint _argc, tchar** _argv, LPHANDLER_FUNCTION _handler, LPTHREAD_START_ROUTINE _monitor_proc)
{
    uint err = 0; // ok

  __try
    {
        // phase I (connect SCM)
        Handle = ::RegisterServiceCtrlHandler(SysName, _handler);

        if(Handle == 0)
        {
            ErrorHandler(_T("RegisterServiceCtrlHandler"));
        }

        //
        const uint _timeout_ = 5000;
        //
        SetStatus(SERVICE_START_PENDING, 1, _timeout_);

        // phase II (parse args)
        ParseArgs(_argc, _argv);

        // phase III (launch monitor)
        LaunchMonitor(_monitor_proc);

        // phase IV (init service)
        Initialize();

        // phase V (go into)
        Run();
    }
  __except(err = ::GetExceptionCode(), EXCEPTION_EXECUTE_HANDLER)
    {
        if(Handle != 0)
        {
            SetStatus(SERVICE_STOPPED, 0, 0, 0, err, 0);
        }
    }

    // phase VI (shutdown)
    if(Monitor != null)
    {
        //
        const uint _timeout_ = 10000;
        //
        ::WaitForSingleObject(Monitor, _timeout_);
        ::CloseHandle(Monitor), Monitor = 0;
    }

    SetStatus(SERVICE_STOPPED, 0, 0, 0, err, 0);
}

void NTService::Handler(uint _control_code)
{
    // guard
    static uint _guard_ = -1;

    if(_guard_ == _control_code)
    {
        return;
    }

    switch(_control_code)
    {
        case SERVICE_CONTROL_STOP:
            StopEvent.Set();
            break;
        case SERVICE_CONTROL_PAUSE:
            PauseEvent.Set();
            break;
        case SERVICE_CONTROL_CONTINUE:
            if(GetState() != SERVICE_RUNNING)
            {
                _guard_ = _control_code;
                //
                ContinueEvent.Set();
            }
            return;
        case SERVICE_CONTROL_SHUTDOWN:
            ShutdownEvent.Set();
            break;
        case SERVICE_CONTROL_INTERROGATE:
            SetStatus(GetState());
            break;
        default: // user defined
            UserCommand(_control_code);
            break;
    }

    _guard_ = _control_code;
}

void NTService::Initialize()
{
}

void NTService::ParseArgs(uint, tchar**)
{
}

void NTService::Pause()
{
}

void NTService::Continue()
{
}

void NTService::Shutdown()
{
}

void NTService::UserCommand(uint)
{
}

void NTService::SetStatus(uint _state, uint _checkpoint, uint _hint, uint _controls, uint _exitcode, uint _spec_exitcode)
{
    if(_state != SERVICE_STOPPED)
    {
        // the only state that can set exit codes is stopped
        _exitcode      = S_OK;
        _spec_exitcode = 0;
    }

    if(_state == SERVICE_STOPPED || _state == SERVICE_PAUSED || _state == SERVICE_RUNNING)
    {
        // only pending states can set checkpoints or wait hints,
        // and pending states *must* set wait hints
        // requires hint and checkpoint == 0
        _hint       = 0;
        _checkpoint = 0;
    }
    else
    {
        // requires hint and checkpoint != 0
        if(_hint <= 0 || _checkpoint <= 0)
        {
            ErrorHandler(_t("CService::SetStatus: Pending statuses require a hint and checkpoint"), true, true, 0);
        }
    }

    Mutex.Acquire();
    //
    State = _state;

    if(_checkpoint != -1)
    {
        Checkpoint = _checkpoint;
    }

    if(_hint != -1)
    {
        WaitHint = _hint;
    }

    if(_controls != -1)
    {
        ControlsAccepted = _controls;
    }

    SERVICE_STATUS ss;

    ss.dwServiceType             = Type;
    ss.dwCurrentState            = State;
    ss.dwControlsAccepted        = ControlsAccepted;
    ss.dwWin32ExitCode           = _exitcode;
    ss.dwServiceSpecificExitCode = _spec_exitcode;
    ss.dwCheckPoint              = Checkpoint;
    ss.dwWaitHint                = WaitHint;
    //
    Mutex.Release();

    if(::SetServiceStatus(Handle, &ss) == 0)
    {
        ErrorHandler(_t("SetServiceStatus"));
    }
}

uint NTService::ErrorHandler(const tchar* _text, bool _report_error, bool _raise_exception, uint _error)
{
    void* buffer;
    AutoPtrArray<tchar> text = new tchar[512+128];

    if(_error != 0)
    {
        // try to get error explanation from the system
        if(::FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_ALLOCATE_BUFFER, 0, _error, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), reinterpret_cast<tchar*>(&buffer), 0, 0) == 0)
        {
            wsprintf(text, _t("%s failed: Unknown error %lu"), _text, _error);
        }
        else
        {
            wsprintf(text, _t("%s failed: %s"), _text, buffer);
        }
      ::LocalFree(buffer);
    }
    else
    {
        wsprintf(text, _t("%s\n"), _text);
    }

#ifdef _DEBUG
    ::OutputDebugString(text);
#endif

    if(_report_error)
    {
        ReportError(text);
    }

    if(_raise_exception)
    {
        ::RaiseException(_error, EXCEPTION_NONCONTINUABLE, 0, 0);
    }

    return _error;
}

void NTService::ReportError(const tchar* _text,  bool _error)
{
    HANDLE hlog = ::RegisterEventSource(0, GetDisplayName());

    if(hlog != 0)
    {
        const tchar* array[] = { _text };
        //
        ::ReportEvent(hlog, _error ? EVENTLOG_ERROR_TYPE : EVENTLOG_INFORMATION_TYPE, 0, 0, 0, 1, 0, array, 0);
        ::DeregisterEventSource(hlog);
    }
}

void NTService::LaunchMonitor(LPTHREAD_START_ROUTINE _monitor_proc)
{
    uint id = 0;
    Monitor = reinterpret_cast<HANDLE>(_beginthreadex(0, 0, (unsigned int (__stdcall *)(void *))(_monitor_proc), 0, 0, &id));

    if(Monitor == 0)
    {
        ErrorHandler(_T("LaunchMonitor"));
    }
}

uint NTService::MonitorProc()
{
    uint wait = 0;

    HANDLE events[NTService::EventNumber];

    events[0] = StopEvent;
    events[1] = PauseEvent;
    events[2] = ContinueEvent;
    events[3] = ShutdownEvent;

    for(;;)
    {
        wait = ::WaitForMultipleObjects(NTService::EventNumber, events, 0, INFINITE);

        switch(wait-WAIT_OBJECT_0)
        {
            case NTService::StopEv:
                Stop();
                goto _exit;
            case NTService::PauseEv:
                Pause();
                PauseEvent.Reset();
                break;
            case NTService::ContinueEv:
                Continue();
                ContinueEvent.Reset();
                break;
            case NTService::ShutdownEv:
                Shutdown();
                goto _exit;
        }
    }

_exit:    
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////
// class NTServiceInstall
// ----- ----------------
NTServiceInstall::NTServiceInstall(const tchar* _sysname, const tchar* _dspname)
{
    xassertv(_sysname != null && _dspname != null)

    SysName     = StrClone(_sysname);
    DisplayName = StrClone(_dspname);
}

NTServiceInstall::~NTServiceInstall()
{
}

bool NTServiceInstall::IsInstalled() const
{
    bool rc = false;

    SC_HANDLE hscm = ::OpenSCManager(null, null, SC_MANAGER_CONNECT);

    if(hscm != null)
    {
        SC_HANDLE hsrv = ::OpenService(hscm, SysName, SERVICE_QUERY_CONFIG);

        if(hsrv != 0)
        {
            rc = true;
          ::CloseServiceHandle(hsrv);
        }

      ::CloseServiceHandle(hscm);
    }

    return rc;
}

bool NTServiceInstall::Install(uint _type, uint _start, const tchar* _depends, const tchar* _name, const tchar* _password)
{
    SC_HANDLE hscm = null;
    SC_HANDLE hsrv = null;

    if(IsInstalled())
    {
        return true;
    }

    hscm = ::OpenSCManager(null, null, SC_MANAGER_CREATE_SERVICE);

    if(hscm == 0)
    {
      ::RaiseException(1, EXCEPTION_NONCONTINUABLE, 0, 0);
        return false;
    }

    AutoPtrArray<tchar> module = new tchar[_MAX_PATH];
  ::GetModuleFileName(null, module, _MAX_PATH);

    hsrv = ::CreateService(hscm, SysName, DisplayName, SERVICE_ALL_ACCESS, _type, _start, SERVICE_ERROR_NORMAL, module, null, null, _depends, _name, _password);

    if(hsrv == 0) 
    {
      ::CloseServiceHandle(hscm);
      ::RaiseException(2, EXCEPTION_NONCONTINUABLE, 0, 0);
        return false;
    }

  ::CloseServiceHandle(hsrv);
  ::CloseServiceHandle(hscm);
    return true;
}

bool NTServiceInstall::Remove(bool _stop)
{
    SC_HANDLE hscm = null;
    SC_HANDLE hsrv = null;

    hscm = ::OpenSCManager(null, null, SC_MANAGER_CREATE_SERVICE);

    if(hscm == 0)
    {
      ::RaiseException(1, EXCEPTION_NONCONTINUABLE, 0, 0);
        return false;
    }

    hsrv = ::OpenService(hscm, SysName, DELETE);

    if(hsrv == 0) 
    {
      ::CloseServiceHandle(hscm);
      ::RaiseException(2, EXCEPTION_NONCONTINUABLE, 0, 0);
        return false;
    }

    if(_stop) 
    {
        SERVICE_STATUS status;
      ::ControlService(hsrv, SERVICE_CONTROL_STOP, &status);
    }

    bool rc = ::DeleteService(hsrv) > 0;

  ::CloseServiceHandle(hsrv);
  ::CloseServiceHandle(hscm);
    return rc;
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__
