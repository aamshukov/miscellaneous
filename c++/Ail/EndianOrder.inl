////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __ENDIAN_ORDER_INL__
#define __ENDIAN_ORDER_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class EndianOrder
// ----- -----------
__INLINE__ bool EndianOrder::IsLittleEndian() const
{
    return LittleEndian;
}

__INLINE__ bool EndianOrder::IsReverseOrder() const
{
    return ReverseOrder;
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __ENDIAN_ORDER_INL__
