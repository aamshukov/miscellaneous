////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __FILE_URL_INL__
#define __FILE_URL_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class FileURL
// ----- -------
__INLINE__ bool FileURL::operator == (const FileURL& _other) const
{
    return StrICompareWithEsc(GetSchema(), _other.GetSchema()) == 0 &&
           StrICompareWithEsc(GetHost(), _other.GetHost())     == 0 &&
           StrCompareWithEsc(GetPath(), _other.GetPath())      == 0;
}

__INLINE__ bool FileURL::operator == (const tchar* _url) const
{
    return StrICompareWithEsc(GetSchema(), FileURL(_url).GetSchema()) == 0 &&
           StrICompareWithEsc(GetHost(), FileURL(_url).GetHost())     == 0 &&
           StrCompareWithEsc(GetPath(), FileURL(_url).GetPath())      == 0;
}

__INLINE__ bool FileURL::operator != (const FileURL& _other) const
{
    return !operator == (_other);
}

__INLINE__ bool FileURL::operator != (const tchar* _url) const
{
    return !operator == (_url);
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __FILE_URL_INL__
