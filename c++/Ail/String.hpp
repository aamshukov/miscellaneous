////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __STRING_H__
#define __STRING_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class CharTraits
// ----- ----------
class CharTraits
{
    public:
     static uint    StrLen(const tchar*);
     static tchar*  StrCopy(tchar*, const tchar*);
     static tchar*  StrSubstr(const tchar*, const tchar*);
     static int     StrColl(const tchar*, const tchar*);
     static int     StrIColl(const tchar*, const tchar*);
     static int     StrNColl(const tchar*, const tchar*, size_t);
     static int     StrNIColl(const tchar*, const tchar*, size_t);
     static int     StrCompare(const tchar*, const tchar*);
     static int     StrICompare(const tchar*, const tchar*);
     static int     StrNCompare(const tchar*, const tchar*, size_t);
     static int     StrNICompare(const tchar*, const tchar*, size_t);
     static tchar*  StrUpper(tchar*);
     static tchar*  StrLower(tchar*);
     static int     Format(tchar*, const tchar*, va_list&);
};
////////////////////////////////////////////////////////////////////////////////////////
// class UniTraits
// ----- ---------
class UniTraits
{
    public:
     static uint    StrLen(const wchar*);
     static wchar*  StrCopy(wchar*, const wchar*);
     static wchar*  StrSubstr(const wchar*, const wchar*);
     static int     StrColl(const wchar*, const wchar*);
     static int     StrIColl(const wchar*, const wchar*);
     static int     StrNColl(const wchar*, const wchar*, size_t);
     static int     StrNIColl(const wchar*, const wchar*, size_t);
     static int     StrCompare(const wchar*, const wchar*);
     static int     StrICompare(const wchar*, const wchar*);
     static int     StrNCompare(const wchar*, const wchar*, size_t);
     static int     StrNICompare(const wchar*, const wchar*, size_t);
     static wchar*  StrUpper(wchar*);
     static wchar*  StrLower(wchar*);
     static int     Format(wchar*, const wchar*, va_list&);
};
////////////////////////////////////////////////////////////////////////////////////////
template <typename _T, typename _Traits, typename _Allocator> class String;
////////////////////////////////////////////////////////////////////////////////////////
// class StrRef
// ----- ------
template <typename _T = tchar, typename _Traits = CharTraits, typename _Allocator = StandardAllocator> class StrRef : private ObjectRef<>
{
    friend class String<_T, _Traits, _Allocator>;

    private:
    _T*             Data;
     uint           Count;
    private:
     // ctor/dtor
                    StrRef();
                    StrRef(const StrRef&);
                    StrRef(_T, uint = 1);
                    StrRef(const _T*, uint = 0, uint = -1);
     virtual       ~StrRef(); 

     // operators
     const StrRef&  operator = (const StrRef&);

     // access
    _T*             GetData()                   const;
     uint           GetCount()                  const;

     // protocol
     uint           RoundCapacity(uint)         const;

     void           Assign(const _T*, uint);
     void           Append(const _T*, uint);
     void           Insert(uint, const _T*, uint, bool = false);
     void           TrimSpace(ushort = 0);
     void           Remove(uint, uint);
     void           Resize(uint);
     void           Reserve(uint);
     void           Release();
     void           FreeExtraMemory();

     virtual uint   AddReference();
     virtual uint   ReleaseReference();
};
////////////////////////////////////////////////////////////////////////////////////////
// class String
// ----- ------
template <typename _T = tchar, typename _Traits = CharTraits, typename _Allocator = StandardAllocator> class String
{
    friend class StrRef<_T, _Traits, _Allocator>;

    public:

    enum EFlag
    {
        None           = 0x00000000,
        ReadOnly       = 0x00000001,
        NLS            = 0x00000002,
        CaseSensitive  = 0x00000004,
        UpperCase      = 0x00000008,
        LowerCase      = 0x00000010,
        Reverse        = 0x00000020,
        FromResource   = 0x00000040,
        MemoryReserve  = 0x00000080,
        Unistring      = 0x00000100
    };

    private:
     typedef StrRef<_T, _Traits, _Allocator> _StrRef;

     uint               Flags;
    _StrRef*            Ref;
    private:
     bool               AssertRange(uint = 0, uint = -1)                const;
     void               AssertIndex(uint)                               const;
     void               AssertFlag(uint = String::None)                 const;
     //
     void               COW();
     void               Clone();
     //
     short              CompareInternal(const _T*)                      const;
     uint               FindInternal(const _T*, uint = 0)               const;
     uint               ReverseFindInternal(const _T*, uint = 0)        const;

     static void        MemMove(_T*, const _T*, uint);
     static void        MemSet(_T*, uint, _T = Char::Space);
    public:
     // ctor/dtor
                        String();
                        String(const String&);
                        String(_T, uint = 1, uint = String::None);
     explicit           String(int, uint = String::None);
     explicit           String(double, const _T* = null, uint = String::None);
                        String(const _T*, uint = 0, uint = -1, uint = String::None);
                        String(HINSTANCE, uint, uint = String::None);
     virtual           ~String();

     // operators
     const String&      operator = (_T);
     const String&      operator = (int);
     const String&      operator = (double);
     const String&      operator = (const _T*);
     const String&      operator = (const String&);

     const String&      operator += (_T);
     const String&      operator += (int);
     const String&      operator += (double);
     const String&      operator += (const _T*);
     const String&      operator += (const String&);

     const _T&          operator [] (uint);

                        operator const _T* ()                           const;
                        operator _T* ();

                        operator () ();

     // access
     uint               GetFlags()                                      const;
     void               SetFlags(uint, uint = 0);

     const _T*          GetData()                                       const;

     // protocol
     uint               GetCount()                                      const;
     uint               GetCapacity()                                   const;

     uint               GetHashValue()                                  const;

     bool               IsEmpty()                                       const;
     void               SetEmpty();

     const _T&          GetAt(uint)                                     const;
     void               SetAt(uint, const _T&);

     String             GetFirstTerm(_T**, _T = Char::Space)            const;
     String             GetNextTerm(_T**, _T = Char::Space)             const;
     String             GetPrevTerm(_T**, _T = Char::Space)             const;
     String             GetLastTerm(_T**, _T = Char::Space)             const;

     String             GetLeftPart(uint)                               const;
     String             GetMidPart(uint)                                const;
     String             GetMidPart(uint, uint)                          const;
     String             GetRightPart(uint)                              const;

     String             SpanIncluding(const _T*)                        const;
     String             SpanExcluding(const _T*)                        const;

     bool               Contains(_T)                                    const;
     bool               Contains(int)                                   const;
     bool               Contains(double, const _T* = null)              const;
     bool               Contains(const _T*)                             const;
     bool               Contains(const String&);

     uint               Find(_T, uint = 0)                              const;
     uint               Find(int, uint = 0)                             const;
     uint               Find(double, const _T* = null, uint = 0)        const;
     uint               Find(const _T*, uint = 0)                       const;
     uint               Find(const String&, uint = 0)                   const;

     uint               ReverseFind(_T, uint = 0)                       const;
     uint               ReverseFind(int, uint = 0)                      const;
     uint               ReverseFind(double, const _T* = null, uint = 0) const;
     uint               ReverseFind(const _T*, uint = 0)                const;
     uint               ReverseFind(const String&, uint = 0)            const;

     uint               FindOneOf(const _T*)                            const;

     short              Compare(_T)                                     const;
     short              Compare(int)                                    const;
     short              Compare(double, const _T* = null)               const;
     short              Compare(const _T*)                              const;
     short              Compare(const String&)                          const;

     const String&      Assign(_T);
     const String&      Assign(int);
     const String&      Assign(double, const _T* = null);
     const String&      Assign(const _T*);
     const String&      Assign(const String&);

     const String&      Append(_T);
     const String&      Append(int);
     const String&      Append(double, const _T* = null);
     const String&      Append(const _T*, uint = 0, uint = -1);
     const String&      Append(const String&, uint = 0, uint = -1);

     const String&      Insert(uint, _T, uint = 1);
     const String&      Insert(uint, int);
     const String&      Insert(uint, double, const _T* = null);
     const String&      Insert(uint, const _T*, uint = 0, uint = -1);
     const String&      Insert(uint, const String&, uint = 0, uint = -1);

     const String&      Remove(uint, uint = -1);

     void               MakeUpper(uint = 0, uint = -1);
     void               MakeLower(uint = 0, uint = -1);

     void               MakeReverse();

     void               Format(const _T*, ...);
     void               Format(HINSTANCE, uint, ...);

     void               TrimLeft();
     void               TrimRight();
     void               TrimLeftRight();

     const String&      Resize(uint);
     const String&      Reserve(uint);
     const String&      FreeExtraMemory();

     // windows stuff
     void               LoadString(HINSTANCE, uint);
#ifndef _UNICODE
     void               ANSI2OEM();
     void               OEM2ANSI();
#endif
};
////////////////////////////////////////////////////////////////////////////////////////
// class XString
// ----- -------
class __DECLSPEC__ XString : public X
{
    public:
        XString(uint = X::Failure);
};
////////////////////////////////////////////////////////////////////////////////////////
// operators
template <typename _T, typename _Traits, typename _Allocator> bool operator == (const String<_T, _Traits, _Allocator>&, const String<_T, _Traits, _Allocator>&);
template <typename _T, typename _Traits, typename _Allocator> bool operator == (const String<_T, _Traits, _Allocator>&, const _T*);
template <typename _T, typename _Traits, typename _Allocator> bool operator == (const String<_T, _Traits, _Allocator>&, _T);
template <typename _T, typename _Traits, typename _Allocator> bool operator == (const String<_T, _Traits, _Allocator>&, int);
template <typename _T, typename _Traits, typename _Allocator> bool operator == (const String<_T, _Traits, _Allocator>&, double);
template <typename _T, typename _Traits, typename _Allocator> bool operator == (const _T*, const String<_T, _Traits, _Allocator>&);
template <typename _T, typename _Traits, typename _Allocator> bool operator == (_T, const String<_T, _Traits, _Allocator>&);
template <typename _T, typename _Traits, typename _Allocator> bool operator == (int, const String<_T, _Traits, _Allocator>&);
template <typename _T, typename _Traits, typename _Allocator> bool operator == (double, const String<_T, _Traits, _Allocator>&);

