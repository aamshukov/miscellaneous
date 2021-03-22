////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __FTP_URL_INL__
#define __FTP_URL_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class FTPURL
// ----- ------
__INLINE__ bool FTPURL::operator == (const FTPURL& _other) const
{
    return StrICompareWithEsc(GetSchema(), _other.GetSchema())    == 0 &&
           StrCompareWithEsc(GetUsername(), _other.GetUsername()) == 0 &&
           StrCompareWithEsc(GetPassword(), _other.GetPassword()) == 0 &&
           StrICompareWithEsc(GetHost(), _other.GetHost())        == 0 &&
           GetPort() == _other.GetPort()                               &&
           StrCompareWithEsc(GetPath(), _other.GetPath())         == 0 &&
           StrICompareWithEsc(GetType(), _other.GetType())        == 0;
}

__INLINE__ bool FTPURL::operator == (const tchar* _url) const
{
    return StrICompareWithEsc(GetSchema(), FTPURL(_url).GetSchema())    == 0 &&
           StrCompareWithEsc(GetUsername(), FTPURL(_url).GetUsername()) == 0 &&
           StrCompareWithEsc(GetPassword(), FTPURL(_url).GetPassword()) == 0 &&
           StrICompareWithEsc(GetHost(), FTPURL(_url).GetHost())        == 0 &&
           GetPort() == FTPURL(_url).GetPort()                               &&
           StrCompareWithEsc(GetPath(), FTPURL(_url).GetPath())         == 0 &&
           StrICompareWithEsc(GetType(), FTPURL(_url).GetType())        == 0;
}

__INLINE__ bool FTPURL::operator != (const FTPURL& _other) const
{
    return !operator == (_other);
}

__INLINE__ bool FTPURL::operator != (const tchar* _url) const
{
    return !operator == (_url);
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __FTP_URL_INL__
