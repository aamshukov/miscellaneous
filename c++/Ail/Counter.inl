////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __COUNTER_INL__
#define __COUNTER_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class Counter
// ----- -------
template <typename T> uint Counter<T>::Count = 0;

template <typename T> Counter<T>::Counter()
{
    ++Count;
}

template <typename T> Counter<T>::Counter(const Counter& _other)
{
    if(this != &_other)
    {
        ++Count;
    }
}

template <typename T> Counter<T>::~Counter()
{
    if(Count > 0)
    {
        --Count;
    }
}
     
template <typename T> AI_INLINE_TEMPLATE uint Counter<T>::GetCount()
{
    return Count;
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __COUNTER_INL__
