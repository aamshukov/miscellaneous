////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __COLOR_INL__
#define __COLOR_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class Color
// ----- -----
__INLINE__ const Color& Color::operator = (const Color& _other)
{
    if(this != &_other)
    {
        Value = _other.Value;
    }
    return *this;
}

__INLINE__ Color::operator COLORREF() const
{
    return GetValue();
}

__INLINE__ bool Color::operator == (const Color& _other) const
{
    return Value == _other.Value;
}

__INLINE__ bool Color::operator != (const Color& _other) const
{
    return Value != _other.Value;
}

__INLINE__ bool Color::operator == (COLORREF _cr) const
{
    return GetValue() == _cr;
}

__INLINE__ bool Color::operator != (COLORREF _cr) const
{
    return GetValue() != _cr;
}

__INLINE__ COLORREF Color::GetValue() const
{
    return IsSysColor() ? ::GetSysColor(GetIndex()) : Value;
}

__INLINE__ void Color::SetValue(const COLORREF& _value)
{
    Value = _value;
}

__INLINE__ ushort Color::GetIndex() const
{
    return static_cast<ushort>(Value) & 0xFFFF;
}

__INLINE__ Color Color::GetRgb() const
{
    return GetValue();
}

__INLINE__ Color Color::GetPalIndex() const
{
    return static_cast<COLORREF>(GetIndex()) | 0x01000000;
}

__INLINE__ Color Color::GetPalRelative() const
{
    return GetRgb() | 0x02000000;
}

__INLINE__ byte Color::GetRed() const
{
    return static_cast<byte>(static_cast<ushort>(GetValue()));
}

__INLINE__ byte Color::GetGreen() const
{
    return static_cast<byte>(static_cast<ushort>(((static_cast<ushort>(GetValue()))) >> 8));
}

__INLINE__ byte Color::GetBlue() const
{
    return static_cast<byte>(static_cast<ushort>(((static_cast<ushort>(GetValue()))) >> 16));
}

__INLINE__ byte Color::GetFlags() const
{
    return static_cast<byte>(static_cast<ushort>(((static_cast<ushort>(Value))) >> 24));
}

__INLINE__ bool Color::IsSysColor() const
{
    return (Value & 0xFF000000) == 0x80000000;
}

__INLINE__ bool Color::IsSpecialColor() const
{
    return (Value & 0xF0000000) == 0xF0000000;
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __COLOR_INL__
