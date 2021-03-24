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

#ifndef __X_INC__
#   include <X.inc>
#endif

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class X
// ----- -
X::X(uint _error, uint _syserror) : Error(_error), SysError(_syserror == 0 ? ::GetLastError() : _syserror)
{
}

X::X(const X& _other)
{
    operator = (_other);
}

X::~X()
{
}

const X& X::operator = (const X& _other)
{
    if(this != &_other)
    {
        Error    = _other.Error;
        SysError = _other.SysError;
    }

    return *this;
}

tchar* X::Why()
{
    return null;
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__