template <typename _T, typename _Traits, typename _Allocator> bool operator != (const String<_T, _Traits, _Allocator>&, const String<_T, _Traits, _Allocator>&);
template <typename _T, typename _Traits, typename _Allocator> bool operator != (const String<_T, _Traits, _Allocator>&, const _T*);
template <typename _T, typename _Traits, typename _Allocator> bool operator != (const String<_T, _Traits, _Allocator>&, _T);
template <typename _T, typename _Traits, typename _Allocator> bool operator != (const String<_T, _Traits, _Allocator>&, int);
template <typename _T, typename _Traits, typename _Allocator> bool operator != (const String<_T, _Traits, _Allocator>&, double);
template <typename _T, typename _Traits, typename _Allocator> bool operator != (const _T*, const String<_T, _Traits, _Allocator>&);
template <typename _T, typename _Traits, typename _Allocator> bool operator != (_T, const String<_T, _Traits, _Allocator>&);
template <typename _T, typename _Traits, typename _Allocator> bool operator != (int, const String<_T, _Traits, _Allocator>&);
template <typename _T, typename _Traits, typename _Allocator> bool operator != (double, const String<_T, _Traits, _Allocator>&);

template <typename _T, typename _Traits, typename _Allocator> bool operator < (const String<_T, _Traits, _Allocator>&, const String<_T, _Traits, _Allocator>&);
template <typename _T, typename _Traits, typename _Allocator> bool operator < (const String<_T, _Traits, _Allocator>&, const _T*);
template <typename _T, typename _Traits, typename _Allocator> bool operator < (const String<_T, _Traits, _Allocator>&, _T);
template <typename _T, typename _Traits, typename _Allocator> bool operator < (const String<_T, _Traits, _Allocator>&, int);
template <typename _T, typename _Traits, typename _Allocator> bool operator < (const String<_T, _Traits, _Allocator>&, double);
template <typename _T, typename _Traits, typename _Allocator> bool operator < (const _T*, const String<_T, _Traits, _Allocator>&);
template <typename _T, typename _Traits, typename _Allocator> bool operator < (_T, const String<_T, _Traits, _Allocator>&);
template <typename _T, typename _Traits, typename _Allocator> bool operator < (int, const String<_T, _Traits, _Allocator>&);
template <typename _T, typename _Traits, typename _Allocator> bool operator < (double, const String<_T, _Traits, _Allocator>&);

