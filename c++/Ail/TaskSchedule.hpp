////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __TASKSCHEDULE_H__
#define __TASKSCHEDULE_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class TaskSchedule
// ----- ------------
class __DECLSPEC__ TaskSchedule : public Thread, protected Singleton<TaskSchedule>
{
    public:

    class __DECLSPEC__ TaskHandler : public TreeNodeBase<TaskHandler, pctchar>
    {
        friend class TaskSchedule;

        typedef AutoPtrArray<tchar> _Array;

        private:

        enum EMonth
        {
            TaskJanuary     = 0x0001,
            TaskFebruary    = 0x0002,
            TaskMarch       = 0x0004,
            TaskApril       = 0x0008,
            TaskMay         = 0x0010,
            TaskJune        = 0x0020,
            TaskJuly        = 0x0040,
            TaskAugust      = 0x0080,
            TaskSeptember   = 0x0100,
            TaskOctober     = 0x0200,
            TaskNovember    = 0x0400,
            TaskDecember    = 0x0800
        };

        enum EWeekday
        { 
            TaskSunday      = 0x0001,
            TaskMonday      = 0x0002,
            TaskTuesday     = 0x0004,
            TaskWednesday   = 0x0008,
            TaskThursday    = 0x0010,
            TaskFriday      = 0x0020,
            TaskSaturday    = 0x0040
        };

        enum EPeriod
        {
            TaskFirstWeek   = 0x01,
            TaskSecondWeek  = 0x02,
            TaskThirdWeek   = 0x04,
            TaskFourthWeek  = 0x08,
            TaskLastWeek    = 0x10
        };

        enum ETrigger
        {
            TriggerTypeUnknown      = 0x00,
            TriggerTypeOnce         = 0x01,
            TriggerTypeDaily        = 0x02,
            TriggerTypeWeekly       = 0x04,
            TriggerTypeMonthlyDate  = 0x08,
            TriggerTypeMonthlyDOW   = 0x10
        };

        struct _Daily
        {
            uint DaysInterval;
        };

        struct _Weekly
        {
             // the interval, in weeks, between invocations of a task
             ushort DOW;  // describes weeks day(s) when the task runs
             uint   WeeksInterval;
        };

        struct _MonthlyDate
        {
             // the day of the month the task will start
             uint   Days;   // bit 0 corresponds first day of the month, bit 1 to the second, and so on
             ushort Months; // describes month(s) when the task runs
        };

        struct _MonthlyDOW
        {
             // monthly day of the week
             ushort Week;
             ushort DOW;
             ushort Months;
        };

        union _TriggerData
        {
           _Daily       Dayly;
           _Weekly      Weekly;
           _MonthlyDate Monthlydate;
           _MonthlyDOW  MonthlyDayOfTheWeek;
        };

        private:
        _Array          Taskname;
         Time           StartTime;
         ushort         TriggerType;
        _TriggerData    TriggerData;
        protected:
         // protocol
         virtual bool   ProcessTask();
        public:
         // ctor/dtor
                        TaskHandler(const tchar*, Time = Time::GetCurrentTime(), ushort = TaskHandler::TriggerTypeDaily);
         virtual       ~TaskHandler();

         // access
         pctchar&       GetKey()            const;
         const tchar*   GetTaskname()       const;
         Time           GetStartTime()      const;
         ushort         GetTriggerType()    const;
    };

    private:

    template <typename _T, typename _Key> struct KeyExtractor
    {
        const _Key& operator () (const _T& _val) const { return _val.GetKey(); }
    };

    template <typename _Key> struct Comparator
    {
        int operator () (const _Key& _k1, const _Key& _k2) const { return StrCompare(_k1, _k2); }
    };
    //
    typedef Synchronization::NullThreadMutex<>              _NullMutex;
    typedef KeyExtractor<TaskHandler, pctchar>              _KeyExtractor;
    typedef Comparator<pctchar>                             _Comparator;
    typedef AVLTree<TaskHandler, pctchar, _KeyExtractor, _Comparator, _NullMutex> _Map;

    _Map                Map;
    _KeyExtractor       KeyExtractor;
    _Comparator         Comparator;
     bool volatile      Shutdown;
     uint               Timeout; // in msec
    private:
                        TaskSchedule(const TaskSchedule&);
     TaskSchedule&      operator = (const TaskSchedule&);
    protected:
     virtual int        Run();
    public:
     // ctor/dtor
                        TaskSchedule(uint = 1000);
                       ~TaskSchedule();

     // access
     bool               IsShutdown()    const;
     void               DoShutdown();

     // protocol
     void               Register(TaskHandler*);
     TaskHandler*       Unregister(const tchar*);
    public:

    class __DECLSPEC__ XTaskSchedule : public X
    {
        public:
            XTaskSchedule(uint = X::Failure);
    };

    friend class XTaskSchedule;
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __TASKSCHEDULE_H__

