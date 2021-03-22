////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __AIL_H__
#   include <ail.hpp>
#endif

#ifndef __RECT_INC__
#   include <Rect.inc>
#endif

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class Rect
// ----- ----
Rect::Rect()
{
    SetNull();
}

#ifdef __MS_WINDOWS__
Rect::Rect(const Rect& _rect)
{
    *reinterpret_cast<RECT*>(this) = *(RECT*)&_rect;
}

Rect::Rect(const RECT& _rect)
{
    *reinterpret_cast<RECT*>(this) = _rect;
}
#endif

#ifdef __PALM_OS__
Rect::Rect(const Rect& _rect)
{
    *reinterpret_cast<RectangleType*>(this) = *(RectangleType*)&_rect;
}
#endif

Rect::Rect(int _left, int _top, int _right, int _bottom)
{
    Set(_left, _top, _right, _bottom);
}

Rect::Rect(int _x, int _y, uint _w, uint _h)
{
    Set(_x, _y, _w, _h);
}

Rect::Rect(const Point& _topleft, const Point& _bottomright)
{
    Set(_topleft.x, _topleft.y, _bottomright.x, _bottomright.y);
}

Rect::Rect(const Point& _origin, const Size& _extent)
{
    Set(_origin.x, _origin.y, static_cast<int>(_origin.x+_extent.cx), static_cast<int>(_origin.y+_extent.cy));
}

#ifndef __PALM_OS__
int Rect::Subtract(const Rect& _other, Rect _result[]) const
{
    // Determines the parts of this rect that do not lie within "other"
    //
    // Resulting rectangles are placed in the "result" array.
    //
    // Returns the resulting number of rectangles which will be in the
    // range "0 .. 4" inclusive
    //
    // Case of non-intersection, result is just this rectangle
    if(!Touches(_other)) 
    {
        _result[0] = *this;
        return 1;
    }
    // Check for up to four sub-rectangles produced
    else 
    {
        int i = 0;

        // Top piece of this rect
        //
        if(_other.top > top) 
        {                
            _result[i].left   = left;
            _result[i].top    = top;
            _result[i].right  = right;
            _result[i].bottom = _other.top;
            
            ++i;
        }

        // Bottom piece of this rect
        if(_other.bottom < bottom) 
        {
            _result[i].left   = left;
            _result[i].top    = _other.bottom;
            _result[i].right  = right;
            _result[i].bottom = bottom;
            
            ++i;
        }

        // Left piece of this rect
        if(_other.left > left)
        {
            _result[i].left   = left;
            _result[i].top    = Max(top, _other.top);
            _result[i].right  = _other.left;
            _result[i].bottom = Min(bottom, _other.bottom);

            ++i;
        }

        // Right piece of this rect
        if(_other.right < right) 
        {
            _result[i].left   = _other.right;
            _result[i].top    = Max(top, _other.top);
            _result[i].right  = right;
            _result[i].bottom = Min(bottom, _other.bottom);

            ++i;
        }

        return i;
    }
}
#endif
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__