template <typename _T, typename _Traits, typename _Allocator> bool operator > (const String<_T, _Traits, _Allocator>&, const String<_T, _Traits, _Allocator>&);
template <typename _T, typename _Traits, typename _Allocator> bool operator > (const String<_T, _Traits, _Allocator>&, const _T*);
template <typename _T, typename _Traits, typename _Allocator> bool operator > (const String<_T, _Traits, _Allocator>&, _T);
template <typename _T, typename _Traits, typename _Allocator> bool operator > (const String<_T, _Traits, _Allocator>&, int);
template <typename _T, typename _Traits, typename _Allocator> bool operator > (const String<_T, _Traits, _Allocator>&, double);
template <typename _T, typename _Traits, typename _Allocator> bool operator > (const _T*, const String<_T, _Traits, _Allocator>&);
template <typename _T, typename _Traits, typename _Allocator> bool operator > (_T, const String<_T, _Traits, _Allocator>&);
template <typename _T, typename _Traits, typename _Allocator> bool operator > (int, const String<_T, _Traits, _Allocator>&);
template <typename _T, typename _Traits, typename _Allocator> bool operator > (double, const String<_T, _Traits, _Allocator>&);

template <typename _T, typename _Traits, typename _Allocator> bool operator <= (const String<_T, _Traits, _Allocator>&, const String<_T, _Traits, _Allocator>&);
template <typename _T, typename _Traits, typename _Allocator> bool operator <= (const String<_T, _Traits, _Allocator>&, const _T*);
template <typename _T, typename _Traits, typename _Allocator> bool operator <= (const String<_T, _Traits, _Allocator>&, _T);
template <typename _T, typename _Traits, typename _Allocator> bool operator <= (const String<_T, _Traits, _Allocator>&, int);
template <typename _T, typename _Traits, typename _Allocator> bool operator <= (const String<_T, _Traits, _Allocator>&, double);
template <typename _T, typename _Traits, typename _Allocator> bool operator <= (const _T*, const String<_T, _Traits, _Allocator>&);
template <typename _T, typename _Traits, typename _Allocator> bool operator <= (_T, const String<_T, _Traits, _Allocator>&);
template <typename _T, typename _Traits, typename _Allocator> bool operator <= (int, const String<_T, _Traits, _Allocator>&);
template <typename _T, typename _Traits, typename _Allocator> bool operator <= (double, const String<_T, _Traits, _Allocator>&);

