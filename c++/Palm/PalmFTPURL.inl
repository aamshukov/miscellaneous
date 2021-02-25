////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  Copyright © 1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PALM_FTP_URL_INL__
#define __PALM_FTP_URL_INL__

#ifdef __PALM_OS__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class FTPURL
// ----- ------
__INLINE__ bool FTPURL::operator == (const FTPURL& _other) const
{
    return PalmText::StrICompareWithEsc(GetSchema().c_str(), _other.GetSchema().c_str())    == 0 &&
           PalmText::StrCompareWithEsc(GetUsername().c_str(), _other.GetUsername().c_str()) == 0 &&
           PalmText::StrCompareWithEsc(GetPassword().c_str(), _other.GetPassword().c_str()) == 0 &&
           PalmText::StrICompareWithEsc(GetHost().c_str(), _other.GetHost().c_str())        == 0 &&
           PalmText::StrCompareWithEsc(GetPath().c_str(), _other.GetPath().c_str())         == 0 &&
           PalmText::StrICompareWithEsc(GetType().c_str(), _other.GetType().c_str())        == 0 &&
           GetPort() == _other.GetPort();
}

__INLINE__ bool FTPURL::operator == (const tchar* _url) const
{
    return PalmText::StrICompareWithEsc(GetSchema().c_str(), FTPURL(_url).GetSchema().c_str())    == 0 &&
           PalmText::StrCompareWithEsc(GetUsername().c_str(), FTPURL(_url).GetUsername().c_str()) == 0 &&
           PalmText::StrCompareWithEsc(GetPassword().c_str(), FTPURL(_url).GetPassword().c_str()) == 0 &&
           PalmText::StrICompareWithEsc(GetHost().c_str(), FTPURL(_url).GetHost().c_str())        == 0 &&
           PalmText::StrCompareWithEsc(GetPath().c_str(), FTPURL(_url).GetPath().c_str())         == 0 &&
           PalmText::StrICompareWithEsc(GetType().c_str(), FTPURL(_url).GetType().c_str())        == 0 &&
           GetPort() == FTPURL(_url).GetPort();
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

#endif // __PALM_OS__
#endif // __PALM_FTP_URL_INL__
