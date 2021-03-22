////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __VALIDATOR_H__
#define __VALIDATOR_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class ValidatorEntry
// ----- --------------
class __DECLSPEC__ ValidatorEntry : public ListNodeBase<ValidatorEntry, tchar>
{
    friend class Validator;

    public:

    enum EFlag
    {
        Substring  = 0x0001,
        Group      = 0x0002,
        Mask       = 0x0004,
        Letter     = 0x0010, 
        Separator  = 0x0020,
        Disable    = 0x0040
    };

    private:
     tchar              Entry;
     int                Index;
     uint               Flags;
     TCharStr           Submask;
    public:
                        ValidatorEntry(tchar, uint);
     virtual           ~ValidatorEntry();

     tchar              GetEntry()                  const;
     void               SetEntry(tchar);

     uint               GetFlags()                  const;
     void               SetFlags(uint);

     TCharStr           GetSubmask()                const;
     const TCharStr*    GetSubmaskAsPtr()           const;
     const tchar*       GetSubmaskAsChar()          const;
     void               SetSubmaskAsStr(TCharStr&);
     int                GetSubmaskAsIndex()         const;
     void               SetSubmaskAsIndex(int);
};
////////////////////////////////////////////////////////////////////////////////////////
// class Validator
// ----- ---------
//
//  Syntax:
//      Filter:
//          \x - any symbol                                         [&b|\\b] 
//          A  - upper letter, digit and space                      [&A]
//          a  - lower letter, digit and space                      [&a]
//          L  - upper letter                                       [&L]
//          l  - lower letter                                       [&l]
//          0  - only digit                                         [&0]
//          9  - digit and space                                    [&9]
//          #  - digit, minus, plus and space                       [&#]
//          E  - digit, minus, plus, period and space (scientific)  [&E]
//          .  - punct                                              [&.]
//          ?  - any single character                               [&?]
//          *  - any character or any sequentance of characters     [&*]
//      Meta characters:
//          [] - one character [A-Za-z] or [&A|&a] can have recur ! ...
//          {} - a group {([&0][&0]-[&0][&0]-[&0]{[&A]}} can have recur ! ...
//          ^  - syntax is the same like a group number ^5
//          !  - except character [&A|&a|&0!B!5!z]
//          |  - logical OR [&A|&a|&0]
//          &  - special prefix [&A]
//          $  - repeat character [$55] 
//  Example:
//   "City:{[ABC|abc]}[A-H|A|\\A|&A|&a|0-9!2!b!v!C]ABCabc{[&*!.!*!,]-[&L|&l]-[&#]-[&0]}[&*]"
//  Substrings:
//   "City:" "ABCabc" 
//  Groups:
//   {[ABC|abc]} {[&*!.!,]-[&L|&l]-[&#]-[&0]}
//  Filters:
//   [A-H|A|\\A|&A|&a|0-9!2!b!v!C] [&*]
////////////////////////////////////////////////////////////////////////////////////////
class __DECLSPEC__ Validator
{
    friend class BaseTimeValidator;
    friend class TimeValidator;
    friend class Field;

    public:

    enum EFlag
    { 
        AutoHint          = 0x00000001,
        AutoFeed          = 0x00000002,
        AutoDefault       = 0x00000004,
        DisplayAsPassword = 0x00000008
    };

    private:

    struct _KeyExtractor
    {
        const tchar& operator() (const ValidatorEntry&) const;
    };

    struct _Comparator
    {
        int operator() (const tchar&, const tchar&) const;
    };

    private: 
    _KeyExtractor           KeyExtractor;
    _Comparator             Comparator;

     bool                   FreeInput;
     tchar                  PlaceholderString;
     tchar                  PlaceholderGroup;
     tchar                  PlaceholderMask;
     tchar                  PlaceholderPassword;
     int                    Position;
     uint                   Flags;

     String<>               Mask;
     String<>               FormatString;
     String<>               MirrorString;

     BitSet                 Bits;

     typedef List<ValidatorEntry, tchar, _KeyExtractor, _Comparator> _ListString;
    _ListString             ListString;
    private:
                            Validator(const Validator&);
     const Validator&       operator = (const Validator&);

     void                   Init(tchar*);

     void                   CorrectMask();
     void                   CheckSyntax();

     tchar*                 BuildString(tchar* = null, bool = false, int = 0);
     void                   BuildFormatString(int = 0, int = 0, bool = false);

     void                   AddEntry(String<>&, tchar, uint);

     tchar*                 GetSubmask(String<>&, tchar*, int = 0);
     tchar*                 GetRepeatSymbolsFromGroup(tchar*, int&, int = 0);

