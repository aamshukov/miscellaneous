////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PALM_APP_INL__
#define __PALM_APP_INL__

#ifdef __PALM_OS__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class PalmApp
// ----- -------
__INLINE__ uint16 PalmApp::GetLaunchCode() const
{
    return LaunchCode;
}

__INLINE__ void PalmApp::SetLaunchCode(uint16 _code)
{
    LaunchCode = _code;
}

__INLINE__ uint16 PalmApp::GetFlags() const
{
    return Flags;
}

__INLINE__ void PalmApp::SetFlags(uint16 _flags)
{
    Flags = _flags;
}

__INLINE__ uint32 PalmApp::GetExitCode() const
{
    return ExitCode;
}

__INLINE__ void PalmApp::SetExitCode(uint32 _code)
{
    ExitCode = _code;
}

__INLINE__ const void* PalmApp::GetCommandPBP() const
{
    return CommandPBP;
}

__INLINE__ void PalmApp::SetCommandPBP(const void* _pbp)
{
    CommandPBP = _pbp;
}

__INLINE__ const EventType& PalmApp::GetCurrEvent() const
{
    return CurrEvent;
}

__INLINE__ int32 PalmApp::GetTimeout() const
{
    return Timeout;
}

__INLINE__ void PalmApp::SetTimeout(int32 _timeout)
{
    Timeout = _timeout;
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__
#endif // __PALM_APP_INL__
