////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PERMUTATION_INL__
#define __PERMUTATION_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class Permutation
// ----- -----------
__INLINE__ const ulong* Permutation::GetPermutation() const
{
    return P;
}

__INLINE__ const ulong* Permutation::GetReversePermutation() const
{
    return PR;
}

__INLINE__ ulong Permutation::GetSize() const
{
    return N;
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PERMUTATION_INL__
