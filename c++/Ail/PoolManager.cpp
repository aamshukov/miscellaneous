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

#ifndef __POOL_MANAGER_INC__
#   include <PoolManager.inc>
#endif

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class XPoolManager
// ----- ------------
XPoolManager::XPoolManager(uint _error) : X(_error)
{
}

XPoolManager::~XPoolManager()
{
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__
