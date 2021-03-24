////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __TIME_INL__
#define __TIME_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class Time
// ----- ----
__INLINE__ int64 Time::GetTime() const
{
    return Value;
}

__INLINE__ bool Time::operator < (const Time& _other) const
{
    return Value < _other.Value;
}

__INLINE__ bool Time::operator <= (const Time& _other) const
{
    return Value <= _other.Value;
}

__INLINE__ bool Time::operator > (const Time& _other) const
{
    return Value > _other.Value;
}

__INLINE__ bool Time::operator >= (const Time& _other) const
{
    return Value >= _other.Value;
}

__INLINE__ bool Time::operator == (const Time& _other) const
{
    return Value == _other.Value;
}

__INLINE__ bool Time::operator != (const Time& _other) const
{
    return Value != _other.Value;
}

__INLINE__ const Time& Time::operator = (const Time& _other)
{
    if(this != &_other)
    {
        Value = _other.Value;
    }
    return *this;
}

__INLINE__ Time Time::operator + (const Time& _other)
{
    return Time(Value+_other.Value);
}

__INLINE__ Time Time::operator + (Day _days)
{
    return Time(Value+_days*SecondsInDay);
}

__INLINE__ Time Time::operator + (Hour _hours)
{
    return Time(Value+_hours*SecondsInHour);
}

__INLINE__ Time Time::operator + (Minute _minutes)
{
    return Time(Value+_minutes*SecondsInMinute);
}

__INLINE__ Time Time::operator + (Second _seconds)
{
    return Time(Value+_seconds);
}

__INLINE__ Time Time::operator - (const Time& _other)
{
    return Time(Value-_other.Value);
}

__INLINE__ Time Time::operator - (Day _days)
{
    return Time(Value-_days*SecondsInDay);
}

__INLINE__ Time Time::operator - (Hour _hours)
{
    return Time(Value-_hours*SecondsInHour);
}

__INLINE__ Time Time::operator - (Minute _minutes)
{
    return Time(Value-_minutes*SecondsInMinute);
}

__INLINE__ Time Time::operator - (Second _seconds)
{
    return Time(Value-_seconds);
}

__INLINE__ void Time::operator ++ ()
{
    ++Value;
}

__INLINE__ void Time::operator -- ()
{
    --Value;
}

__INLINE__ void Time::operator += (Day _days)
{
    Value += _days;
}

__INLINE__ void Time::operator += (Hour _hours)
{
    Value += _hours*SecondsInHour;
}

__INLINE__ void Time::operator += (Minute _minutes)
{
    Value += _minutes*SecondsInMinute;
}

__INLINE__ void Time::operator += (Second _seconds)
{
    Value += _seconds;
}

__INLINE__ void Time::operator -= (Day _days)
{
    Value -= _days*SecondsInDay;
}

__INLINE__ void Time::operator -= (Hour _hours)
{
    Value -= _hours*SecondsInHour;
}

__INLINE__ void Time::operator -= (Minute _minutes)
{
    Value -= _minutes*SecondsInMinute;
}

__INLINE__ void Time::operator -= (Second _seconds)
{
    Value -= _seconds;
}

__INLINE__ bool Time::IsBetween(const Time& _t1, const Time& _t2) const
{
    return Value >= _t1.Value && Value <= _t2.Value;
}

__INLINE__ const tchar** Time::GetMonths()
{
    return reinterpret_cast<const tchar**>(&Time::Months);
}

__INLINE__ const tchar** Time::GetMonthsAbbr()
{
    return reinterpret_cast<const tchar**>(&Time::MonthsAbbr);
}

__INLINE__ const tchar** Time::GetWeekDays()
{
    return reinterpret_cast<const tchar**>(&Time::WeekDays);
}

__INLINE__ const tchar** Time::GetWeekDaysAbbr()
{
    return reinterpret_cast<const tchar**>(&Time::WeekDaysAbbr);
}

__INLINE__ const Time::Day& Time::GetDaysInMonth()
{
    return reinterpret_cast<const Day&>(Time::DaysInMonth);
}

__INLINE__ const Time::Day& Time::GetFirstDayOfEachMonth()
{
    return reinterpret_cast<const Day&>(Time::FirstDayOfEachMonth);
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __TIME_INL__
