////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __VALIDATOR_INL__
#define __VALIDATOR_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class ValidatorEntry
// ----- --------------
__INLINE__ tchar ValidatorEntry::GetEntry() const
{
    return Entry;
}

__INLINE__ void ValidatorEntry::SetEntry(tchar _c)
{
    Entry = _c;
}

__INLINE__ uint ValidatorEntry::GetFlags() const
{
    return Flags;
}

__INLINE__ void ValidatorEntry::SetFlags(uint _o)
{
    Flags = _o;
}

__INLINE__ TCharStr ValidatorEntry::GetSubmask() const
{
    return Submask;
}

__INLINE__ const TCharStr* ValidatorEntry::GetSubmaskAsPtr() const
{
    return reinterpret_cast<const TCharStr*>(&Submask);
}

__INLINE__ const tchar* ValidatorEntry::GetSubmaskAsChar() const
{
    return Submask;
}

__INLINE__ void ValidatorEntry::SetSubmaskAsStr(TCharStr& _str)
{
    Submask = _str;
}

__INLINE__ int ValidatorEntry::GetSubmaskAsIndex() const
{
    return Index;
}

__INLINE__ void ValidatorEntry::SetSubmaskAsIndex(int _i)
{
    Index = _i;
}
////////////////////////////////////////////////////////////////////////////////////////
// class Validator
// ----- ---------
__INLINE__ int Validator::GetPosition() const
{
    return Position;
}

__INLINE__ void Validator::SetPosition(int _pos)
{
    Position = _pos;
}

__INLINE__ bool Validator::IsFreeInput() const
{
    return FreeInput;
}

__INLINE__ uint Validator::GetFlags() const
{
    return Flags;
}

__INLINE__ void Validator::SetFlags(uint _flags)
{
   _flags &= ~AutoHint;
    Flags  = _flags;
}

__INLINE__ const BitSet& Validator::GetBits() const
{
    return Bits;
}

__INLINE__ tchar Validator::GetPlaceholderString() const
{
    return PlaceholderString;
}

__INLINE__ void Validator::SetPlaceholderString(tchar _pl)
{
    PlaceholderString = _pl;
}

__INLINE__ tchar Validator::GetPlaceholderGroup() const
{
    return PlaceholderGroup;
}

__INLINE__ void Validator::SetPlaceholderGroup(tchar _pl)
{
    PlaceholderGroup = _pl;
}

__INLINE__ tchar Validator::GetPlaceholderMask() const
{
    return PlaceholderMask;
}

__INLINE__ void Validator::SetPlaceholderMask(tchar _pl)
{
    PlaceholderMask = _pl;
}

__INLINE__ tchar Validator::GetPlaceholderPassword() const
{
    return PlaceholderPassword;
}

__INLINE__ void Validator::SetPlaceholderPassword(tchar _pl)
{
    PlaceholderPassword = _pl;
}

__INLINE__ TCharStr Validator::GetMask() const
{
    return Mask;
}

__INLINE__ TCharStr* Validator::GetMaskAsPtr() const
{
    return const_cast<TCharStr*>(&Mask);
}

__INLINE__ tchar* Validator::GetMaskAsChar() const
{
    return const_cast<tchar*>(Mask.GetData());
}

__INLINE__ TCharStr Validator::GetFormatString() const
{
    return FormatString;
}

__INLINE__ TCharStr* Validator::GetFormatStringAsPtr() const
{
    return const_cast<TCharStr*>(&FormatString);
}

__INLINE__ tchar* Validator::GetFormatStringAsChar() const
{
    return const_cast<tchar*>(FormatString.GetData());
}

__INLINE__ void Validator::Reset()
{
    Position = 0;
}
////////////////////////////////////////////////////////////////////////////////////////
// class BaseTimeValidator
// ----- -----------------
__INLINE__ Time& BaseTimeValidator::GetTime()
{
    return TimeValue;
}

__INLINE__ const Time& BaseTimeValidator::GetTime( ) const
{
    return TimeValue;
}

__INLINE__ void BaseTimeValidator::SetTime(Time& _tm)
{
    TimeValue = _tm;
}

__INLINE__ Time& BaseTimeValidator::GetTimeMin()
{
    return TimeValueMin;
}

__INLINE__ const Time& BaseTimeValidator::GetTimeMin() const
{
    return TimeValueMin;
}

__INLINE__ Time* BaseTimeValidator::GetTimeMinAsPtr()
{
    return &TimeValueMin;
}

__INLINE__ const Time* BaseTimeValidator::GetTimeMinAsPtr() const
{
    return &TimeValueMin;
}

__INLINE__ void BaseTimeValidator::SetTimeMin(Time& tm)
{
    TimeValueMin = tm;
}

__INLINE__ Time& BaseTimeValidator::GetTimeMax()
{
    return TimeValueMax;
}

__INLINE__ const Time& BaseTimeValidator::GetTimeMax() const
{
    return TimeValueMax;
}

__INLINE__ Time* BaseTimeValidator::GetTimeMaxAsPtr()
{
    return &TimeValueMax;
}

__INLINE__ const Time* BaseTimeValidator::GetTimeMaxAsPtr() const
{
    return &TimeValueMax;
}

__INLINE__ void BaseTimeValidator::SetTimeMax(Time& tm)
{
    TimeValueMax = tm;
}

__INLINE__ TCharStr* BaseTimeValidator::GetOriginalMaskAsPtr()
{
    return &OriginalMask;
}

__INLINE__ void BaseTimeValidator::SetOriginalMask(tchar* mask)
{
    OriginalMask = mask;
}

__INLINE__ bool BaseTimeValidator::GetData()
{
    return true;
}
////////////////////////////////////////////////////////////////////////////////////////
// class TimeValidator
// ----- -------------
__INLINE__ uint TimeValidator::GetStyle() const
{
    return Style;
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __VALIDATOR_INL__
