////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __UNIT_H__
#define __UNIT_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class Unit
// ----- ----
class __DECLSPEC__ Unit
{
    public:

    enum ECount
    {
        ConstUnitCount = 5
    };

    enum EMetric
    { 
        None       = 0x00,
        Inch       = 0x01,
        Centimeter = 0x02,
        Point      = 0x04,
        Pica       = 0x08,
        Custom     = 0x10
    };

    private:
     ushort         TwipsPerUnit;
     ushort         SmallDiv;
     ushort         MediumDiv;
     ushort         LargeDiv;
     EMetric        Metric;
     TCharStr       MetricAbbrev;
    protected:
     void           Init();
    public:
     static Unit    SystemUnits[Unit::ConstUnitCount]; // ConstUnitCount-1 -> Custom unit
    public:
                    Unit();
                    Unit(const Unit&);
                    Unit(EMetric, const tchar* = null);
                    Unit(EMetric, const TCharStr&);
                    Unit(EMetric, ushort, ushort, ushort, ushort, const tchar*);
     virtual       ~Unit(); 

     const Unit&    operator = (const Unit&);

     ushort         GetTwipsPerUnit()               const;
     ushort         GetSmallDiv()                   const;
     ushort         GetMediumDiv()                  const;
     ushort         GetLargeDiv()                   const;
     EMetric        GetMetric()                     const;
     TCharStr       GetMetricAbbrev()               const;
     tchar*         GetMetricAbbrevAsPtr()          const;
     void           SetMetricAbbrev(const TCharStr&);
     void           SetMetricAbbrevAsPtr(const tchar*);

     static Unit    GetSystemUnit(EMetric = Unit::None);
     static void    SetSystemUnit(ushort, ushort, ushort, ushort, const tchar*);
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __UNIT_H__
