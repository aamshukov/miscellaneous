////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __RR_DISPATCHER_INL__
#define __RR_DISPATCHER_INL__

#pragma once

__BEGIN_NAMESPACE__
__BEGIN_RRT_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class TEntry
// ----- ------
__INLINE__ uint& RRDispatcher::DEntry::GetKey() const
{
    return (uint&)Transaction->GetKey(); // Transaction != 0
}
////////////////////////////////////////////////////////////////////////////////////////
// class RRDispatcher
// ----- ------------
__INLINE__ ushort RRDispatcher::GetInterleave() const
{
    return Interleave;
}

__INLINE__ void RRDispatcher::SetInterleave(ushort _interleave)
{
    Interleave = _interleave;
}

__INLINE__ uint RRDispatcher::GetConnectionCount() const
{
    return NetManagers.GetCount();
}

__INLINE__ uint RRDispatcher::GetMaxConnections() const
{
    return MaxConnections;
}

__INLINE__ void RRDispatcher::SetMaxConnections(uint _count)
{
    MaxConnections = _count;
}
////////////////////////////////////////////////////////////////////////////////////////
__END_RRT_NAMESPACE__
__END_NAMESPACE__

#endif // __RR_DISPATCHER_INL__
