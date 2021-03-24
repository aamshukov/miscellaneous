////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __URL_INL__
#define __URL_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class URL
// ----- ---
__INLINE__ bool URL::operator == (const URL& _other) const
{
    return StrCompareWithEsc(URL_, _other.URL_) == 0;
}

__INLINE__ bool URL::operator == (const tchar* _url) const
{
    return StrCompareWithEsc(URL_, _url) == 0;
}

__INLINE__ bool URL::operator != (const URL& _other) const
{
    return !operator == (_other);
}

__INLINE__ bool URL::operator != (const tchar* _url) const
{
    return !operator == (_url);
}

__INLINE__ URL::operator tchar* ()
{
    return URL_;
}

__INLINE__ URL::operator const tchar* () const
{
    return static_cast<const tchar*>(URL_);
}

__INLINE__ bool URL::IsURL() const
{
    // actually should return true if only we have <URL:><...>, but ...
    return true;
}

__INLINE__ String<> URL::GetURL() const
{
    return URL_;
}

__INLINE__ void URL::SetURL(const tchar* _url)
{
    URL_ = _url;
    //
    Correct();
}

__INLINE__ String<> URL::GetHost() const
{
    return String<>();
}

__INLINE__ ushort URL::GetPort() const
{
    return 0;
}

__INLINE__ ulong URL::Hash() const
{
    return ElfHashBytes(reinterpret_cast<byte*>(const_cast<tchar*>(URL_.GetData())));
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __URL_INL__
