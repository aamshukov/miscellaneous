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

#ifndef __TASKSCHEDULE_INC__
#   include <TaskSchedule.inc>
#endif

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class TaskSchedule
// ----- ------------
TaskSchedule::TaskSchedule(uint _timeout)
            : Timeout(_timeout), Shutdown(false), Map(KeyExtractor, Comparator)
{
}

TaskSchedule::~TaskSchedule()
{
}

void TaskSchedule::Register(TaskHandler* _handler)
{
    if(_handler == null)
    {
        return;
    }
    //
    Mutex.Acquire(5000);
    Map.Insert(_handler);
    Mutex.Release();
}

TaskSchedule::TaskHandler* TaskSchedule::Unregister(const tchar* _key)
{
    if(_key == null)
    {
        return null;
    }
    //
    Mutex.Acquire(5000);
    TaskHandler* handler = (TaskHandler*)Map.Search(_key);

    if(handler != null)
    {
        Map.Remove(handler, false);
    }

    Mutex.Release();
    return handler;
}

int TaskSchedule::Run()
{
    try
    {
        SetPriority(THREAD_PRIORITY_IDLE);

        while(!Shutdown)
        {
            BinaryTreeIterator<TaskHandler, pctchar, _KeyExtractor, _Comparator> iter(Map.GetLeftMostIter(Map.GetRoot()));

            for(; iter; iter++)
            {
                (*iter).ProcessTask();
            }
            //
            Sleep(Timeout); // yield processor's time
        }
        DoShutdown();
    }
    catch(...)
    {
        DoShutdown();
        return -1;
    }
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////
// class TaskHandler
// ----- -----------
TaskSchedule::TaskHandler::TaskHandler(const tchar* _name, Time _time, ushort _type)
                         : Taskname(StrClone(_name)), StartTime(_time), TriggerType(_type)
{
}

TaskSchedule::TaskHandler::~TaskHandler()
{
}

bool TaskSchedule::TaskHandler::ProcessTask()
{
    // if you are going to use a time consuming procedure,
    // it's better to switch to asynchronous mode (post a message)
    return true;
}
////////////////////////////////////////////////////////////////////////////////////////
// class XTaskSchedule
// ----- -------------
TaskSchedule::XTaskSchedule::XTaskSchedule(uint _error) : X(_error)
{
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

