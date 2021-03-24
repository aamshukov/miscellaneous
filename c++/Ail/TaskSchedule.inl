////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __TASKSCHEDULE_INL__
#define __TASKSCHEDULE_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class TaskSchedule
// ----- ------------
__INLINE__ bool TaskSchedule::IsShutdown() const
{
    return Shutdown;
}

void TaskSchedule::DoShutdown()
{
    Shutdown = true;
}
////////////////////////////////////////////////////////////////////////////////////////
// class TaskHandler
// ----- -----------
pctchar& TaskSchedule::TaskHandler::GetKey() const
{
    return (pctchar&)Taskname;
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __TASKSCHEDULE_INL__

