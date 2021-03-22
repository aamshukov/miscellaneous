////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __AIL_RECT_INL__
#define __AIL_RECT_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class Rect
// ----- ----
__INLINE__ void Rect::SetNull()
{
#ifdef __PALM_OS__
    topLeft.x = topLeft.y = extent.x = extent.y = 0;
#else
    left = top = right = bottom = 0;
#endif
}

__INLINE__ void  Rect::SetEmpty()
{
    SetNull();
}

__INLINE__ void Rect::Set(int _left, int _top, int _right, int _bottom)
{
#ifdef __PALM_OS__
    topLeft.x = static_cast<Coord>(_left);
    topLeft.y = static_cast<Coord>(_top);
    extent.x  = static_cast<Coord>(Abs(_right-_left));
    extent.y  = static_cast<Coord>(Abs(_bottom-_top));
#else
    left   = _left;
    top    = _top;
    right  = _right;
    bottom = _bottom;
#endif
}

__INLINE__ void Rect::Set(int _x, int _y, uint _w, uint _h)
{
#ifdef __PALM_OS__
    topLeft.x = static_cast<Coord>(_x);
    topLeft.y = static_cast<Coord>(_y);
    extent.x  = static_cast<Coord>(_w);
    extent.y  = static_cast<Coord>(_h);
#else
    left   = _x;
    top    = _y;
    right  = left+_w;
    bottom = top+_h;
#endif
}

__INLINE__ bool Rect::IsEmpty() const
{
#ifdef __PALM_OS__
    return (extent.x <= 0 || extent.y <= 0);
#else
    return (left >= right || top >= bottom);
#endif
}

__INLINE__ bool Rect::IsNull() const
{
#ifdef __PALM_OS__
    return (topLeft.x == 0 && topLeft.y == 0 && extent.x == 0 && extent.y == 0);
#else
    return (left == 0 && right == 0 && top == 0 && bottom == 0);
#endif
}

__INLINE__ Point Rect::TopLeft() const
{
#ifdef __PALM_OS__
    return Point(topLeft.x, topLeft.y);
#else
    return Point(left, top);
#endif    
}

__INLINE__ Point Rect::TopRight() const
{
#ifdef __PALM_OS__
    return Point(topLeft.x+extent.x, topLeft.y);
#else
    return Point(right, top);
#endif    
}

__INLINE__ Point Rect::BottomLeft() const
{
#ifdef __PALM_OS__
    return Point(topLeft.x, topLeft.y+extent.y);
#else
    return Point(left, bottom);
#endif    
}

__INLINE__ Point Rect::BottomRight() const
{
#ifdef __PALM_OS__
    return Point(topLeft.x+extent.x, topLeft.y+extent.y);
#else
    return Point(right, bottom);
#endif    
}

__INLINE__ int Rect::Width() const
{
#ifdef __PALM_OS__
    return extent.x;
#else
    return right-left;
#endif
}

__INLINE__ int Rect::Height() const
{
#ifdef __PALM_OS__
    return extent.y;
#else
    return bottom-top;
#endif
}

__INLINE__ Size Rect::GetSize() const
{
    return Size(Width(), Height());
}

__INLINE__ int Rect::GetArea() const
{
    return int(Width())*int(Height());
}

__INLINE__ Rect::operator const Point* () const
{
    return (const Point*)this;
}

__INLINE__ Rect::operator Point* ()
{
    return (Point*)this;
}

#ifdef __MS_WINDOWS__
__INLINE__ Rect::operator const RECT* () const
{
    return (const RECT*)this;
}

__INLINE__ Rect::operator RECT* ()
{
    return (RECT*)this;
}
#endif

#ifdef __PALM_OS__
__INLINE__ Rect::operator const RectangleType* () const
{
    return (const RectangleType*)this;
}

__INLINE__ Rect::operator RectangleType* ()
{
    return (RectangleType*)this;
}
#endif

__INLINE__ bool Rect::operator == (const Rect& _other) const
{
#ifdef __PALM_OS__
    return (_other.topLeft.x == topLeft.x && _other.topLeft.y == topLeft.y && _other.extent.x == extent.x && _other.extent.y == extent.y);
#else
    return (_other.left == left && _other.top == top && _other.right == right && _other.bottom == bottom);
#endif
}

