////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __SYNCOBJECT_INL__
#define __SYNCOBJECT_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class SyncObject
// ----- ----------
__INLINE__ const SyncObject& SyncObject::operator = (const SyncObject&)
{
    return *this;
}

__INLINE__ const CriticalSection& SyncObject::Lock::GetCriticalSection(const SyncObject* _o)
{
    if(_o == null)
    {
        throw SyncObject::XSyncObject();
    }
    return _o->CS;
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __SYNCOBJECT_INL__
