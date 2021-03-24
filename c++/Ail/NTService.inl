////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __NTSERVICE_INL__
#define __NTSERVICE_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class NTService
// ----- ---------
__INLINE__ SERVICE_STATUS_HANDLE NTService::GetHandle() const
{
    return Handle;
}

__INLINE__ uint NTService::GetState() const
{
    return State;
}

__INLINE__ uint NTService::GetControlsAccepted() const
{
    return ControlsAccepted;
}

__INLINE__ uint NTService::GetCheckpoint() const
{
    return Checkpoint;
}

__INLINE__ uint NTService::GetWaitHint() const
{
    return WaitHint;
}

__INLINE__ uint NTService::GetType() const
{
    return Type;
}

__INLINE__ const tchar* NTService::GetSysName() const
{
    return static_cast<const tchar*>(SysName);
}

__INLINE__ const tchar* NTService::GetDisplayName() const
{
    return static_cast<const tchar*>(DisplayName);
}

__INLINE__ HANDLE NTService::GetMonitor() const
{
    return Monitor;
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __NTSERVICE_INL__