template <typename _T, typename _Traits, typename _Allocator> bool operator >= (const String<_T, _Traits, _Allocator>&, const String<_T, _Traits, _Allocator>&);
template <typename _T, typename _Traits, typename _Allocator> bool operator >= (const String<_T, _Traits, _Allocator>&, const _T*);
template <typename _T, typename _Traits, typename _Allocator> bool operator >= (const String<_T, _Traits, _Allocator>&, _T);
template <typename _T, typename _Traits, typename _Allocator> bool operator >= (const String<_T, _Traits, _Allocator>&, int);
template <typename _T, typename _Traits, typename _Allocator> bool operator >= (const String<_T, _Traits, _Allocator>&, double);
template <typename _T, typename _Traits, typename _Allocator> bool operator >= (const _T*, const String<_T, _Traits, _Allocator>&);
template <typename _T, typename _Traits, typename _Allocator> bool operator >= (_T, const String<_T, _Traits, _Allocator>&);
template <typename _T, typename _Traits, typename _Allocator> bool operator >= (int, const String<_T, _Traits, _Allocator>&);
template <typename _T, typename _Traits, typename _Allocator> bool operator >= (double, const String<_T, _Traits, _Allocator>&);

template <typename _T, typename _Traits, typename _Allocator> String<_T, _Traits, _Allocator> operator + (const String<_T, _Traits, _Allocator>&, const String<_T, _Traits, _Allocator>&);
template <typename _T, typename _Traits, typename _Allocator> String<_T, _Traits, _Allocator> operator + (const String<_T, _Traits, _Allocator>&, const _T*);
template <typename _T, typename _Traits, typename _Allocator> String<_T, _Traits, _Allocator> operator + (const String<_T, _Traits, _Allocator>&, _T);
template <typename _T, typename _Traits, typename _Allocator> String<_T, _Traits, _Allocator> operator + (const String<_T, _Traits, _Allocator>&, int);
template <typename _T, typename _Traits, typename _Allocator> String<_T, _Traits, _Allocator> operator + (const String<_T, _Traits, _Allocator>&, double);
////////////////////////////////////////////////////////////////////////////////////////
typedef String<char,  CharTraits, StandardAllocator> CharStr;
typedef String<tchar, CharTraits, StandardAllocator> TCharStr;
typedef String<wchar, UniTraits,  StandardAllocator> UniString;
////////////////////////////////////////////////////////////////////////////////////////
// c-runtime wrap
// --------- ----
void    __DECLSPEC__ TrimSpace(tchar*, ushort = 2);
tchar*  __DECLSPEC__ SkipSymbol(tchar*, tchar);
tchar*  __DECLSPEC__ SkipSymbols(tchar*, const tchar* = null);
tchar*  __DECLSPEC__ SkipTo(tchar*, tchar);
tchar*  __DECLSPEC__ SkipLWS(tchar*);