__INLINE__ bool Rect::operator != (const Rect& _other) const
{
    return !(_other == *this);
}

__INLINE__ bool Rect::PtInRect(const Point& _pt) const
{
#ifdef __PALM_OS__
    return (_pt.x >= topLeft.x && _pt.x < topLeft.x+extent.x &&
            _pt.y >= topLeft.y && _pt.y < topLeft.y+extent.y);
#else
    return (_pt.x >= left && _pt.x < right && _pt.y >= top && _pt.y < bottom);
#endif
}

__INLINE__ bool Rect::Contains(const Point& _pt) const
{
#ifdef __PALM_OS__
    return (_pt.x >= topLeft.x && _pt.x < topLeft.x+extent.x &&
            _pt.y >= topLeft.y && _pt.y < topLeft.y+extent.y);
#else
    return (_pt.x >= left && _pt.x < right && _pt.y >= top && _pt.y < bottom);
#endif
}

__INLINE__ bool Rect::Contains(const Rect& _other) const
{
#ifdef __PALM_OS__
    return (_other.topLeft.x >= topLeft.x && _other.topLeft.x+_other.extent.x <= topLeft.x+extent.x &&
            _other.topLeft.y >= topLeft.y && _other.topLeft.y+_other.extent.y <= topLeft.y+extent.y);
#else
    return (_other.left >= left && _other.right <= right && _other.top >= top && _other.bottom <= bottom);
#endif
}

__INLINE__ bool Rect::Touches(const Rect& _other) const
{
#ifdef __PALM_OS__
    return (_other.topLeft.x > topLeft.x && _other.topLeft.x+extent.x < topLeft.x+extent.x &&
            _other.topLeft.y > topLeft.y && _other.topLeft.y+extent.y < topLeft.y+extent.y);
#else
    return (_other.right > left && _other.left < right && _other.bottom > top && _other.top < bottom);
#endif
}

__INLINE__ Rect Rect::OffsetBy(int _dx, int _dy) const
{
#ifdef __PALM_OS__
    return Rect(topLeft.x+_dx, topLeft.y+_dy, static_cast<uint>(extent.x), static_cast<uint>(extent.y));
#else
    return Rect(left+_dx, top+_dy, right+_dx, bottom+_dy);
#endif
}

__INLINE__ Rect Rect::operator + (const Size& _sz) const
{
    return OffsetBy(_sz.cx, _sz.cy);
}

__INLINE__ Rect Rect::operator - (const Size& _sz) const
{
    return OffsetBy(-_sz.cx, -_sz.cy);
}

__INLINE__ Rect Rect::InflatedBy(int _dx, int _dy) const
{
#ifdef __PALM_OS__
    return Rect(topLeft.x-_dx, topLeft.y-_dy, extent.x+_dx, extent.y+_dy);
#else
    return Rect(left-_dx, top-_dy, right+_dx, bottom+_dy);
#endif
}

__INLINE__ Rect Rect::InflatedBy(const Size& _sz) const
{
    return InflatedBy(_sz.cx, _sz.cy);
}

__INLINE__ Rect Rect::Normalized() const
{
#ifdef __PALM_OS__
    return Rect(*this);
#else
    return Rect(Min(left, right), Min(top, bottom), Max(left, right), Max(top, bottom));
#endif
}

__INLINE__ Rect Rect::operator & (const Rect& _other) const
{
#ifdef __PALM_OS__
    return Rect(Max(topLeft.x, _other.topLeft.x),
                Max(topLeft.y, _other.topLeft.y),
                Min(topLeft.x+extent.x, _other.topLeft.x+_other.extent.x),
                Min(topLeft.y+extent.y, _other.topLeft.y+_other.extent.y));
#else
    return Rect(Max(left, _other.left), Max(top, _other.top), Min(right, _other.right), Min(bottom, _other.bottom));
#endif
}

