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

#ifndef __COM_MODULE_INC__
#   include <ComModule.inc>
#endif

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class ComModule
// ----- ---------
ComModule::ComModule()
         : LockCount(0), HModule(0)
{
}

ComModule::~ComModule()
{
}

refcnt ComModule::GetLockCount() const
{
    return LockCount;
}

refcnt ComModule::Lock()
{
    return InterlockedIncrement(reinterpret_cast<long*>(&LockCount));
}

refcnt ComModule::Unlock()
{
    return InterlockedDecrement(reinterpret_cast<long*>(&LockCount));
}

HMODULE ComModule::GetHModule() const
{
    return HModule;
}

void ComModule::SetHModule(HMODULE _module)
{
    HModule = _module;
}

ComModule::operator HMODULE ()
{
    return HModule;
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__
