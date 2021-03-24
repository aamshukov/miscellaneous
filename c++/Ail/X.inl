////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __X_INL__
#define __X_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class X
// ----- -
__INLINE__ uint X::GetError() const
{ 
    return Error;
}

__INLINE__ uint X::GetSysError() const
{ 
    return SysError;
}
////////////////////////////////////////////////////////////////////////////////////////
__INLINE__ void __x_assert__(int _expr, uint _error)
{
    if(_expr == 0)
    {
        throw X(_error);
    }
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __X_INL__
