////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __RANGE_INL__
#define __RANGE_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class Range
// ----- -----
template <typename V> Range<V>::Range() : MinValue(0), MaxValue(0)
{
}

template <typename V> Range<V>::Range(const Range& _other)
{
    operator = (_other);
}

template <typename V> Range<V>::Range(V _min, V _max) : MinValue(_min), MaxValue(_max)
{
}

template <typename V> __INLINE_TEMPLATE__ const Range<V> Range<V>::operator = (const Range<V>& _other)
{
    if(&_other != this) 
    {
        MinValue = _other.MinValue, MaxValue = _other.MaxValue;
    }

    return *this; 
}  

template <typename V> __INLINE_TEMPLATE__ bool Range<V>::operator == (const Range<V>& _other)
{ 
    return MinValue == _other.MinValue && MaxValue == _other.MaxValue;
}  

template <typename V> __INLINE_TEMPLATE__ V Range<V>::GetMinValue() const
{ 
    return MinValue;
}

template <typename V> __INLINE_TEMPLATE__ void Range<V>::SetMinValue(V _v)
{ 
    MinValue = _v;
}

template <typename V> __INLINE_TEMPLATE__ V Range<V>::GetMaxValue() const
{ 
    return MaxValue;
}

template <typename V> __INLINE_TEMPLATE__ void Range<V>::SetMaxValue(V _v)
{ 
    MaxValue = _v;
}

template <typename V> __INLINE_TEMPLATE__ bool Range<V>::IsInRange(V _r) const
{
    return _r >= MinValue && _r <= MaxValue;
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __RANGE_INL__