tchar*  __DECLSPEC__ GetLine(const tchar*, tchar*);
String<>
        __DECLSPEC__ GetString(const tchar*, uint);
tchar*  __DECLSPEC__ HasToken(const tchar*, const tchar*, const tchar* = null, bool = true);

tchar*  __DECLSPEC__ StrClone(const tchar*);

int     __DECLSPEC__ StrLen(const tchar*);
int     __DECLSPEC__ StrCompare(const tchar*, const tchar*);
int     __DECLSPEC__ StrNCompare(const tchar*, const tchar*, size_t);
int     __DECLSPEC__ StrICompare(const tchar*, const tchar*);
int     __DECLSPEC__ StrNICompare(const tchar*, const tchar*, size_t);
int     __DECLSPEC__ StrColl(const tchar*, const tchar*);
int     __DECLSPEC__ StrIColl(const tchar*, const tchar*);
int     __DECLSPEC__ StrNColl(const tchar*, const tchar*, size_t);
int     __DECLSPEC__ StrNIColl(const tchar*, const tchar*, size_t);
tchar*  __DECLSPEC__ StrCopy(tchar*, const tchar*);
tchar*  __DECLSPEC__ StrNCopy(tchar*, const tchar*, size_t);
tchar*  __DECLSPEC__ StrCaten(tchar*, const tchar*);
tchar*  __DECLSPEC__ StrNCaten(tchar*, const tchar*, size_t);
tchar*  __DECLSPEC__ StrChar(const tchar*, int);
tchar*  __DECLSPEC__ StrRChar(const tchar*, int);
tchar*  __DECLSPEC__ StrSubstr(const tchar*, const tchar*);
tchar*  __DECLSPEC__ StrUpper(tchar*);
tchar*  __DECLSPEC__ StrLower(tchar*);
tchar*  __DECLSPEC__ Strpbrk(const tchar*, const tchar*);
int     __DECLSPEC__ StrSpan(const tchar*, const tchar*);
int     __DECLSPEC__ StrCSpan(const tchar*, const tchar*);
long    __DECLSPEC__ StrToInteger(const tchar*, tchar** = null, int = 10);
double  __DECLSPEC__ StrToDouble(const tchar*, tchar** = null);

