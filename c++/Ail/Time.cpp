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

#ifndef __TIME_INC__
#   include <Time.inc>
#endif

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class Time
// ----- ----
const tchar* Time::Months[12] =
{
    _t("January"),
    _t("February"),
    _t("March"),
    _t("April"),
    _t("May"),
    _t("June"),
    _t("July"),
    _t("August"),
    _t("September"),
    _t("October"),
    _t("November"),
    _t("December")
};

const tchar* Time::MonthsAbbr[12] =
{
    _t("Jan"),
    _t("Feb"),
    _t("Mar"),
    _t("Apr"),
    _t("May"),
    _t("Jun"),
    _t("Jul"),
    _t("Aug"),
    _t("Sep"),
    _t("Oct"),
    _t("Nov"),
    _t("Dec") 
};

const tchar* Time::WeekDays[7] =
{ 
    _t("Sunday"),
    _t("Monday"),
    _t("Tuesday"),
    _t("Wednesday"),
    _t("Thursday"),
    _t("Friday"),
    _t("Saturday")
};

const tchar* Time::WeekDaysAbbr[7] =
{ 
    _t("Sun"),
    _t("Mon"),
    _t("Tue"),
    _t("Wed"),
    _t("Thu"),
    _t("Fri"),
    _t("Sat")
};