     tchar*                 ArrangeBits(tchar* = null, int = 0);

     tchar*                 SkipGroup(tchar*, int = 0);
     tchar*                 SkipMask(tchar*, int = 0);

     int                    GetPosition()                   const;
     void                   SetPosition(int);
     bool                   GetFirstPosition();
     bool                   GetLastPosition();
     bool                   GetNextPosition();
     bool                   GetPrevPosition();
     bool                   CorrectPosition(int = 0);

     void                   FindFirstVacantPlace();

     tchar*                 GetFreeInput(tchar*, int = 0);

     tchar*                 GetNextSubstring(tchar*, String<>&);

     bool                   Delete(int, int, bool = true);

     bool                   IsSeparator();
     bool                   IsFreeInput()                   const;
    protected:
     virtual void           BuildMask(tchar* = null);

     virtual bool           IsInputValid(tchar);
     virtual bool           IsValid();

     virtual bool           DefaultValue(String<>&);
     virtual bool           GetData();
    public:
     // ctor/dtor
                            Validator(tchar* = null, tchar = Char::Underscore, tchar = Char::Underscore, tchar = Char::Underscore, tchar = Char::Asterisk, uint = 0x00000007, bool = true);
     virtual               ~Validator();

     // access/protocol
     uint                   GetFlags()                      const;
     void                   SetFlags(uint);

     uint                   GetEntryFlags(int = -1);

     const BitSet&          GetBits()                       const;

     tchar                  GetPlaceholderString()          const;
     void                   SetPlaceholderString(tchar);

     tchar                  GetPlaceholderGroup()           const;
     void                   SetPlaceholderGroup(tchar);

     tchar                  GetPlaceholderMask()            const;
     void                   SetPlaceholderMask(tchar);

     tchar                  GetPlaceholderPassword()        const;
     void                   SetPlaceholderPassword(tchar);

     String<>               GetMask()                       const;
     String<>*              GetMaskAsPtr()                  const;
     tchar*                 GetMaskAsChar()                 const;

     void                   ResetMask(tchar*);

     String<>               GetFormatString()               const;
     String<>*              GetFormatStringAsPtr()          const;
     tchar*                 GetFormatStringAsChar()         const;

     void                   SetupDefault();

     ushort                 GetFirstLeftDisableEntry();
     ushort                 GetLastRightDisableEntry();

     void                   Reset();
    public:

    class __DECLSPEC__ XValidator : public X
    {
        public:

        enum EError
        {
            InvalidSyntax = 0x00000100
        };

        public:
            XValidator(uint = X::Failure);
    };

    friend class XValidator;
};
////////////////////////////////////////////////////////////////////////////////////////
// class BaseTimeValidator
// ----- -----------------
//
// Syntax:
//  M    - a number without a leading 0 (zero) for single-digit months.
//  MM   - a number with a leading 0 (zero) for single-digit months.
//  MMM  - a three-letter abbreviation.
//  MMMM - the full name of the month.
//  d    - a number without a leading 0 (zero) for single-digit days.
//  dd   - a number with a leading 0 (zero) for single-digit days.
//  ddd  - a three-letter abbreviation.
//  dddd - the full name of the day of the week.
//  yy   - two digits with a leading 0 (zero) for years.
//  yyyy - four digits.
//  h    - without a leading 0 (zero) for single-digit hours 0-12.
//  H    - without a leading 0 (zero) for single-digit hours 0-24.
//  hh   - with a leading 0 (zero) for single-digit hours 0-12.
//  HH   - with a leading 0 (zero) for single-digit hours 0-24.
//  m    - without a leading 0 (zero) for single-digit minutes.
//  mm   - with a leading 0 (zero) for single-digit minutes.
//  ss   - with a leading 0 (zero) for single-digit seconds.
//  cc   - with a leading 0 (zero) for single-digit hundred seconds.
//  A    - AM/PM
//  a    - am/pm
//  P    - A/P
//  p    - a/p
// Example:
//  "{&M/&MM/&MMM/&MMMM &d &dd &ddd &dddd &yy &yyyy &h &hh &H &HH &m &mm &ss &A &a &P &p}"
////////////////////////////////////////////////////////////////////////////////////////
class __DECLSPEC__ BaseTimeValidator : public Validator
{
    friend class Field;

    private:
     Time                       TimeValue;
     Time                       TimeValueMin;
     Time                       TimeValueMax;

     String<>                     OriginalMask;
    private:
                                BaseTimeValidator(const BaseTimeValidator&);
     const BaseTimeValidator&   operator = (const BaseTimeValidator&);

