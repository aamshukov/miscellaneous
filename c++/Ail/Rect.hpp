////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __AIL_RECT_H__
#define __AIL_RECT_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class Rect
// ----- ----
#if defined __MS_WINDOWS__
class __DECLSPEC__ Rect : public tagRECT
#elif defined(__PALM_OS__)
class __DECLSPEC__ Rect : public RectangleType
#else
// error: unknown platform!
#endif
{
    public:
     // ctor/dtor
                    Rect();
                    Rect(const Rect&);
#ifdef __MS_WINDOWS__
                    Rect(const RECT&);
#endif

#ifdef __PALM_OS__
                    Rect(const RectangleType&);
#endif

                    Rect(int, int, int, int);
                    Rect(int, int, uint, uint);
                    Rect(const Point&, const Point&);
                    Rect(const Point&, const Size&);

     // operator
     bool           operator == (const Rect&)               const;
     bool           operator != (const Rect&)               const;

     Rect           operator + (const Size&)                const;
     Rect           operator - (const Size&)                const;
     Rect           operator & (const Rect&)                const;
     Rect           operator | (const Rect&)                const;
     Rect&          operator += (const Size&);
     Rect&          operator -= (const Size&);
     Rect&          operator &= (const Rect&);
     Rect&          operator |= (const Rect&);

                    operator const Point* ()                const;
                    operator Point* ();

#ifdef __MS_WINDOWS__
                    operator const RECT* ()                 const;
                    operator RECT* ();
#endif

#ifdef __PALM_OS__
                    operator const RectangleType* ()        const;
                    operator RectangleType* ();
#endif

     // protocol
     void           SetNull();
     void           SetEmpty();

     void           Set(int, int, int, int);
     void           Set(int, int, uint, uint);

     bool           IsEmpty()                               const;
     bool           IsNull()                                const;

     bool           PtInRect(const Point&)                  const;
     bool           Contains(const Point&)                  const;
     bool           Contains(const Rect&)                   const;

     bool           Touches(const Rect&)                    const;

     Point          GetCenterPoint()                        const;

     Point          TopLeft()                               const;
     Point          TopRight()                              const;
     Point          BottomLeft()                            const;
     Point          BottomRight()                           const;

     int            Width()                                 const;
     int            Height()                                const;

     Size           GetSize()                               const;
     int            GetArea()                               const;

     Rect           OffsetBy(int, int)                      const;

     Rect&          Inflate(int, int);
     Rect&          Inflate(const Size&);
     Rect           InflatedBy(int, int)                    const;
     Rect           InflatedBy(const Size&)                 const;

     Rect           Normalized()                            const;
     Rect&          Normalize();

     Rect&          Offset(int, int);

#ifndef __PALM_OS__
     int            Subtract(const Rect&, Rect result[])    const;

     void           ToSquare();
     Rect           ToSquareBy();
#endif
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __AIL_RECT_H__
