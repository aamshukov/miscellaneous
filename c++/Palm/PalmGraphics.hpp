////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PALM_GRAPHICS_H__
#define __PALM_GRAPHICS_H__

#ifdef __PALM_OS__

#pragma once

__BEGIN_NAMESPACE__

/** 
 * @class PalmGraphics
 * @brief Wraps Palm OS graphics routine
 */

////////////////////////////////////////////////////////////////////////////////////////
// class PalmGraphics
// ----- ------------
class __DECLSPEC__ PalmGraphics
{
    public:

    /** 
     * @class DrawState
     * @brief Simplifies using of 'draw state' metaphor
     */
    class DrawState
    {
        private:
         WinDrawOperation   Operation;
        public:

        /** 
         *  Constructor, pushes a draw state
         */
                            DrawState(WinDrawOperation = winPaint);

        /** 
         *  Destructor, pops up a draw state
         */
                           ~DrawState();

        /** 
         *  Accessor, returns the current draw state
         */
         WinDrawOperation   GetOperation()  const;
    };

    /** 
     * @class ClipState
     * @brief Simplifies work with a clip area metaphor
     */
    class ClipState
    {
        private:
         Rect   ClipArea;
        public:
        /** 
         *  Constructor
         */
                ClipState();

        /** 
         *  Destructor
         */
               ~ClipState();

        /** 
         *  Accessor, returns the current clip area
         */
         const Rect& GetClipArea()   const;
    };

    public:
    /** 
     *  Default constructor
     */
                        PalmGraphics();

    /** 
     *  Destructor
     */
                       ~PalmGraphics();

    /** 
     * @brief Pixel functions
     */
     static IndexedColorType
                        GetPixel(Coord, Coord);
     static IndexedColorType
                        GetPixel(Point&);

     static void        PaintPixel(Coord, Coord);
     static void        PaintPixel(const Point&);

     static void        DrawPixel(Coord, Coord);
     static void        DrawPixel(const Point&);

     static void        ErasePixel(Coord, Coord);
     static void        ErasePixel(const Point&);

     static void        InvertPixel(Coord, Coord);
     static void        InvertPixel(const Point&);

     static void        PaintPixels(uint16, Point []);

    /** 
     * @brief Line functions
     */
     static void        PaintLines(uint16, WinLineType []);

     static void        PaintLine(Coord, Coord, Coord, Coord);
     static void        PaintLine(const Point&, const Point&);

     static void        DrawLine(Coord, Coord, Coord, Coord);
     static void        DrawLine(const Point&, const Point&);

     static void        DrawGrayLine(Coord, Coord, Coord, Coord);
     static void        DrawGrayLine(const Point&, const Point&);

     static void        EraseLine(Coord, Coord, Coord, Coord);
     static void        EraseLine(const Point&, const Point&);

     static void        InvertLine(Coord, Coord, Coord, Coord);
     static void        InvertLine(const Point&, const Point&);

     static void        FillLine(Coord, Coord, Coord, Coord);
     static void        FillLine(const Point&, const Point&);

    /** 
     * @brief Rectangle functions
     */
     static void        PaintRectangle(const Rect&, uint16);
     static void        DrawRectangle(const Rect&, uint16);
     static void        EraseRectangle(const Rect&, uint16);
     static void        InvertRectangle(const Rect&, uint16);
     static void        FillRectangle(const Rect&, uint16);

     static void        PaintRectangleFrame(FrameType, const Rect&);
     static void        DrawRectangleFrame(FrameType, const Rect&);
     static void        DrawGrayRectangleFrame(FrameType, const Rect&);
     static void        EraseRectangleFrame(FrameType, const Rect&);
     static void        InvertRectangleFrame(FrameType, const Rect&);
     static void        GetFramesRectangle(FrameType, const Rect&, Rect&);

    /** 
     * @brief Bitmap functions
     */
     static void        DrawBitmap(const PalmBitmap&, Coord, Coord);
     static void        DrawBitmap(const PalmBitmap&, const Point&);

     static void        PaintBitmap(const PalmBitmap&, Coord, Coord);
     static void        PaintBitmap(const PalmBitmap&, const Point&);

    /** 
     * @brief Character functions
     */
     static void        DrawChar(wchar, Coord, Coord);
     static void        DrawChar(wchar, const Point&);

     static void        DrawChars(const char*, int16, Coord, Coord);
     static void        DrawChars(const char*, int16, const Point&);

     static void        PaintChar(wchar, Coord, Coord);
     static void        PaintChar(wchar, const Point&);

     static void        PaintChars(const char*, int16, Coord, Coord);
     static void        PaintChars(const char*, int16, const Point&);

     static void        DrawInvertedChars(const char*, int16, Coord, Coord);
     static void        DrawInvertedChars(const char*, int16, const Point&);

     static void        DrawTruncChars(const char*, int16, Coord, Coord, Coord);
     static void        DrawTruncChars(const char*, int16, const Point&, Coord);

     static void        EraseChars(const char*, int16, Coord, Coord);
     static void        EraseChars(const char*, int16, const Point&);

     static void        InvertChars(const char*, int16, Coord, Coord);
     static void        InvertChars(const char*, int16, const Point&);

     static UnderlineModeType
                        SetUnderlineMode(UnderlineModeType = noUnderline);

    /** 
     * @brief Pattern and Color functions
     */
     static WinDrawOperation
                        SetDrawMode(WinDrawOperation = winPaint);

     static IndexedColorType
                        SetForeColor(IndexedColorType);
     static IndexedColorType
                        SetBackColor(IndexedColorType);
     static IndexedColorType
                        SetTextColor(IndexedColorType);

     static void        GetPattern(CustomPatternType&);
     static void        SetPattern(const CustomPatternType&);

     static PatternType WinGetPatternType();
     static void        SetPatternType(PatternType);

     static Err         Palette(uint8, int16, uint16, RGBColorType&);

     static IndexedColorType
                        RGBToIndex(const RGBColorType&);
     static void        IndexToRGB(IndexedColorType, RGBColorType&);

#if (__PALM_OS__ >= 0x0400)
     static Err         GetPixelRGB(Coord, Coord, RGBColorType&);
     static Err         GetPixelRGB(const Point&, RGBColorType&);

     static void        SetForeColorRGB(const RGBColorType&, RGBColorType&);
     static void        SetBackColorRGB(const RGBColorType&, RGBColorType&);
     static void        SetTextColorRGB(const RGBColorType&, RGBColorType&);
#endif
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__
#endif // __PALM_GRAPHICS_H__
