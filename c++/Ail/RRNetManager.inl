////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __RR_NET_MANAGER_INL__
#define __RR_NET_MANAGER_INL__

#pragma once

__BEGIN_NAMESPACE__
__BEGIN_RRT_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class RRNetManager
// ----- ------------
__INLINE__ const byte* RRNetManager::GetKeyData() const
{
    return Key;
}

__INLINE__ uint RRNetManager::AddReference()
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    //
    return ++Reference;
}

__INLINE__ uint RRNetManager::ReleaseReference()
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    //
    if(--Reference == 0)
    {
        delete this;
        return 0;
    }
    return ++Reference;
}

__INLINE__ const IPv4Address& RRNetManager::GetKey() const
{
    return Connection.GetRemoteAddress();
}

__INLINE__ bool RRNetManager::IsClientSide() const
{
    return Side == RRNetManager::ClientSide;
}

__INLINE__ StreamSocket& RRNetManager::GetConnection() const
{
    return const_cast<StreamSocket&>(Connection);
}

__INLINE__ uint RRNetManager::GetTimeout() const
{
    return Timeout;
}

__INLINE__ void RRNetManager::SetTimeout(uint _timeout)
{
    Timeout = _timeout;
}

__INLINE__ ushort RRNetManager::GetInterleave() const
{
    return Interleave;
}

__INLINE__ void RRNetManager::SetInterleave(ushort _interleave)
{
    Interleave = _interleave;
}
////////////////////////////////////////////////////////////////////////////////////////
__END_RRT_NAMESPACE__
__END_NAMESPACE__

#endif // __RR_NET_MANAGER_INL__
