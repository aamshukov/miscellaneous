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

#ifndef __TIMEOUT_MANAGER_INC__
#   include <TimeoutManager.inc>
#endif

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class TimeoutManager
// ----- --------------
TimeoutManager::TimeoutManager()
              : TriggerTimeout(1000),
                ReadPolling(1000),
                NetTimeout(20000) // 20 secs
{
}

TimeoutManager::~TimeoutManager()
{
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__
