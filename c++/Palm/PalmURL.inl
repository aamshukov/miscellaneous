////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PALM_URL_INL__
#define __PALM_URL_INL__

#ifdef __PALM_OS__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class URL
// ----- ---
__INLINE__ bool URL::operator == (const URL& _other) const
{
    return PalmText::StrCompareWithEsc(URL_.c_str(), _other.URL_.c_str()) == 0;
}

__INLINE__ bool URL::operator == (const char* _url) const
{
    return PalmText::StrCompareWithEsc(URL_.c_str(), _url) == 0;
}

__INLINE__ bool URL::operator != (const URL& _other) const
{
    return !operator == (_other);
}

__INLINE__ bool URL::operator != (const char* _url) const
{
    return !operator == (_url);
}

__INLINE__ URL::operator const char* () const
{
    return static_cast<const char*>(URL_.c_str());
}

__INLINE__ bool URL::IsURL() const
{
    // actually should return true if only we have <URL:><...>, but ...
    return true;
}

__INLINE__ _string URL::GetURL() const
{
    return URL_;
}

__INLINE__ void URL::SetURL(const char* _url)
{
    URL_ = _url;
    //
    Correct();
}

__INLINE__ _string URL::GetHost() const
{
    return _string();
}

__INLINE__ uint16 URL::GetPort() const
{
    return 0;
}

__INLINE__ uint32 URL::Hash() const
{
    return PalmOS::ElfHash(URL_.c_str());
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__
#endif // __PALM_URL_INL__
