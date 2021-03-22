////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __TIMEOUT_MANAGER_H__
#define __TIMEOUT_MANAGER_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class TimeoutManager
// ----- --------------
class __DECLSPEC__ TimeoutManager : public Singleton<TimeoutManager>
{
    // timeouts in msecs
    private:
     uint       TriggerTimeout; // trigger timeout
     uint       ReadPolling;    // read polling
     uint       NetTimeout;     // network (send/receive) timeout
     uint       ThreadTL;       // thread time to live
     uint       MutexTimeout;   // mutex timeout
    public:
     // ctor/dtor
                TimeoutManager();
               ~TimeoutManager();

     // access
     uint       GetTriggerTimeout()     const;
     void       SetTriggerTimeout(uint);

     uint       GetReadPolling()        const;
     void       SetReadPolling(uint);

     uint       GetNetTimeout()         const;
     void       SetNetTimeout(uint);

     uint       GetThreadTL()           const;
     void       SetThreadTL(uint);

     uint       GetMutexTimeout()       const;
     void       SetMutexTimeout(uint);
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __TIMEOUT_MANAGER_H__
