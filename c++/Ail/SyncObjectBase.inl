////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __SYNCOBJECTBASE_INL__
#define __SYNCOBJECTBASE_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class SyncObjectBase
// ----- --------------
__INLINE__ void SyncObjectBase::Assert()
{
    if(Handle == 0)
    {
        throw SyncObjectBase::XSyncObjectBase();
    }
}

__INLINE__ SyncObjectBase::operator HANDLE () const
{
    return Handle;
}

__INLINE__ HANDLE SyncObjectBase::GetHandle() const
{
    return Handle;
}

__INLINE__ bool SyncObjectBase::Lock::WasAquired() const
{
    return SO != null;
} 

__INLINE__ void SyncObjectBase::Lock::Release(bool _relinquish)
{
    if(SO) 
    {
        const_cast<SyncObjectBase*>(SO)->Release();

        if(_relinquish)
        {
            SO = null;
        }
    }
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __SYNCOBJECTBASE_INL__
