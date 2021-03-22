////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __HTTP_URL_INL__
#define __HTTP_URL_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class HTTPURL
// ----- -------
__INLINE__ bool HTTPURL::operator == (const HTTPURL& _other) const
{
    return StrICompareWithEsc(GetSchema(), _other.GetSchema()) == 0 &&
           StrICompareWithEsc(GetHost(), _other.GetHost())     == 0 &&
           GetPort() == _other.GetPort()                            &&
           StrCompareWithEsc(GetPath(), _other.GetPath())      == 0 &&
           StrCompareWithEsc(GetQuery(), _other.GetQuery())    == 0;
}

__INLINE__ bool HTTPURL::operator == (const tchar* _url) const
{
    return StrICompareWithEsc(GetSchema(), HTTPURL(_url).GetSchema())  == 0 &&
           StrICompareWithEsc(GetHost(), HTTPURL(_url).GetHost())      == 0 &&
           GetPort() == HTTPURL(_url).GetPort()                             &&
           StrCompareWithEsc(GetPath(), HTTPURL(_url).GetPath())       == 0 &&
           StrCompareWithEsc(GetQuery(), HTTPURL(_url).GetQuery())     == 0;
}

__INLINE__ bool HTTPURL::operator != (const HTTPURL& _other) const
{
    return !operator == (_other);
}

__INLINE__ bool HTTPURL::operator != (const tchar* _url) const
{
    return !operator == (_url);
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __HTTP_URL_INL__
