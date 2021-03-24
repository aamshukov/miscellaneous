////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __AIL_H__
#   include <ail.hpp>
#endif

#ifndef __UNIT_INC__
#   include <Unit.inc>
#endif

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class Unit
// ----- ------
const byte CustomUnitIndex = 4;

enum EnumArrows { ArrowUp = 1, ArrowDown = 2, ArrowLeft = 3, ArrowRight = 4 };

Unit Unit::SystemUnits[] =
{
    //     Metric           TPU,   SmallDiv,  MedDiv, LargeDiv,  MetricAbbrev
    Unit(Unit::Inch,       1440,     180,      720,   1440,      _t("Inch")   ),
    Unit(Unit::Centimeter,  568,     142,      284,    568,      _t("Cm")     ),
    Unit(Unit::Point,        20,     120,      720,    720,      _t("Point")  ),
    Unit(Unit::Pica,        240,     240,     1440,   1440,      _t("Pica")   ),
    Unit(Unit::Custom,        0,       0,        0,      0,      _t("Custom") )
};

Unit::Unit()
{
    Init();
}

Unit::Unit(const Unit& other)
{
    if(this != &other)
    {
        TwipsPerUnit = other.TwipsPerUnit;
        SmallDiv     = other.SmallDiv;
        MediumDiv    = other.MediumDiv;
        LargeDiv     = other.LargeDiv;
        Metric       = other.Metric;
        MetricAbbrev = other.MetricAbbrev;
    }
}

Unit::Unit(EMetric metric, const tchar* str)
{
    TwipsPerUnit = GetSystemUnit(metric).TwipsPerUnit;
    SmallDiv     = GetSystemUnit(metric).SmallDiv;
    MediumDiv    = GetSystemUnit(metric).MediumDiv;
    LargeDiv     = GetSystemUnit(metric).LargeDiv;
    Metric       = GetSystemUnit(metric).Metric;

    if(str != null)
    {
        MetricAbbrev = str;
    }
    else
    {
        MetricAbbrev = GetSystemUnit(metric).MetricAbbrev;
    }
}

Unit::Unit(EMetric metric, const TCharStr& str)
{
    TwipsPerUnit = GetSystemUnit(metric).TwipsPerUnit;
    SmallDiv     = GetSystemUnit(metric).SmallDiv;
    MediumDiv    = GetSystemUnit(metric).MediumDiv;
    LargeDiv     = GetSystemUnit(metric).LargeDiv;
    Metric       = GetSystemUnit(metric).Metric;

    if(!str.IsEmpty())
    {
        MetricAbbrev = str;
    }
    else
    {
        MetricAbbrev = GetSystemUnit(metric).MetricAbbrev;
    }
}

Unit::Unit(EMetric metric, ushort tpu, ushort small_div, ushort medium_div, ushort large_div, const tchar* str)
{
    TwipsPerUnit = tpu;
    SmallDiv     = small_div;
    MediumDiv    = medium_div;
    LargeDiv     = large_div;
    Metric       = metric;
    MetricAbbrev = str;
}

Unit::~Unit()
{
}

void Unit::Init()
{
    TwipsPerUnit = 0;
    SmallDiv     = 0;
    MediumDiv    = 0;
    LargeDiv     = 0;
    Metric       = Unit::None;
}

const Unit& Unit::operator = (const Unit& other)
{
    if(this != &other)
    {
        TwipsPerUnit = other.TwipsPerUnit;
        SmallDiv     = other.SmallDiv;
        MediumDiv    = other.MediumDiv;
        LargeDiv     = other.LargeDiv;
        Metric       = other.Metric;
        MetricAbbrev = other.MetricAbbrev;
    }
    return *this;
}

Unit Unit::GetSystemUnit(EMetric metric)
{
    if(metric == Unit::Inch)
    {
        return Unit::SystemUnits[0];
    }
    else if(metric == Unit::Centimeter)
    {
        return Unit::SystemUnits[1];
    }
    else if(metric == Unit::Point)
    {
        return Unit::SystemUnits[2];
    }
    else if(metric == Unit::Pica)
    {
        return Unit::SystemUnits[3];
    }
    else if(metric == Unit::Custom)
    {
        return Unit::SystemUnits[4];
    }

    return Unit();
}

void Unit::SetSystemUnit(ushort tpu, ushort small_div, ushort medium_div, ushort large_div, const tchar* str)
{
    Unit::SystemUnits[CustomUnitIndex].TwipsPerUnit = tpu;
    Unit::SystemUnits[CustomUnitIndex].SmallDiv     = small_div;
    Unit::SystemUnits[CustomUnitIndex].MediumDiv    = medium_div;
    Unit::SystemUnits[CustomUnitIndex].LargeDiv     = large_div;
    Unit::SystemUnits[CustomUnitIndex].Metric       = Unit::Custom;
    Unit::SystemUnits[CustomUnitIndex].MetricAbbrev = str;
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__
