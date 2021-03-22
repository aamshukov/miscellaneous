////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __IJ_INL__
#define __IJ_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class IJ
// ----- --
template <typename C, typename R, typename S> IJ<C, R, S>::IJ() : Column(0), Row(0), Stuff(ConstError32)
{
}

template <typename C, typename R, typename S> IJ<C, R, S>::IJ(const IJ& _other)
{
    operator = (_other);
}

template <typename C, typename R, typename S> IJ<C, R, S>::IJ(C& c, R& r) : Column(c), Row(r), Stuff(ConstError32)
{
}

template <typename C, typename R, typename S> __INLINE_TEMPLATE__ const IJ<C, R, S>& IJ<C, R, S>::operator = (const IJ<C, R, S>& _other)
{
    if(this != &_other) 
    {
        Column = _other.Column, Row = _other.Row, Stuff = _other.Stuff;
    }
    return *this; 
}  

template <typename C, typename R, typename S> __INLINE_TEMPLATE__ bool IJ<C, R, S>::operator == (const IJ<C, R, S>& _other)
{
    return Column == _other.Column && Row == _other.Row && Stuff == _other.Stuff;
}  

template <typename C, typename R, typename S> __INLINE_TEMPLATE__ C IJ<C, R, S>::GetColumn() const
{
    return Column;
}

template <typename C, typename R, typename S> __INLINE_TEMPLATE__ void IJ<C, R, S>::SetColumn(C _c)
{
    Column = _c;
}

template <typename C, typename R, typename S> __INLINE_TEMPLATE__ R IJ<C, R, S>::GetRow() const
{
    return Row;
}

template <typename C, typename R, typename S> __INLINE_TEMPLATE__ void IJ<C, R, S>::SetRow(R _r)
{
    Row = _r;
}

template <typename C, typename R, typename S> __INLINE_TEMPLATE__ S IJ<C, R, S>::GetStuff() const
{
    return Stuff;
}

template <typename C, typename R, typename S> __INLINE_TEMPLATE__ void IJ<C, R, S>::SetStuff(S _s)
{
    Stuff = _s;
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __IJ_INL__
