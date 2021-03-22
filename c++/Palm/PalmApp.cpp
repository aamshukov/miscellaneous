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

#ifndef __PALM_APP_INC__
#   include <PalmApp.inc>
#endif

#ifdef __PALM_OS__

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class PalmApp
// ----- -------
PalmApp::PalmApp()
       : LaunchCode(0), ExitCode(errNone), Flags(0), Timeout(PalmApp::eTimeout)
{
    // only one instance of the PalmApp object is exist
}

PalmApp::~PalmApp()
{
}

void PalmApp::InitInstance()
{
}

void PalmApp::ExitInstance()
{
}

bool PalmApp::Idle(int32 _count)
{
    return _count < 1;
}

bool PalmApp::PretranslateI()
{
    return false;
}

bool PalmApp::PretranslateII()
{
    return false;
}

bool PalmApp::AppHandleEvent()
{
    // MUST be called from derived classes!
    if(CurrEvent.eType == frmLoadEvent)
    {
        FormType* form = ::FrmInitForm(CurrEvent.data.frmLoad.formID);

        if(form != null)
        {
          ::FrmSetActiveForm(form);
          ::FrmSetEventHandler(form, PalmEventManager::DispatchEvent);
            return true;
        }
    }
    return false;
}

bool PalmApp::IsIdleEvent()
{
    // check hard keys
    bool power_off = false;

    if(CurrEvent.eType == keyDownEvent)
    {
        if(CurrEvent.data.keyDown.modifiers & commandKeyMask && (CurrEvent.data.keyDown.chr == autoOffChr || CurrEvent.data.keyDown.chr == hardPowerChr))
        {
            power_off = true;
        }
    }
    return power_off == false && CurrEvent.eType != ctlRepeatEvent && CurrEvent.eType != sclRepeatEvent;
}

#pragma stack_cleanup on

void PalmApp::Run()
{
    volatile bool idle = true;
    volatile int32 count = 0;

    // clean up ...
  ::WinSetActiveWindow(0);

    for(;;)
    {
        while(idle && !::EvtEventAvail() && !::EvtSysEventAvail(false))
        {
            if(!Idle(count++))
            {
                idle = false;
            }
        }

        do
        {
            if(!RetriveEvent())
            {
                return;
            }

            if(IsIdleEvent())
            {
                idle = true, count = 0;
            }
        }
        while(::EvtEventAvail() || !::EvtSysEventAvail(false));
    }
}

bool PalmApp::RetriveEvent()
{
  ::EvtGetEvent(&CurrEvent, GetTimeout());

#ifdef __PROCESS_NIL_EVENT__
    if(CurrEvent.eType == nilEvent)
    {
        // something wrong so stop & quit
        ExitCode = PalmApp::eUnknownCode;
        return false;
    }
#endif

    if(CurrEvent.eType == appStopEvent)
    {
        // stop & quit
        return false;
    }

    if(!PretranslateI())
    {
        if(!::SysHandleEvent(&CurrEvent))
        {
            if(!PretranslateII())
            {
                uint16 err;

                if(!::MenuHandleEvent(null, &CurrEvent, &err))
                {
                    if(!AppHandleEvent())
                    {
                      ::FrmDispatchEvent(&CurrEvent); 
                    }
                }
            }
        }
    }
    return true;
}

#pragma stack_cleanup off

uint32 PalmApp::PilotMain(uint16 _command, void* _command_pbp, uint16 _flags)
{
    // setup
    SetLaunchCode(_command);
    SetFlags(_flags);
    SetCommandPBP(_command_pbp);
    SetExitCode(errNone);

    // let's start
    try
    {
        InitInstance();

        if(ExitCode == PalmApp::eOk)
        {
            Run();
        }

        ExitInstance();
    }
    catch(PalmError&)
    {
        NON_FATAL_ERROR("The Application unexpectedly terminated");
    }
    catch(...)
    {
        FATAL_ERROR("The Application unexpectedly terminated");
    }
    return ExitCode;
}

void PalmApp::Quit()
{
    EventType event;
    event.eType = appStopEvent;
  ::EvtAddEventToQueue(&event);
}
////////////////////////////////////////////////////////////////////////////////////////
// class XPalmApp
// ----- --------
void PalmApp::XPalmApp::LoadErrorDescriptions()
{
    // base class
    PalmError::LoadErrorDescriptions();
}
////////////////////////////////////////////////////////////////////////////////////////
// Stub
// ----
extern "C" uint32 PilotMainCStub(uint16, void*, uint16)
{
    return errNone;
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__

