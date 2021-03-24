////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __EVENT_H__
#define __EVENT_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class Event
// ----- -----
class __DECLSPEC__ Event : public SyncObjectBase
{
    private:
                    Event(const Event&);
     const Event&   operator = (const Event&);
    public:
                    Event(bool = false, bool = false, const tchar* = null, SECURITY_ATTRIBUTES* = null);
                    Event(const tchar*, bool, uint = SEMAPHORE_ALL_ACCESS);
                    Event(HANDLE);

     void           Set();
     void           Reset();
     void           Pulse();

     virtual void   Release();
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __EVENT_H__