const Time::Day Time::DaysInMonth[12] =
{ 
    31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

const Time::Day Time::FirstDayOfEachMonth[12] =
{
    1, 32, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335
};

const tchar* Time::_MM_dd_yy_               = _t("&MM/&dd/&yy");
const tchar* Time::_MM_dd_yyyy_             = _t("&MM/&dd/&yyyy");
const tchar* Time::_dddd_MMMM_dd_yyyy_      = _t("&dddd, &MMMM &dd, &yyyy");
const tchar* Time::_dd_MMMM_yyyy_           = _t("&dd &MMMM &yyyy");
const tchar* Time::_MMM_dd_yyyy_            = _t("&MMM &dd, &yyyy");
const tchar* Time::_MMMM_dd_yyyy_           = _t("&MMMM &dd, &yyyy");
const tchar* Time::_d_MMM_yy_               = _t("&d-&MMM-&yy");
const tchar* Time::_MMMM_yy_                = _t("&MMMM, &yy");
const tchar* Time::_MMM_yy_                 = _t("&MMM-&yy");
const tchar* Time::_MM_dd_yy_hh_mm_A_       = _t("&MM/&dd/&yy &hh:&mm &A");
const tchar* Time::_MM_dd_yy_hh_mm_ss_A_    = _t("&MM/&dd/&yy &hh:&mm:&ss &A");
const tchar* Time::_MM_dd_yyyy_hh_mm_ss_A_  = _t("&MM/&dd/&yyyy &hh:&mm:&ss &A");
const tchar* Time::_hh_mm_A_                = _t("&hh:&mm &A");
const tchar* Time::_hh_mm_ss_A_             = _t("&hh:&mm:&ss &A");
const tchar* Time::_HH_mm_                  = _t("&HH:&mm");
const tchar* Time::_HH_mm_ss_               = _t("&HH:&mm:&ss");
//
Time::Time() : Value(Time::GetCurrentTime().GetTime())
{
}

Time::Time(Year _year, Month _month, Day _day, Hour _hour, Minute _min, Second _sec)
{
    SetupTime(_year, _month, _day, _hour, _min, _sec);
}

Time::Time(int64 _v)
{
    Value = _v;
}

Time::Time(const Time& _other)
{
    if(this != &_other)
    {
        Value = _other.Value;
    }
}

Time::~Time()
{
    Value = 0; // doesn't matter ! ...
}

bool Time::IsDateValid(Year _year, Month _month, Day _day)
{
    Year  year;
    Month month;
    Day   day;

    int date = DateToNumber(_year, _month, _day);

    NumberToDate(date, year, month, day);
    return (_year == year && _month == month && _day == day);
}

void Time::GetCurrentTime(Year& _year, Month& _month, Day& _day, Hour& _hour, Minute& _min, Second& _sec)
{
    tm*    today;
    time_t ltime;

    time(&ltime);
    today = localtime(&ltime);

    _year  = static_cast<Year>(1900+today->tm_year);
    _month = static_cast<Month>(1+today->tm_mon);
    _day   = static_cast<Day>(today->tm_mday);
    _hour  = static_cast<Hour>(today->tm_hour);
    _min   = static_cast<Minute>(today->tm_min);
    _sec   = static_cast<Second>(today->tm_sec%60);
}

Time Time::GetCurrentTime()
{
    tm*    today;
    time_t ltime;

    time(&ltime);
    today = localtime(&ltime);
    return Time(static_cast<Year>(1900+today->tm_year), static_cast<Month>(1+today->tm_mon), static_cast<Day>(today->tm_mday), static_cast<Hour>(today->tm_hour), static_cast<Minute>(today->tm_min), static_cast<Second>(today->tm_sec%60));
}

void Time::SetupTime(Year _year, Month _month, Day _day, Hour _hour, Minute _min, Second _sec)
{
    if(IsDateValid(_year, _month, _day))
    {
        Value  = DateToNumber(_year, _month, _day);
        Value *= Time::SecondsInDay;
        Value += _hour*Time::SecondsInHour+_min*Time::SecondsInMinute+_sec;
    }
    else
    {
        throw Time::XTime();
    }
}

void Time::SetupRealTime(Hour _hour, Minute _min, Second _sec)
{
    Year   year;
    Month  month;
    Day    day;
    Hour   hour;
    Minute min;
    Second sec;

    GetCurrentTime(year, month, day, hour, min, sec);
    SetupTime(year, month, day, _hour, _min, _sec);
}

// See "Computer LANGUAGE", December, 1990, pp. 57-62 ...
int Time::DateToNumber(Year _year, Month _month, Day _day)
{
    int a, b;

    if(_month <= 2)
    {
        --_year;
        
        _month += 12;
    }

    b = 0;

    if(_year*10000.0+_month*100.0+_day >= 15821015.0)
    {
        a = _year/100;
        b = 2-a+a/4;
    }
    return static_cast<int>(365.25*_year-(_year > 0 ? 0.0 : 0.75)+static_cast<int>(30.6001*(_month+1))+_day+1720994L+b);
}

void Time::NumberToDate(int _date, Year& _year, Month& _month, Day& _day)
{
    // See "Computer LANGUAGE", December, 1990, pp. 57-62 ! ...
    int a, b, c, d, e, z, alpha;
    
    z = _date+1;
    
    if(z < 2299161L)
    {
        a = z;
    }
    else
    {
        alpha = static_cast<int>((z-1867216.25)/36524.25);
        a = z+1+alpha-alpha/4;
    }

    b = static_cast<int>(a+1524);
    c = static_cast<int>((b-122.1)/365.25);
    d = static_cast<int>(365.25*c);
    e = static_cast<int>((b-d)/30.6001);

   _day   = static_cast<Day>(static_cast<int>(b-d-static_cast<int>(30.6001*e)));
   _month = static_cast<Month>(static_cast<int>(e < 13.5 ? e-1 : e-13));
   _year  = static_cast<Year>(static_cast<int>(_month > 2.5 ? c-4716 : c-4715));
}

Time::Year Time::GetYear() 
{
    Year  year;
    Month month;
    Day   day;

    NumberToDate(static_cast<int>(Value/Time::SecondsInDay), year, month, day);
    return year;
}

Time::Month Time::GetMonth()
{
    Year  year;
    Month month;
    Day   day;

    NumberToDate(static_cast<int>(Value/Time::SecondsInDay), year, month, day);
    return month;
}

Time::Day Time::GetDay()
{
    Year  year;
    Month month;
    Day   day;

    NumberToDate(static_cast<int>(Value/Time::SecondsInDay), year, month, day);
    return day;
}

Time::Hour Time::GetHours()
{
    return static_cast<Hour>(Abs((Value%Time::SecondsInDay)/Time::SecondsInHour));
}

Time::Minute Time::GetMinutes()
{
    return static_cast<Minute>(Abs(((Value%Time::SecondsInDay)%Time::SecondsInHour)/Time::SecondsInMinute));
}

Time::Second Time::GetSeconds()
{
    return static_cast<Second>(Abs(((Value%Time::SecondsInDay)%Time::SecondsInHour)%Time::SecondsInMinute));
}

Time::Day Time::GetDayOfYear()
{
    return static_cast<Day>(Abs((Value/Time::SecondsInDay)-DateToNumber(GetYear(), 1, 1)+1));
}

Time::Day Time::GetDayOfWeek(Year _year, Month _month, Day _day)
{
    int date = Abs(DateToNumber(_year, _month, _day));
    return static_cast<Day>(((date+2)%7)+1);
}

Time::Day Time::GetDayOfWeek()
{
    return static_cast<Day>(Abs((((Value/Time::SecondsInDay)+2)%7)+1));
}

Time::Day Time::GetFirstDayOfMonth(Month _month)
{
    if(_month < 1 || _month > 12)
    {
        return 0;
    }

    Day firstday = Time::FirstDayOfEachMonth[_month-1];

    if(_month > 2 && IsYearLeap(GetYear()))
    {
        ++firstday;
    }
    return firstday;
}

bool Time::IsYearLeap(Year _year)
{
    if(_year%4 != 0)
    {
        return false;
    }

    if(_year < 1582) // ! ...
    {
        return true;
    }

    if(_year%100 != 0)
    {
        return true;
    }

    if(_year%400 != 0)
    {
        return false;
    }
    return true;
}


const tchar* Time::GetNameOfDay(bool _flag)
{
    return _flag ? reinterpret_cast<const tchar*>(Time::WeekDays[GetDayOfWeek()-1]) : reinterpret_cast<const tchar*>(Time::WeekDaysAbbr[GetDayOfWeek()-1]);
}

const tchar* Time::GetNameOfMonth(Time::Month _month, bool _flag)
{
    return _flag ? reinterpret_cast<const tchar*>(Time::Months[_month == 0 ? GetMonth()-1 : _month-1]) : reinterpret_cast<const tchar*>(Time::MonthsAbbr[_month == 0 ? GetMonth()-1 : _month-1]);
}

void Time::GetTimeAsString(tchar* _buffer, const tchar* _template)
{
    xassertv(_buffer != null && _template != null)
   _buffer[0] = 0;
    //
    const tchar _e_ = _t('&');
    //
    tchar* p = StrChar(_template, _e_);

    int   len;
    tchar term[32];

    if(p == null || *p++ == 0)
    {
        return;
    }

    std::basic_string<tchar> s;

    while(*p != 0)
    {
        if(*p == _t('M'))
        {
            // month
            len = 0;

            while(*p != 0 && *p == _t('M'))
            {
                ++p;
                ++len;
            }

            if(len > 2)
            {
                s += GetNameOfMonth(GetMonth(), len > 3 ? true : false);
            }
            else
            {
               _snprintf(term, sizeof(term), len == 2 ? _t("%02u") : _t("%u"), GetMonth());
                s += term, term[0] = 0;
            }
        }
        else if(*p == _t('d'))
        {
            // day
            len = 0;

            while(*p != 0 && *p == _t('d'))
            {
                ++p;
                ++len;
            }

            if(len > 2)
            {
                s += GetNameOfDay(len > 3 ? true : false);
            }
            else
            {
               _snprintf(term, sizeof(term), len == 2 ? _t("%02u") : _t("%u"), GetDay());
                s += term, term[0] = 0;
            }
        }
        else if(*p == _t('y'))
        {
            // year
            len = 0;

            while(*p != 0 && *p == _t('y'))
            {
                ++p;
                ++len;
            }

            if(len > 2)
            {
                _snprintf(term, sizeof(term), _t("%u"), GetYear());
            }
            else
            {
                Time::Year y = GetYear();
                y = y-((y/100)*100);
               _snprintf(term, sizeof(term), y < 10 ? _t("0%u") : _t("%u"), y);
            }

            s += term, term[0] = 0;
        }
        else if(*p == _t('h') || *p == _t('H'))
        {
            // hour
            len = 0;

            while(*p != 0 && (*p == _t('h') || *p == _t('H')))
            {
                ++p;
                ++len;
            }

            Time::Hour h = GetHours();

            if(len > 1)
            {
                _snprintf(term, sizeof(term), _t("%02u"), h-(*p == _t('h') && h > 12 ? 12 : 0));
            }
            else
            {
                _snprintf(term, sizeof(term), _t("%u"), h-(*p == _t('h') && h > 12 ? 12 : 0));
            }

            s += term, term[0] = 0;
        }
        else if(*p == _t('m'))
        {
            // minute
            len = 0;

            while(*p != 0 && *p == _t('m'))
            {
                ++p;
                ++len;
            }

           _snprintf(term, sizeof(term), len > 1 ? _t("%02u") : _t("%u"), GetMinutes());
            s += term, term[0] = 0;
        }
        else if(*p == _t('s'))
        {
            // second
            len = 0;

            while(*p != 0 && *p == _t('s'))
            {
                ++p;
                ++len;
            }

           _snprintf(term, sizeof(term), len > 1 ? _t("%02u") : _t("%u"), GetSeconds());
            s += term, term[0] = 0;
        }
        else if(*p == _t('c'))
        {
            // hundred second
            s += _t("00");
        }
        else if(*p == _t('a') || *p == _t('A'))
        {
            // am/pm AM/PM
            s += GetHours() < 12 ? (*p == _t('a') ? _t("am") : _t("AM")) : (*p == _t('a') ? _t("pm") : _t("PM"));
            ++p;
        }
        else if(*p == _t('p') || *p == _t('P'))
        {
            // a/p A/P
            s += GetHours() < 12 ? (*p == _t('a') ? _t("a") : _t("A")) : (*p == _t('a') ? _t("p") : _t("P"));
            ++p;
        }
        else if(*p != _e_)
        {
            s += *p++;
        }
        else
        {
            ++p;
        }
    }

    StrCopy(_buffer, s.c_str());
}
////////////////////////////////////////////////////////////////////////////////////////
// class XTime
// ----- -----
Time::XTime::XTime(uint _error) : X(_error)
{
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__
