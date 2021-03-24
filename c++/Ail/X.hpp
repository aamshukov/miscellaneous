////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __X_H__
#define __X_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class X
// ----- -
class __DECLSPEC__ X
{
    public:
    
    enum EError
    {
        Failure     = 0x00000000,
        InvalidArg  = 0x00000001,
        OutOfMemory = 0x00000002,
        OutOfRange  = 0x00000004
    };

    protected:
     uint           Error;
     uint           SysError;
    public:
                    X(uint = 0, uint = 0);
                    X(const X&);
     virtual       ~X();

     const X&       operator = (const X&);

     uint           GetError()      const;
     uint           GetSysError()   const;

     virtual tchar* Why();
};
////////////////////////////////////////////////////////////////////////////////////////
void __x_assert__(int, uint = X::InvalidArg);
////////////////////////////////////////////////////////////////////////////////////////
// assert
// ------
#define xassertdv(_expr)            \
    __x_assert__(_expr);            \
    if(_expr == 0)                  \
    {                               \
        return;                     \
    }                               \
//
#define xassertd(_expr, _rval)      \
    __x_assert__(_expr);            \
    if(_expr == 0)                  \
    {                               \
        return _rval;               \
    }                               \
//
#define xassertrv(_expr)            \
    if(_expr == 0)                  \
    {                               \
        return;                     \
    }                               \
//
#define xassertr(_expr, _rval)      \
    if(_expr == 0)                  \
    {                               \
        return _rval;               \
    }                               \
//
#ifdef _DEBUG
#   define xassertv(_expr)          xassertdv(_expr)        // debug void
#   define xassert(_expr, _rval)    xassertd(_expr, _rval)  // debug return value
#else
#   define xassertv(_expr)          xassertrv(_expr)        // run-time void
#   define xassert(_expr, _rval)    xassertr(_expr, _rval)  // run-time return value
#endif

#ifdef _DEBUG
#define _xassertv(_T, _expr, _err)          \
    if(_expr == 0)                          \
    {                                       \
        throw _T(_err);                     \
    }

#define _xassert(_T, _expr, _rval, _err)    \
    if(_expr == 0)                          \
    {                                       \
        throw _T(_err);                     \
    }                                       
#else
#define _xassertv(_T, _expr, _err)          \
    if(_expr == 0)                          \
    {                                       \
        return;                             \
    }                                       

#define _xassert(_T, _expr, _rval, _err)    \
    if(_expr == 0)                          \
    {                                       \
        return _rval;                       \
    }                                       
#endif
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __X_H__