__INLINE__ Rect Rect::operator | (const Rect& _other) const
{
#ifdef __PALM_OS__
    return Rect(Min(topLeft.x, _other.topLeft.x),
                Min(topLeft.y, _other.topLeft.y),
                Max(topLeft.x+extent.x, _other.topLeft.x+_other.extent.x),
                Max(topLeft.y+extent.y, _other.topLeft.y+_other.extent.y));
#else
    return Rect(Min(left, _other.left), Min(top, _other.top), Max(right, _other.right), Max(bottom, _other.bottom));
#endif
}

__INLINE__ Rect& Rect::operator += (const Size& _delta)
{
    Offset(_delta.cx, _delta.cy);
    return *this;
}

__INLINE__ Rect& Rect::operator -= (const Size& _delta)
{
    return *this += -_delta;
}

__INLINE__ Rect& Rect::Inflate(const Size& _delta)
{
    return Inflate(_delta.cx, _delta.cy);
}

__INLINE__ Rect& Rect::Normalize()
{
#ifdef __PALM_OS__
#else
    if(left > right)
    {
        Swap(left, right);
    }

    if(top > bottom)
    {
        Swap(top, bottom);
    }
#endif
    return *this;
}

__INLINE__ Rect& Rect::Offset(int _dx, int _dy)
{
#ifdef __PALM_OS__
    topLeft.x += static_cast<Coord>(_dx);
    topLeft.y += static_cast<Coord>(_dy);
#else
    left   += _dx;
    top    += _dy;
    right  += _dx;
    bottom += _dy;
#endif
    return *this;
}

__INLINE__ Rect& Rect::Inflate(int _dx, int _dy)
{
#ifdef __PALM_OS__
    topLeft.x  -= static_cast<Coord>(_dx);
    topLeft.y  -= static_cast<Coord>(_dy);
    extent.x   += static_cast<Coord>(_dx);
    extent.y   += static_cast<Coord>(_dy);
#else
    left   -= _dx;
    top    -= _dy;
    right  += _dx;
    bottom += _dy;
#endif
    return *this;
}

__INLINE__ Rect& Rect::operator &= (const Rect& _other)
{
    if(!IsNull())
    {
        if(_other.IsNull())
        {
            SetNull();
        }
        else
        {
#ifdef __PALM_OS__
            topLeft.x = Max(topLeft.x, _other.topLeft.x);
            topLeft.y = Max(topLeft.y, _other.topLeft.y);
            extent.x  = Min(extent.x,  _other.extent.x);
            extent.y  = Min(extent.y,  _other.extent.y);
#else
            left   = Max(left,   _other.left);
            top    = Max(top,    _other.top);
            right  = Min(right,  _other.right);
            bottom = Min(bottom, _other.bottom);
#endif
        }
    }
    return *this;
}

__INLINE__ Rect& Rect::operator |= (const Rect& _other)
{
    if(!_other.IsNull())
    {
        if(IsNull())
        {
            *this = _other;
        }
        else
        {
#ifdef __PALM_OS__
            topLeft.x = Min(topLeft.x, _other.topLeft.x);
            topLeft.y = Min(topLeft.y, _other.topLeft.y);
            extent.x  = Max(extent.x,  _other.extent.x);
            extent.y  = Max(extent.y,  _other.extent.y);
#else
            left   = Min(left,   _other.left);
            top    = Min(top,    _other.top);
            right  = Max(right,  _other.right);
            bottom = Max(bottom, _other.bottom);
#endif
        }
    }
    return *this;
}

#ifndef __PALM_OS__
__INLINE__ void Rect::ToSquare()
{
    bottom = right = Min(bottom, right);
}

__INLINE__ Rect Rect::ToSquareBy()
{
    Rect r(left, top, right, bottom);
    r.bottom = r.right = Min(r.bottom, r.right);
    return r;
}
#endif

__INLINE__ Point Rect::GetCenterPoint() const
{
#ifdef __PALM_OS__
    return Point((topLeft.x+topLeft.x+extent.x)/2, (topLeft.y+topLeft.y+extent.y)/2);
#else
    return Point((left+right)/2, (top+bottom)/2);
#endif
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __AIL_RECT_INL__
