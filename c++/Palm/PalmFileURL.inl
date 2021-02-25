////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PALM_FILE_URL_INL__
#define __PALM_FILE_URL_INL__

#ifdef __PALM_OS__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class FileURL
// ----- -------
__INLINE__ bool FileURL::operator == (const FileURL& _other) const
{
    return PalmText::StrICompareWithEsc(GetSchema().c_str(), _other.GetSchema().c_str()) == 0 &&
           PalmText::StrICompareWithEsc(GetHost().c_str(), _other.GetHost().c_str())     == 0 &&
           PalmText::StrCompareWithEsc(GetPath().c_str(), _other.GetPath().c_str())      == 0;
}

__INLINE__ bool FileURL::operator == (const char* _url) const
{
    return PalmText::StrICompareWithEsc(GetSchema().c_str(), FileURL(_url).GetSchema().c_str()) == 0 &&
           PalmText::StrICompareWithEsc(GetHost().c_str(), FileURL(_url).GetHost().c_str())     == 0 &&
           PalmText::StrCompareWithEsc(GetPath().c_str(), FileURL(_url).GetPath().c_str())      == 0;
}

__INLINE__ bool FileURL::operator != (const FileURL& _other) const
{
    return !operator == (_other);
}

__INLINE__ bool FileURL::operator != (const char* _url) const
{
    return !operator == (_url);
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__
#endif // __PALM_FILE_URL_INL__
