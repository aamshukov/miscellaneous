////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __TIME_H__
#define __TIME_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class Time
// ----- ----
// In 1582, Pope Gregory XII decided to trim the extra days the Julian calendar ...
// October 4, 1582 ---> October 15, 1582
// Unix version: September 2, 1752 ---> September 14, 1752 ...
// See "Computer LANGUAGE", December, 1990, pp. 57-62 ...
//
// Syntax:
//  Year +=...      
//  Month 1-12      
//  Day 1-31        
//  DayOfWeek 1-7:  1 sunday, 2 monday, ... , 7 saturday
//  Hour 0-23       
//  Minute 0-59     
//  Second 0-59     
//
#undef GetCurrentTime

class __DECLSPEC__ Time
{
    public:

    enum ESecond
    {
        SecondsInMinute = 60,
        SecondsInHour   = 3600,
        SecondsInDay    = 86400,

        // syntax is as follows:
        //  long pctime = ntohl(nettime);
        //  pctime -= Seconds1900;
        //  char* atime = ctime(&pctime);
        Seconds1900     = 2208988800L   // secs since 1900 up to 1970
    };

    public:
     typedef ushort         Year;
     typedef short          Month;
     typedef int            Day;
     typedef uint           Hour;
     typedef long           Minute;
     typedef ulong          Second;
    private:
     int64                  Value;

     static const tchar*    Months[12];
     static const tchar*    MonthsAbbr[12];
     static const tchar*    WeekDays[7];
     static const tchar*    WeekDaysAbbr[7];

     static const Day       DaysInMonth[12];
     static const Day       FirstDayOfEachMonth[12];
    protected:
     static int             DateToNumber(Year, Month, Day);
     static void            NumberToDate(int, Year&, Month&, Day&);
    public:
     // construct/destruct
                            Time();
                            Time(Year, Month = 1, Day = 1, Hour = 0, Minute = 0, Second = 0);
                            Time(int64);
                            Time(const Time&);
     virtual               ~Time();

     // common
     int64                  GetTime()                       const;

     static bool            IsDateValid(Year, Month, Day);
     bool                   IsBetween(const Time&, const Time&) const;

     static Time            GetCurrentTime();
     static void            GetCurrentTime(Year&, Month&, Day&, Hour&, Minute&, Second&);

     void                   SetupTime(Year, Month = 1, Day = 1, Hour = 0, Minute = 0, Second = 0);
     void                   SetupRealTime(Hour = 0, Minute = 0, Second = 0);

     const Time&            operator = (const Time&);

     Time                   operator + (const Time&);
     Time                   operator - (const Time&);

     void                   operator ++ ();
     void                   operator -- ();

     bool                   operator <  (const Time&)       const;
     bool                   operator <= (const Time&)       const;
     bool                   operator >  (const Time&)       const;
     bool                   operator >= (const Time&)       const;
     bool                   operator == (const Time&)       const;
     bool                   operator != (const Time&)       const;

     // year
     Year                   GetYear();

     static bool            IsYearLeap(Year);

     // month
     Month                  GetMonth();

     static const tchar**   GetMonths();
     static const tchar**   GetMonthsAbbr();

     const tchar*           GetNameOfMonth(Time::Month = 0, bool = true);

     // day
     Day                    GetDay();

     Day                    GetDayOfYear();
     Day                    GetFirstDayOfMonth(Month);

     static const Day&      GetFirstDayOfEachMonth();
     static const Day&      GetDaysInMonth();

     const tchar*           GetNameOfDay(bool = true);

     Day                    GetDayOfWeek();
     static Day             GetDayOfWeek(Year, Month, Day);

     static const tchar**   GetWeekDays();
     static const tchar**   GetWeekDaysAbbr();

     Time                   operator +  (Day);
     Time                   operator -  (Day);

     void                   operator += (Day);
     void                   operator -= (Day);

     // hour
     Hour                   GetHours();

     Time                   operator +  (Hour);
     Time                   operator -  (Hour);

     void                   operator += (Hour);
     void                   operator -= (Hour);

     // minute
     Minute                 GetMinutes();

     Time                   operator +  (Minute);
     Time                   operator -  (Minute);

     void                   operator += (Minute);
     void                   operator -= (Minute);

     // second
     Second                 GetSeconds();

     Time                   operator +  (Second);
     Time                   operator -  (Second);

     void                   operator += (Second);
     void                   operator -= (Second);

     //
     // Syntax:
     //  M    - a number without a leading 0 (zero) for single-digit months.
     //  MM   - a number with a leading 0 (zero) for single-digit months.
     //  MMM  - a three-letter abbreviation.
     //  MMMM - the full name of the month.
     //  d    - a number without a leading 0 (zero) for single-digit days.
     //  dd   - a number with a leading 0 (zero) for single-digit days.
     //  ddd  - a three-letter abbreviation.
     //  dddd - the full name of the day of the week.
     //  yy   - two digits with a leading 0 (zero) for years.
     //  yyyy - four digits.
     //  h    - without a leading 0 (zero) for single-digit hours 0-12.
     //  H    - without a leading 0 (zero) for single-digit hours 0-24.
     //  hh   - with a leading 0 (zero) for single-digit hours 0-12.
     //  HH   - with a leading 0 (zero) for single-digit hours 0-24.
     //  m    - without a leading 0 (zero) for single-digit minutes.
     //  mm   - with a leading 0 (zero) for single-digit minutes.
     //  s    - without a leading 0 (zero) for single-digit second.
     //  ss   - with a leading 0 (zero) for single-digit seconds.
     //  cc   - with a leading 0 (zero) for single-digit hundred seconds.
     //  A    - AM/PM
     //  a    - am/pm
     //  P    - A/P
     //  p    - a/p
     static const tchar* _MM_dd_yy_;
     static const tchar* _MM_dd_yyyy_;
     static const tchar* _dddd_MMMM_dd_yyyy_;
     static const tchar* _dd_MMMM_yyyy_;
     static const tchar* _MMM_dd_yyyy_;
     static const tchar* _MMMM_dd_yyyy_;
     static const tchar* _d_MMM_yy_;
     static const tchar* _MMMM_yy_;
     static const tchar* _MMM_yy_;
     static const tchar* _MM_dd_yy_hh_mm_A_;
     static const tchar* _MM_dd_yy_hh_mm_ss_A_;
     static const tchar* _MM_dd_yyyy_hh_mm_ss_A_;
     static const tchar* _hh_mm_A_;
     static const tchar* _hh_mm_ss_A_;
     static const tchar* _HH_mm_;
     static const tchar* _HH_mm_ss_;
     //
     void                   GetTimeAsString(tchar*, const tchar*);
    public:

    class __DECLSPEC__ XTime : public X
    {
        public:
            XTime(uint = X::Failure);
    };

    friend class XTime;
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __TIME_H__
