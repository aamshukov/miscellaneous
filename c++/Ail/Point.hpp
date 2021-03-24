////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __POINT_H__
#define __POINT_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class Point
// ----- -----
#if defined(__MS_WINDOWS__)
class __DECLSPEC__ Point : public tagPOINT
#elif defined(__PALM_OS__)
class __DECLSPEC__ Point : public PointType
#else
// error: unknown platform!
#endif
{
    public:
     // ctor/dtor
            Point();
            Point(const Point&);
            Point(int, int);
#ifdef __MS_WINDOWS__
            Point(const POINT&);
            Point(const SIZE&);
            Point(uint);
#endif

#ifdef __PALM_OS__
            Point(const PointType&);
#endif

     // operators
#ifdef __MS_WINDOWS__
            operator const POINT* ()        const;
            operator POINT* ();
#endif

#ifdef __PALM_OS__
            operator const PointType* ()    const;
            operator PointType* ();
#endif

     bool   operator == (const Point&)      const;
     bool   operator != (const Point&)      const;

     Point  operator + (const Size&)        const;
     Size   operator - (const Point&)       const;
     Point  operator - (const Size&)        const;
     Point  operator - ()                   const;
     Point& operator += (const Point&);
     Point& operator += (const Size&);
     Point& operator -= (const Point&);
     Point& operator -= (const Size&);

     // protocol
     Point& Offset(int, int);
     Point& Offset(const Point&);
     Point& Offset(const Size&);
     Point  OffsetBy(int, int)              const;
     Point  OffsetBy(const Size&)           const;

#ifdef __MS_WINDOWS__
     int    Magnitude()                     const;
#endif
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __POINT_H__
