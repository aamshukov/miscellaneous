////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __UNIT_INL__
#define __UNIT_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class Unit
// ----- ----
__INLINE__ ushort Unit::GetTwipsPerUnit() const
{ 
    return TwipsPerUnit;
}

__INLINE__ ushort Unit::GetSmallDiv() const 
{ 
    return SmallDiv;
}

__INLINE__ ushort Unit::GetMediumDiv() const 
{ 
    return MediumDiv;
}

__INLINE__ ushort Unit::GetLargeDiv() const 
{ 
    return LargeDiv;
}

__INLINE__ TCharStr Unit::GetMetricAbbrev() const 
{ 
    return MetricAbbrev;
}

__INLINE__ tchar* Unit::GetMetricAbbrevAsPtr() const 
{ 
    return (tchar*)MetricAbbrev.GetData();
}

__INLINE__ void Unit::SetMetricAbbrev(const TCharStr& str)
{
    MetricAbbrev = str;
}

__INLINE__ void Unit::SetMetricAbbrevAsPtr(const tchar* str)
{
    MetricAbbrev = str;
}

__INLINE__ Unit::EMetric Unit::GetMetric() const
{
    return Metric;
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __UNIT_INL__
