////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  Copyright © 1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PALM_TEXT_INL__
#define __PALM_TEXT_INL__

#ifdef __PALM_OS__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class PalmText
// ----- --------
#if (__PALM_OS__ >= 0x0400)
__INLINE__ int16 PalmText::GetWCharWidth(wchar _wch)
{
    return ::FntWCharWidth(_wch);
}
#endif

__INLINE__ char* PalmText::StrClone(const char* _s)
{
    palmxassert(_s != null, Error::eInvalidArg, Error);
    return PalmText::StrCopy(new char[PalmText::StrLen(_s)+1], _s);
}

__INLINE__ char* PalmText::StrCopy(char* _dst, const char* _src)
{
    palmxassert(_dst != null, Error::eInvalidArg, Error);
    palmxassert(_src != null, Error::eInvalidArg, Error);
    return ::StrCopy(_dst, _src);
}

__INLINE__ char* PalmText::StrNCopy(char* _dst, const char* _src, int16 _count)
{
    palmxassert(_dst != null, Error::eInvalidArg, Error);
    palmxassert(_src != null, Error::eInvalidArg, Error);
    return ::StrNCopy(_dst, _src, _count);
}

__INLINE__ char* PalmText::StrCat(char* _dst, const char* _src)
{
    palmxassert(_dst != null, Error::eInvalidArg, Error);
    palmxassert(_src != null, Error::eInvalidArg, Error);
    return ::StrCat(_dst, _src);
}

__INLINE__ char* PalmText::StrNCat(char* _dst, const char* _src, int16 _count)
{
    palmxassert(_dst != null, Error::eInvalidArg, Error);
    palmxassert(_src != null, Error::eInvalidArg, Error);
    return ::StrNCat(_dst, _src, _count);
}

__INLINE__ int16 PalmText::StrLen(const char* _src)
{
    palmxassert(_src != null, Error::eInvalidArg, Error);
    return ::StrLen(_src);
}

__INLINE__ int16 PalmText::StrCompare(const char* _s1, const char* _s2)
{
    palmxassert(_s1 != null, Error::eInvalidArg, Error);
    palmxassert(_s2 != null, Error::eInvalidArg, Error);
    return ::StrCompare(_s1, _s2);
}

__INLINE__ int16 PalmText::StrNCompare(const char* _s1, const char* _s2, int32 _count)
{
    palmxassert(_s1 != null, Error::eInvalidArg, Error);
    palmxassert(_s2 != null, Error::eInvalidArg, Error);
    return ::StrNCompare(_s1, _s2, _count);
}

#if (__PALM_OS__ >= 0x0400)
__INLINE__ int16 PalmText::StrCompareAscii(const char* _s1, const char* _s2)
{
    palmxassert(_s1 != null, Error::eInvalidArg, Error);
    palmxassert(_s2 != null, Error::eInvalidArg, Error);
    return ::StrCompareAscii(_s1, _s2);
}

__INLINE__ int16 PalmText::StrNCompareAscii(const char* _s1, const char* _s2, int32 _count)
{
    palmxassert(_s1 != null, Error::eInvalidArg, Error);
    palmxassert(_s2 != null, Error::eInvalidArg, Error);
    return ::StrNCompareAscii(_s1, _s2, _count);
}
#endif

__INLINE__ int16 PalmText::StrCaselessCompare(const char* _s1, const char* _s2)
{
    palmxassert(_s1 != null, Error::eInvalidArg, Error);
    palmxassert(_s2 != null, Error::eInvalidArg, Error);
    return ::StrCaselessCompare(_s1, _s2);
}

__INLINE__ int16 PalmText::StrICompare(const char* _s1, const char* _s2)
{
    palmxassert(_s1 != null, Error::eInvalidArg, Error);
    palmxassert(_s2 != null, Error::eInvalidArg, Error);
    return ::StrCaselessCompare(_s1, _s2);
}

__INLINE__ int16 PalmText::StrNCaselessCompare(const char* _s1, const char* _s2, int32 _count)
{
    palmxassert(_s1 != null, Error::eInvalidArg, Error);
    palmxassert(_s2 != null, Error::eInvalidArg, Error);
    return ::StrNCaselessCompare(_s1, _s2, _count);
}