int     __DECLSPEC__ StrLenW(const wchar*);
int     __DECLSPEC__ StrCompareW(const wchar*, const wchar*);
int     __DECLSPEC__ StrNCompareW(const wchar*, const wchar*, size_t);
int     __DECLSPEC__ StrICompareW(const wchar*, const wchar*);
int     __DECLSPEC__ StrNICompareW(const wchar*, const wchar*, size_t);
int     __DECLSPEC__ StrCollW(const wchar*, const wchar*);
int     __DECLSPEC__ StrICollW(const wchar*, const wchar*);
int     __DECLSPEC__ StrNCollW(const wchar*, const wchar*, size_t);
int     __DECLSPEC__ StrNICollW(const wchar*, const wchar*, size_t);
wchar*  __DECLSPEC__ StrCopyW(wchar*, const wchar*);
wchar*  __DECLSPEC__ StrNCopyW(wchar*, const wchar*, size_t);
wchar*  __DECLSPEC__ StrCatenW(wchar*, const wchar*);
wchar*  __DECLSPEC__ StrNCatenW(wchar*, const wchar*, size_t);
wchar*  __DECLSPEC__ StrCharW(const wchar*, int);
wchar*  __DECLSPEC__ StrSubstrW(const wchar*, const wchar*);
wchar*  __DECLSPEC__ StrUpperW(wchar*);
wchar*  __DECLSPEC__ StrLowerW(wchar*);
wchar*  __DECLSPEC__ StrpbrkW(const wchar*, const wchar*);
int     __DECLSPEC__ StrSpanW(const wchar*, const wchar*);
int     __DECLSPEC__ StrCSpanW(const wchar*, const wchar*);
long    __DECLSPEC__ StrToIntegerW(const wchar*, wchar** = null, int = 10);
double  __DECLSPEC__ StrToDoubleW(const wchar*, wchar** = null);

int     __DECLSPEC__ MultiByteToWideChar(const char*, int, wchar*, int, uint = CP_ACP, uint = 0);
int     __DECLSPEC__ WideCharToMultiByte(const wchar*, int, char*, int, uint = CP_ACP, uint = 0, const char* = null, BOOL* = null);

bool    __DECLSPEC__ StringFromResource(tchar*, ushort, uint, HINSTANCE = 0);
template <typename _T, typename _Traits, typename _Allocator>
bool                 StringFromResource(String<_T, _Traits, _Allocator>&, uint, HINSTANCE = 0);

void    __DECLSPEC__ StringToSoundex(const tchar*, tchar*);

char*   __DECLSPEC__ AILW2A(const wchar*);
wchar*  __DECLSPEC__ AILA2W(const char*);

void    __DECLSPEC__ StrToHex(const byte*, uint, byte*);
void    __DECLSPEC__ HexToStr(const byte*, uint, byte*);

int     __DECLSPEC__ StrCompareWithEsc(const tchar*, const tchar*);
int     __DECLSPEC__ StrICompareWithEsc(const tchar*, const tchar*);
void    __DECLSPEC__ ConvertEsc(tchar*, bool = true);
void    __DECLSPEC__ RemoveEsc(tchar*, bool = true);
bool    __DECLSPEC__ IsUnsafeChar(tchar);
bool    __DECLSPEC__ IsNonAsciiChar(tchar);

int     __DECLSPEC__ IsPrefix(const tchar*, const tchar*);
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __STRING_H__
