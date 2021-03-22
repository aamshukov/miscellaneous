////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __L_TRANSACTION_INL__
#define __L_TRANSACTION_INL__

#pragma once

__BEGIN_NAMESPACE__
__BEGIN_RRT_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class LTransaction
// ----- ------------
__INLINE__ bool LTransaction::IsPended() const
{
    return State == LTransaction::Pended;
}

__INLINE__ bool LTransaction::IsAborted() const
{
    return State == LTransaction::Aborted;
}

__INLINE__ bool LTransaction::IsCompleted() const
{
    return State == LTransaction::Completed;
}
////////////////////////////////////////////////////////////////////////////////////////
__END_RRT_NAMESPACE__
__END_NAMESPACE__

#endif // __L_TRANSACTION_INL__
