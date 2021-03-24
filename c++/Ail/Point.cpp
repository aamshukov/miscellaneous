////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __AIL_H__
#   include <ail.hpp>
#endif

#ifndef __POINT_INC__
#   include <Point.inc>
#endif

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class Point
// ----- -----
Point::Point()
{
    x = 0;
    y = 0;
}

Point::Point(const Point& _pt)
{
    x = _pt.x;
    y = _pt.y;
}

Point::Point(int _x, int _y)
{
#ifdef __PALM_OS__
    x = static_cast<Coord>(_x);
    y = static_cast<Coord>(_y);
#else
    x = _x;
    y = _y;
#endif
}

#ifdef __MS_WINDOWS__
Point::Point(const POINT& _pt)
{
    x = _pt.x;
    y = _pt.y;
}

Point::Point(const SIZE& _sz)
{
    x = _sz.cx;
    y = _sz.cy;
}

Point::Point(uint _dw)
{
    x = MAKEPOINTS(_dw).x;
    y = MAKEPOINTS(_dw).y;
}
#endif

#ifdef __PALM_OS__
Point::Point(const PointType& _pt)
{
    x = _pt.x;
    y = _pt.y;
}
#endif
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__
