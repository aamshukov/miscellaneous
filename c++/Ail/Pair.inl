////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PAIR_INL__
#define __PAIR_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class Pair
// ----- ----
template <typename F, typename S> Pair<F, S>::Pair() : First(0), Second(0)
{
}

template <typename F, typename S> Pair<F, S>::Pair(const Pair& _other)
{
    operator = (_other);
}

template <typename F, typename S> Pair<F, S>::Pair(F& _f, S& _s) : First(_f), Second(_s)
{
}

template <typename F, typename S> __INLINE_TEMPLATE__ const Pair<F, S>& Pair<F, S>::operator = (const Pair<F, S>& _other)
{ 
    if(this != &_other) 
    {
        First = _other.First, Second = _other.Second; 
    }
    return *this;
}  

template <typename F, typename S> __INLINE_TEMPLATE__ bool Pair<F, S>::operator == (const Pair<F, S>& _other)
{ 
    return First == _other.First && Second == _other.Second; 
}  

template <typename F, typename S> __INLINE_TEMPLATE__ F Pair<F, S>::GetFirst() const
{
    return First;
}

template <typename F, typename S> __INLINE_TEMPLATE__ void Pair<F, S>::SetFirst(F _f)
{
    First = _f;
}

template <typename F, typename S> __INLINE_TEMPLATE__ S Pair<F, S>::GetSecond() const
{
    return Second;
}

template <typename F, typename S> __INLINE_TEMPLATE__ void Pair<F, S>::SetSecond(S _s)
{
    Second = _s;
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PAIR_INL__
