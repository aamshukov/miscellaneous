////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
// this code is borrowed and adapted from the following book:
// "Professional NT Services" by Kevin Miller
// 1998 Wrox Press
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __NTSERVICE_H__
#define __NTSERVICE_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class NTService
// ----- ---------
class __DECLSPEC__ NTService
{
    protected:

    enum EConst
    {
        EventNumber = 4
    };

    enum EEvents
    {
        StopEv,
        PauseEv,
        ContinueEv,
        ShutdownEv
    };

    protected:

    typedef AutoPtrArray<tchar>             _Array;
    typedef Synchronization::ThreadMutex<>  _Mutex;
    typedef Synchronization::Event<>        _Event;

    _Mutex                  Mutex;

    _Event                  StopEvent;
    _Event                  PauseEvent;
    _Event                  ContinueEvent;
    _Event                  ShutdownEvent;

     SERVICE_STATUS_HANDLE  Handle;

     uint                   State;
     uint                   ControlsAccepted;
     uint                   Checkpoint;
     uint                   WaitHint;
     uint                   Type;

    _Array                  SysName;
    _Array                  DisplayName;

     HANDLE                 Monitor; // watcher thread
    protected:
     // protocol
     virtual void           Initialize();
     virtual void           ParseArgs(uint, tchar**);

     virtual void           Run()                           = 0;
     virtual void           Stop()                          = 0;
     virtual void           Pause();
     virtual void           Continue();
     virtual void           Shutdown();
     virtual void           UserCommand(uint);
     //
     void                   SetStatus(uint, uint = -1, uint = -1, uint = -1, uint = 0, uint = 0);
     uint                   ErrorHandler(const tchar*, bool = true, bool = true, uint = ::GetLastError());
     void                   ReportError(const tchar*,  bool = true);
     //
     virtual void           LaunchMonitor(LPTHREAD_START_ROUTINE);
     virtual uint           MonitorProc();
    public:
     // ctor/dtor
                            NTService(const tchar*, const tchar*, uint = SERVICE_WIN32_OWN_PROCESS);
                           ~NTService();
     // access
     SERVICE_STATUS_HANDLE  GetHandle()             const;
     uint                   GetState()              const;
     uint                   GetControlsAccepted()   const;
     uint                   GetCheckpoint()         const;
     uint                   GetWaitHint()           const;
     uint                   GetType()               const;
     const tchar*           GetSysName()            const;
     const tchar*           GetDisplayName()        const;
     HANDLE                 GetMonitor()            const;

     // entry point
     void                   ServiceMain(uint, tchar**, LPHANDLER_FUNCTION, LPTHREAD_START_ROUTINE);
     void                   Handler(uint);
};
////////////////////////////////////////////////////////////////////////////////////////
// macros
// ------
#define DECLARE_SERVICE(_class_name, _service_name)                                                         \
        public:                                                                                             \
         static _class_name##* This;                                                                        \
         static void WINAPI _service_name##Main(uint, tchar**);                                             \
         static void WINAPI _service_name##Handler(uint);                                                   \
         static uint WINAPI _service_name##MonitorProc(void*);
//
#define IMPLEMENT_SERVICE(_class_name, _service_name)                                                       \
        _class_name##* _class_name::This = null;                                                            \
        void WINAPI _class_name::_service_name##Main(uint _argc, tchar** _argv)                             \
        {                                                                                                   \
            This->ServiceMain(_argc, _argv,                                                                 \
                             reinterpret_cast<LPHANDLER_FUNCTION>(_service_name##Handler),                  \
                             reinterpret_cast<LPTHREAD_START_ROUTINE>(_service_name##MonitorProc));         \
        }                                                                                                   \
        void WINAPI _class_name::_service_name##Handler(uint _control)                                      \
        {                                                                                                   \
            This->Handler(_control);                                                                        \
        }                                                                                                   \
        uint WINAPI _class_name::_service_name##MonitorProc(void* _par)                                     \
        {                                                                                                   \
            return This->MonitorProc();                                                                     \
        }                                                                                                   \
//
#define BEGIN_SERVICE_MAP                                                                                   \
        SERVICE_TABLE_ENTRY table[] =                                                                       \
        {                                                                                                   \

#define SERVICE_MAP_ENTRY(_class_name, _service_name)                                                       \
        {                                                                                                   \
            _t(#_service_name), reinterpret_cast<LPSERVICE_MAIN_FUNCTION>(_class_name::_service_name##Main) \
        },                                                                                                  \

#define END_SERVICE_MAP                                                                                     \
        {                                                                                                   \
            null, null                                                                                      \
        }                                                                                                   \
        };                                                                                                  \
      ::StartServiceCtrlDispatcher(table);
////////////////////////////////////////////////////////////////////////////////////////
// class NTServiceInstall
// ----- ----------------
class NTServiceInstall
{
    private:

    typedef AutoPtrArray<tchar> _Array;

    _Array      SysName;
    _Array      DisplayName;
    public:
     // ctor/dtor
                NTServiceInstall(const tchar*, const tchar*);
               ~NTServiceInstall();

     // protocol
     bool       IsInstalled()   const;

     bool       Install(uint = SERVICE_WIN32_OWN_PROCESS, uint = SERVICE_DEMAND_START, const tchar* = null, const tchar* = null, const tchar* = null);
     bool       Remove(bool = false);
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __NTSERVICE_H__