     tchar*                     BuildSubmask(tchar*, int = 0);
     tchar*                     BuildDefaultValue(tchar*, String<>&, int = 0);
    protected:
     virtual void               BuildMask(tchar* = null);
     virtual bool               IsValid();
     virtual bool               DefaultValue(String<>&);
     virtual bool               GetData();
    public:
                                BaseTimeValidator(tchar* = null, tchar = '_', tchar = '_', tchar = '_', tchar = '*', uint = 0x00000007, bool = false);
                               ~BaseTimeValidator();

     Time&                      GetTime();
     const Time&                GetTime( )              const;
     void                       SetTime(Time&);
     Time&                      GetTimeMin();
     const Time&                GetTimeMin()            const;
     Time*                      GetTimeMinAsPtr();
     const Time*                GetTimeMinAsPtr()       const;
     void                       SetTimeMin(Time&);
     Time&                      GetTimeMax();
     const Time&                GetTimeMax()            const;
     Time*                      GetTimeMaxAsPtr();
     const Time*                GetTimeMaxAsPtr()       const;
     void                       SetTimeMax(Time&);
     String<>*                    GetOriginalMaskAsPtr();
     void                       SetOriginalMask(tchar*);
};
////////////////////////////////////////////////////////////////////////////////////////
// class TimeValidator
// ----- -------------
//
// Syntax:
//  1.  M/d/yy
//  2.  dddd,MMMM dd,yyyy
//  3.  d MMMM,yyyy
//  4.  dd MMMM yyyy
//  5.  MMMM d, yyyy
//  6.  d-MMM-yy
//  7.  MMMM,yy
//  8.  MMM-yy
//  9.  MM/dd/yy h:mm AM/PM
//  10. MM/dd/yy h:mm:ss AM/PM
//  11. h:mm AM/PM 
//  12. h:mm:ss AM/PM 
//  13. H:mm
//  14. H:mm:ss and etc.
////////////////////////////////////////////////////////////////////////////////////////
class __DECLSPEC__ TimeValidator : public BaseTimeValidator
{
    friend class Field;

    public:

    enum EStyle
    {
        MMddyy         = 0x00000001,
        MMddyyyy       = 0x00000002,
        ddddMMMMddyyyy = 0x00000004,
        ddMMMMyyyy     = 0x00000008,
        MMMddyyyy      = 0x00000010,
        MMMMddyyyy     = 0x00000020,
        ddMMMyy        = 0x00000040,
        MMMMyy         = 0x00000080,
        MMMyy          = 0x00000100,
        MMddyyhhmmAM   = 0x00000200,
        MMddyyhhmmssAM = 0x00000400,
        hhmmAM         = 0x00000800,
        hhmmssAM       = 0x00001000,
        HHmm           = 0x00002000,
        HHmmss         = 0x00004000
    };

    private:
     uint                   Style;
    private:
                            TimeValidator(const TimeValidator&);
     const TimeValidator&   operator = (const TimeValidator&);
    public:
                            TimeValidator(uint = MMddyy);
                           ~TimeValidator();

     virtual bool           TimeFrom_MMddyy(tchar* = null, const tchar* = null);
     virtual bool           TimeFrom_MMddyyyy(tchar* = null, const tchar* = null);
     virtual bool           TimeFrom_ddddMMMMddyyyy(tchar* = null, const tchar* = null);
     virtual bool           TimeFrom_ddMMMMyyyy(tchar* = null, const tchar* = null);
     virtual bool           TimeFrom_MMMddyyyy(tchar* = null, const tchar* = null);
     virtual bool           TimeFrom_MMMMddyyyy(tchar* = null, const tchar* = null);
     virtual bool           TimeFrom_ddMMMyy(tchar* = null, const tchar* = null);
     virtual bool           TimeFrom_MMMMyy(tchar* = null, const tchar* = null);
     virtual bool           TimeFrom_MMMyy(tchar* = null, const tchar* = null);
     virtual bool           TimeFrom_MMddyyhhmmAM(tchar* = null, const tchar* = null);
     virtual bool           TimeFrom_MMddyyhhmmssAM(tchar* = null, const tchar* = null);
     virtual bool           TimeFrom_hhmmAM(tchar* = null, const tchar* = null);
     virtual bool           TimeFrom_hhmmssAM(tchar* = null, const tchar* = null);
     virtual bool           TimeFrom_HHmm(tchar* = null, const tchar* = null);
     virtual bool           TimeFrom_HHmmss(tchar* = null, const tchar* = null);

     virtual bool           IsTimeValid(tchar* = null, const tchar* = null);

     uint                   GetStyle() const;
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __VALIDATOR_H__
