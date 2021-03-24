////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __AIL_H__
#   include <ail.hpp>
#endif

#ifndef __SYNCOBJECTBASE_INC__
#   include <SyncObjectBase.inc>
#endif

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class SyncObjectBase
// ----- --------------
SyncObjectBase::SyncObjectBase() : Handle(0)
{
}

SyncObjectBase::~SyncObjectBase()
{
    if(Handle)
    {
        ::CloseHandle(Handle);

        Handle = null;
    }
}

SyncObjectBase::Lock::Lock(const SyncObjectBase& _o, uint _timeout, bool _alertable) : SO(null)
{
    if(::WaitForSingleObjectEx(_o, _timeout, _alertable) == 0)
    {
        SO = &_o;
    }
}

SyncObjectBase::Lock::~Lock()
{
    Release();
}

SyncObjectBase::XSyncObjectBase::XSyncObjectBase(uint _error) : X(_error)
{
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__
