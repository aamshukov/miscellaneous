////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __TIMEOUT_MANAGER_INL__
#define __TIMEOUT_MANAGER_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class TimeoutManager
// ----- --------------
__INLINE__ uint TimeoutManager::GetTriggerTimeout() const
{
    return TriggerTimeout;
}

__INLINE__ void TimeoutManager::SetTriggerTimeout(uint _timeout)
{
    TriggerTimeout = _timeout;
}

__INLINE__ uint TimeoutManager::GetReadPolling() const
{
    return ReadPolling;
}

__INLINE__ void TimeoutManager::SetReadPolling(uint _timeout)
{
    ReadPolling = _timeout;
}

__INLINE__ uint TimeoutManager::GetNetTimeout() const
{
    return NetTimeout;
}

__INLINE__ void TimeoutManager::SetNetTimeout(uint _timeout)
{
    NetTimeout = _timeout;
}

__INLINE__ uint TimeoutManager::GetThreadTL() const
{
    return ThreadTL;
}

__INLINE__ void TimeoutManager::SetThreadTL(uint _timeout)
{
    ThreadTL = _timeout;
}

__INLINE__ uint TimeoutManager::GetMutexTimeout() const
{
    return MutexTimeout;
}

__INLINE__ void TimeoutManager::SetMutexTimeout(uint _timeout)
{
    MutexTimeout = _timeout;
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __TIMEOUT_MANAGER_INL__