__INLINE__ int16 PalmText::StrNICompare(const char* _s1, const char* _s2, int32 _count)
{
    palmxassert(_s1 != null, Error::eInvalidArg, Error);
    palmxassert(_s2 != null, Error::eInvalidArg, Error);
    return ::StrNCaselessCompare(_s1, _s2, _count);
}

__INLINE__ char* PalmText::StrToLower(char* _dst, const char* _src)
{
    palmxassert(_dst != null, Error::eInvalidArg, Error);
    palmxassert(_src != null, Error::eInvalidArg, Error);
    return ::StrToLower(_dst, _src);
}

__INLINE__ char* PalmText::StrIToA(char* _s, int32 _i)
{
    palmxassert(_s != null, Error::eInvalidArg, Error);
    return ::StrIToA(_s, _i);
}

__INLINE__ char* PalmText::StrIToH(char* _s, uint32 _ui)
{
    palmxassert(_s != null, Error::eInvalidArg, Error);
    return ::StrIToH(_s, _ui);
}

__INLINE__ char* PalmText::StrLocalizeNumber(char* _s, char _thousand_separator, char _decimal_separator)
{
    palmxassert(_s != null, Error::eInvalidArg, Error);
    return ::StrLocalizeNumber(_s, _thousand_separator, _decimal_separator);
}

__INLINE__ char* PalmText::StrDelocalizeNumber(char* _s, char _thousand_separator, char _decimal_separator)
{
    palmxassert(_s != null, Error::eInvalidArg, Error);
    return ::StrDelocalizeNumber(_s, _thousand_separator, _decimal_separator);
}

__INLINE__ char* PalmText::StrCharW(const char* _s, wchar _pattern)
{
    palmxassert(_s != null, Error::eInvalidArg, Error);
    return ::StrChr(_s, _pattern);
}

__INLINE__ char* PalmText::StrStr(const char* _s, const char* _pattern)
{
    palmxassert(_s != null, Error::eInvalidArg, Error);
    palmxassert(_pattern != null, Error::eInvalidArg, Error);
    return ::StrStr(_s, _pattern);
}

__INLINE__ int32 PalmText::StrAToI(const char* _s)
{
    palmxassert(_s != null, Error::eInvalidArg, Error);
    return ::StrAToI(_s);
}

__INLINE__ int16 PalmText::StrPrintf(char* _s, const char* _format, ...)
{
    palmxassert(_s != null, Error::eInvalidArg, Error);
    palmxassert(_format != null, Error::eInvalidArg, Error);
    int16 rc;
    char* lst = (char*)(&_format+1);
    rc = ::StrVPrintF(_s, _format, lst);
    return rc;
}

#if (__PALM_OS__ >= 0x0400)
__INLINE__ Err PalmText::ConvertEncoding(bool _new_conversion, TxtConvertStateType& _state,
                                         const char* _src, uint16& _src_count, CharEncodingType _src_encoding,
			                             char* _dst, uint16& _dst_count, CharEncodingType _dst_encoding,
                                         const char* _substitution, uint16 _substitution_count)
{
    palmxassert(_src != null, Error::eInvalidArg, Error);
    palmxassert(_dst != null, Error::eInvalidArg, Error);
    return ::TxtConvertEncoding(_new_conversion, &_state, _src, &_src_count, _src_encoding, _dst, &_dst_count, _dst_encoding, _substitution, _substitution_count);
}

__INLINE__ uint32 PalmText::GetWordWrapOffset(const char* _text, uint32 _offset)
{
    palmxassert(_text != null, Error::eInvalidArg, Error);
    return ::TxtGetWordWrapOffset(_text, _offset);
}

__INLINE__ CharEncodingType PalmText::NameToEncoding(const char* _encoding_name)
{
    palmxassert(_encoding_name != null, Error::eInvalidArg, Error);
    return ::TxtNameToEncoding(_encoding_name);
}
#endif
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__
#endif // __PALM_TEXT_INL__
