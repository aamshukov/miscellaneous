////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __POINT_INL__
#define __POINT_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class Point
// ----- -----
#ifdef __MS_WINDOWS__
__INLINE__ Point::operator const POINT* () const
{
    return (const POINT*)this;
}

__INLINE__ Point::operator POINT* ()
{
    return (POINT*)this;
}
#endif

#ifdef __PALM_OS__
__INLINE__ Point::operator const PointType* () const
{
    return (const PointType*)this;
}

__INLINE__ Point::operator PointType* ()
{
    return (PointType*)this;
}
#endif

__INLINE__ bool Point::operator == (const Point& _other) const
{
    return (_other.x == x && _other.y == y);
}

__INLINE__ bool Point::operator != (const Point& _other) const
{
    return (_other.x != x || _other.y != y);
}

__INLINE__ Point Point::operator + (const Size& _sz) const
{
    return Point(x+_sz.cx, y+_sz.cy);
}

__INLINE__ Size Point::operator - (const Point& _pt) const
{
    return Size(x-_pt.x, y-_pt.y);
}

__INLINE__ Point Point::operator - (const Size& _sz) const
{
    return Point(x-_sz.cx, y-_sz.cy);
}

__INLINE__ Point Point::operator - () const
{
    return Point(-x, -y);
}

__INLINE__ Point& Point::Offset(int _dx, int _dy)
{
#ifdef __PALM_OS__
    x += static_cast<Coord>(_dx);
    y += static_cast<Coord>(_dy);
#else
    x += _dx;
    y += _dy;
#endif    
    return *this;
}

__INLINE__ Point& Point::Offset(const Point& _pt)
{
    x += _pt.x;
    y += _pt.y;
    return *this;
}

__INLINE__ Point& Point::Offset(const Size& _sz)
{
#ifdef __PALM_OS__
    x += static_cast<Coord>(_sz.cx);
    y += static_cast<Coord>(_sz.cy);
#else
    x += _sz.cx;
    y += _sz.cy;
#endif
    return *this;
}

__INLINE__ Point& Point::operator += (const Point& _pt)
{
    x += _pt.x;
    y += _pt.y;
    return *this;
}

__INLINE__ Point& Point::operator += (const Size& _sz)
{
#ifdef __PALM_OS__
    x += static_cast<Coord>(_sz.cx);
    y += static_cast<Coord>(_sz.cy);
#else
    x += _sz.cx;
    y += _sz.cy;
#endif
    return *this;
}

__INLINE__ Point& Point::operator -= (const Point& _pt)
{
    x -= _pt.x;
    y -= _pt.y;
    return *this;
}

__INLINE__ Point& Point::operator -= (const Size& _sz)
{
#ifdef __PALM_OS__
    x -= static_cast<Coord>(_sz.cx);
    y -= static_cast<Coord>(_sz.cy);
#else
    x -= _sz.cx;
    y -= _sz.cy;
#endif
    return *this;
}

__INLINE__ Point Point::OffsetBy(int _dx, int _dy) const
{
    return Point(x+_dx, y+_dy);
}

__INLINE__ Point Point::OffsetBy(const Size& _sz) const
{
    return Point(x+_sz.cx, y+_sz.cy);
}

#ifdef __MS_WINDOWS__
__INLINE__ int Point::Magnitude() const
{
    // Return the distance between the origin and the point.
    return Sqrt(long(x)*long(x)+long(y)*long(y));
}
#endif
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __POINT_INL__
