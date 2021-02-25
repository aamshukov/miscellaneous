////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PALM_TEXT_H__
#define __PALM_TEXT_H__

#ifdef __PALM_OS__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class PalmText
// ----- --------
class __DECLSPEC__ PalmText
{
    public:
     // text
     static uint8               ByteAttr(uint8);
     static uint16              CharAttr(wchar);
     static uint16              CharXAttr(wchar);

     static uint16              CharSize(wchar);
     static int16               CharWidth(wchar);

     static wchar               GetChar(const char*, uint32);
     static uint16              GetNextChar(const char*, uint32, wchar*);
     static uint16              SetNextChar(char*, uint32, wchar);
     static uint16              GetPreviousChar(const char*, uint32, wchar*);

     static uint16              ReplaceStr(char*, uint16, const char*, uint16);
     static char*               ParamString(const char*, const char*, const char*, const char*, const char*);
     static wchar               CharBounds(const char*, uint32, uint32&, uint32&);
     static uint32              GetTruncationOffset(const char*, uint32);
     static bool                FindString(const char*, const char*, uint32&, uint16&);
     static bool                WordBounds(const char*, uint32, uint32, uint32&, uint32&);

     static CharEncodingType    CharEncoding(wchar);
     static CharEncodingType    StrEncoding(const char*);
     static CharEncodingType    MaxEncoding(CharEncodingType, CharEncodingType);
     static const char*         EncodingName(CharEncodingType);

     static Err                 Transliterate(const char*, uint16, char*, uint16&, TranslitOpType);
     static bool                CharIsValid(wchar);

     static int16               Compare(const char*, uint16, uint16&, const char*, uint16, uint16&);
     static int16               CaselessCompare(const char *, uint16, uint16&, const char*, uint16, uint16&);

     // string
     static char*               StrClone(const char*);
     static char*               StrCopy(char*, const char*);
     static char*               StrNCopy(char*, const char*, int16);
     static char*               StrCat(char*, const char*);
     static char*               StrNCat(char*, const char*, int16);
     static int16               StrLen(const char*);
     static int16               StrCompare(const char*, const char*);
     static int16               StrNCompare(const char*, const char*, int32);
     static int16               StrCaselessCompare(const char*, const char*);
     static int16               StrICompare(const char*, const char*);
     static int16               StrNCaselessCompare(const char*, const char*, int32);
     static int16               StrNICompare(const char*, const char*, int32);
     static char*               StrToLower(char*, const char*);
     static char*               StrIToA(char*, int32);
     static char*               StrIToH(char*, uint32);
     static char*               StrLocalizeNumber(char*, char, char);
     static char*               StrDelocalizeNumber(char*, char, char);
     static char*               StrCharW(const char*, wchar);
     static char*               StrChar(const char*, char);
     static char*               StrRChar(const char*, char);
     static char*               StrStr(const char*, const char*);
     static int32               StrAToI(const char*);
     static uint32              StrHToI(const char*); // hex to integer
     static void                Str64ToA(uint64, char*); // 64 to integer
     static int16               StrPrintf(char*, const char*, ...);

#if (__PALM_OS__ >= 0x0400)
     static int16               StrCompareAscii(const char*, const char*);
     static int16               StrNCompareAscii(const char*, const char*, int32);
#endif

     // font
     static Err                 DefineFont(FontID, FontType*);

     static FontID              GetFont();
     static FontID              SetFont(FontID);
     static FontPtr             GetFontPtr();

     static int16               BaseLine();
     static int16               GetDescenderHeight();

     static int16               GetCharWidth(char);
     static int16               GetCharsWidth(char const*, int16);
     static int16               GetAverageCharWidth();
#if (__PALM_OS__ >= 0x0400)
     static int16               GetWCharWidth(wchar);
#endif
     static int16               GetCharHeight();

     static int16               GetLineWidth(char const*, uint16);
     static int16               GetLineHeight();

     static int16               GetWidthToOffset(char const*, uint16, int16, bool&, int16&);
     static void                GetCharsInWidth(char const*, int16&, int16&, bool&);

     static uint16              WordWrap(char const*, uint16);
     static void                WordWrapReverseNLines(char const* const, uint16, uint16&, uint16&);

     static void                GetScrollValues(char const*, uint16, uint16, uint16&, uint16&);

     static FontID              FontSelect(FontID);

#if (__PALM_OS__ >= 0x0400)
     static Err                 ConvertEncoding(bool, TxtConvertStateType&, const char*, uint16&, CharEncodingType, char*, uint16&, CharEncodingType, const char*, uint16);
     static uint32              GetWordWrapOffset(const char*, uint32);
     static CharEncodingType    NameToEncoding(const char*);
#endif

     // api
     static int32               StrCompareWithEsc(const char*, const char*);
     static int32               StrICompareWithEsc(const char*, const char*);
     static void                ConvertEsc(char*, bool);
     static void                RemoveEsc(char*, bool);
     static bool                IsUnsafeChar(char);
     static bool                IsNonAsciiChar(char);
     static void                TrimSpace(char*, uint16);
     static char*               SkipSymbol(char*, char);
     static char*               SkipSymbols(char*, const char*);
     static char*               SkipTo(char*, char);
     static char*               SkipLWS(char*);
     static char*               GetLine(const char*, char*);
     static _string             GetString(const char*, uint32);
     static char*               HasToken(const char*, const char*, const char*, bool = false);
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__
#endif // __PALM_TEXT_H__
