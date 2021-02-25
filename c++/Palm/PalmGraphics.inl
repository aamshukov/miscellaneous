////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  Copyright © 1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PALM_GRAPHICS_INL__
#define __PALM_GRAPHICS_INL__

#ifdef __PALM_OS__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class DrawState
// ----- ---------
__INLINE__ WinDrawOperation PalmGraphics::DrawState::GetOperation() const
{
    return Operation;
}
////////////////////////////////////////////////////////////////////////////////////////
// class ClipState
// ----- ---------
__INLINE__ const Rect& PalmGraphics::ClipState::GetClipArea() const
{
    return ClipArea;
}
////////////////////////////////////////////////////////////////////////////////////////
// class PalmGraphics
// ----- ------------
__INLINE__ IndexedColorType PalmGraphics::GetPixel(Coord _x, Coord _y)
{
    return ::WinGetPixel(_x, _y);
}

__INLINE__ IndexedColorType PalmGraphics::GetPixel(Point& _pt)
{
    return ::WinGetPixel(_pt.x, _pt.y);
}

__INLINE__ void PalmGraphics::PaintPixel(Coord _x, Coord _y)
{
  ::WinPaintPixel(_x, _y);
}

__INLINE__ void PalmGraphics::PaintPixel(const Point& _pt)
{
  ::WinPaintPixel(_pt.x, _pt.y);
}

__INLINE__ void PalmGraphics::DrawPixel(Coord _x, Coord _y)
{
  ::WinDrawPixel(_x, _y);
}

__INLINE__ void PalmGraphics::DrawPixel(const Point& _pt)
{
  ::WinDrawPixel(_pt.x, _pt.y);
}

__INLINE__ void PalmGraphics::ErasePixel(Coord _x, Coord _y)
{
  ::WinErasePixel(_x, _y);
}

__INLINE__ void PalmGraphics::ErasePixel(const Point& _pt)
{
  ::WinErasePixel(_pt.x, _pt.y);
}

__INLINE__ void PalmGraphics::InvertPixel(Coord _x, Coord _y)
{
  ::WinInvertPixel(_x, _y);
}

__INLINE__ void PalmGraphics::InvertPixel(const Point& _pt)
{
  ::WinInvertPixel(_pt.x, _pt.y);
}

__INLINE__ void PalmGraphics::PaintPixels(uint16 _count, Point _pts[])
{
  ::WinPaintPixels(_count, _pts);
}

__INLINE__ void PalmGraphics::PaintLines(uint16 _count, WinLineType _lines[])
{
  ::WinPaintLines(_count, _lines);
}

__INLINE__ void PalmGraphics::PaintLine(Coord _x1, Coord _y1, Coord _x2, Coord _y2)
{
  ::WinPaintLine(_x1, _y1, _x2, _y2);
}

__INLINE__ void PalmGraphics::PaintLine(const Point& _start, const Point& _end)
{
  ::WinPaintLine(_start.x, _start.y, _end.x, _end.y);
}

__INLINE__ void PalmGraphics::DrawLine(Coord _x1, Coord _y1, Coord _x2, Coord _y2)
{
  ::WinDrawLine(_x1, _y1, _x2, _y2);
}

__INLINE__ void PalmGraphics::DrawLine(const Point& _start, const Point& _end)
{
  ::WinDrawLine(_start.x, _start.y, _end.x, _end.y);
}

__INLINE__ void PalmGraphics::DrawGrayLine(Coord _x1, Coord _y1, Coord _x2, Coord _y2)
{
  ::WinDrawLine(_x1, _y1, _x2, _y2);
}

__INLINE__ void PalmGraphics::DrawGrayLine(const Point& _start, const Point& _end)
{
  ::WinDrawLine(_start.x, _start.y, _end.x, _end.y);
}

__INLINE__ void PalmGraphics::EraseLine(Coord _x1, Coord _y1, Coord _x2, Coord _y2)
{
  ::WinEraseLine(_x1, _y1, _x2, _y2);
}

__INLINE__ void PalmGraphics::EraseLine(const Point& _start, const Point& _end)
{
  ::WinEraseLine(_start.x, _start.y, _end.x, _end.y);
}

__INLINE__ void PalmGraphics::InvertLine(Coord _x1, Coord _y1, Coord _x2, Coord _y2)
{
  ::WinInvertLine(_x1, _y1, _x2, _y2);
}

__INLINE__ void PalmGraphics::InvertLine(const Point& _start, const Point& _end)
{
  ::WinInvertLine(_start.x, _start.y, _end.x, _end.y);
}

__INLINE__ void PalmGraphics::FillLine(Coord _x1, Coord _y1, Coord _x2, Coord _y2)
{
  ::WinFillLine(_x1, _y1, _x2, _y2);
}

__INLINE__ void PalmGraphics::FillLine(const Point& _start, const Point& _end)
{
  ::WinFillLine(_start.x, _start.y, _end.x, _end.y);
}

__INLINE__ void PalmGraphics::PaintRectangle(const Rect& _r, uint16 _corner)
{
  ::WinPaintRectangle(_r, _corner);
}

__INLINE__ void PalmGraphics::DrawRectangle(const Rect& _r, uint16 _corner)
{
  ::WinDrawRectangle(_r, _corner);
}

__INLINE__ void PalmGraphics::EraseRectangle(const Rect& _r, uint16 _corner)
{
  ::WinEraseRectangle(_r, _corner);
}

__INLINE__ void PalmGraphics::InvertRectangle(const Rect& _r, uint16 _corner)
{
  ::WinInvertRectangle(_r, _corner);
}

__INLINE__ void PalmGraphics::FillRectangle(const Rect& _r, uint16 _corner)
{
  ::WinFillRectangle(_r, _corner);
}

__INLINE__ void PalmGraphics::PaintRectangleFrame(FrameType _type, const Rect& _r)
{
  ::WinPaintRectangleFrame(_type, _r);
}

__INLINE__ void PalmGraphics::DrawRectangleFrame(FrameType _type, const Rect& _r)
{
  ::WinDrawRectangleFrame(_type, _r);
}

__INLINE__ void PalmGraphics::DrawGrayRectangleFrame(FrameType _type, const Rect& _r)
{
  ::WinDrawGrayRectangleFrame(_type, _r);
}

__INLINE__ void PalmGraphics::EraseRectangleFrame(FrameType _type, const Rect& _r)
{
  ::WinEraseRectangleFrame(_type, _r);
}

__INLINE__ void PalmGraphics::InvertRectangleFrame(FrameType _type, const Rect& _r)
{
  ::WinInvertRectangleFrame(_type, _r);
}

__INLINE__ void PalmGraphics::GetFramesRectangle(FrameType _type, const Rect& _r_in, Rect& _r_out)
{
  ::WinGetFramesRectangle(_type, _r_in, _r_out);
}

__INLINE__ void PalmGraphics::DrawBitmap(const PalmBitmap& _bmp, Coord _x, Coord _y)
{
  ::WinDrawBitmap((BitmapType*)(&_bmp), _x, _y);
}

__INLINE__ void PalmGraphics::DrawBitmap(const PalmBitmap& _bmp, const Point& _pt)
{
  ::WinDrawBitmap((BitmapType*)(&_bmp), _pt.x, _pt.y);
}

__INLINE__ void PalmGraphics::PaintBitmap(const PalmBitmap& _bmp, Coord _x, Coord _y)
{
  ::WinPaintBitmap((BitmapType*)(&_bmp), _x, _y);
}

__INLINE__ void PalmGraphics::PaintBitmap(const PalmBitmap& _bmp, const Point& _pt)
{
  ::WinPaintBitmap((BitmapType*)(&_bmp), _pt.x, _pt.y);
}

__INLINE__ void PalmGraphics::DrawChar(wchar _ch, Coord _x, Coord _y)
{
  ::WinDrawChar(_ch, _x, _y);
}

__INLINE__ void PalmGraphics::DrawChar(wchar _ch, const Point& _pt)
{
  ::WinDrawChar(_ch, _pt.x, _pt.y);
}

__INLINE__ void PalmGraphics::DrawChars(const char* _chs, int16 _count, Coord _x, Coord _y)
{
  ::WinDrawChars(_chs, _count, _x, _y);
}

__INLINE__ void PalmGraphics::DrawChars(const char* _chs, int16 _count, const Point& _pt)
{
  ::WinDrawChars(_chs, _count, _pt.x, _pt.y);
}

__INLINE__ void PalmGraphics::PaintChar(wchar _ch, Coord _x, Coord _y)
{
  ::WinPaintChar(_ch, _x, _y);
}

__INLINE__ void PalmGraphics::PaintChar(wchar _ch, const Point& _pt)
{
  ::WinPaintChar(_ch, _pt.x, _pt.y);
}

__INLINE__ void PalmGraphics::PaintChars(const char* _chs, int16 _count, Coord _x, Coord _y)
{
  ::WinPaintChars(_chs, _count, _x, _y);
}

__INLINE__ void PalmGraphics::PaintChars(const char* _chs, int16 _count, const Point& _pt)
{
  ::WinPaintChars(_chs, _count, _pt.x, _pt.y);
}

__INLINE__ void PalmGraphics::DrawInvertedChars(const char* _chs, int16 _count, Coord _x, Coord _y)
{
  ::WinDrawInvertedChars(_chs, _count, _x, _y);
}

__INLINE__ void PalmGraphics::DrawInvertedChars(const char* _chs, int16 _count, const Point& _pt)
{
  ::WinDrawInvertedChars(_chs, _count, _pt.x, _pt.y);
}

__INLINE__ void PalmGraphics::DrawTruncChars(const char* _chs, int16 _count, Coord _x, Coord _y, Coord _max_width)
{
  ::WinDrawTruncChars(_chs, _count, _x, _y, _max_width);
}

__INLINE__ void PalmGraphics::DrawTruncChars(const char* _chs, int16 _count, const Point& _pt, Coord _max_width)
{
  ::WinDrawTruncChars(_chs, _count, _pt.x, _pt.y, _max_width);
}

__INLINE__ void PalmGraphics::EraseChars(const char* _chs, int16 _count, Coord _x, Coord _y)
{
  ::WinEraseChars(_chs, _count, _x, _y);
}

__INLINE__ void PalmGraphics::EraseChars(const char* _chs, int16 _count, const Point& _pt)
{
  ::WinEraseChars(_chs, _count, _pt.x, _pt.y);
}

__INLINE__ void PalmGraphics::InvertChars(const char* _chs, int16 _count, Coord _x, Coord _y)
{
  ::WinInvertChars(_chs, _count, _x, _y);
}

__INLINE__ void PalmGraphics::InvertChars(const char* _chs, int16 _count, const Point& _pt)
{
  ::WinInvertChars(_chs, _count, _pt.x, _pt.y);
}

__INLINE__ UnderlineModeType PalmGraphics::SetUnderlineMode(UnderlineModeType _mode)
{
    return ::WinSetUnderlineMode(_mode);
}

__INLINE__ WinDrawOperation PalmGraphics::SetDrawMode(WinDrawOperation _op)
{
    return ::WinSetDrawMode(_op);
}

__INLINE__ IndexedColorType PalmGraphics::SetForeColor(IndexedColorType _color)
{
    return ::WinSetForeColor(_color);
}

__INLINE__ IndexedColorType PalmGraphics::SetBackColor(IndexedColorType _color)
{
    return ::WinSetBackColor(_color);
}

__INLINE__ IndexedColorType PalmGraphics::SetTextColor(IndexedColorType _color)
{
    return ::WinSetTextColor(_color);
}

__INLINE__ void PalmGraphics::GetPattern(CustomPatternType& _pattern)
{
  ::WinGetPattern(&_pattern);
}

__INLINE__ void PalmGraphics::SetPattern(const CustomPatternType& _pattern)
{
  ::WinSetPattern(&_pattern);
}

__INLINE__ PatternType PalmGraphics::WinGetPatternType()
{
    return ::WinGetPatternType();
}

__INLINE__ void PalmGraphics::SetPatternType(PatternType _type)
{
  ::WinSetPatternType(_type);
}

__INLINE__ Err PalmGraphics::Palette(uint8 _op, int16 _start_index, uint16 _count, RGBColorType& _color_table)
{
    return ::WinPalette(_op, _start_index, _count, &_color_table);
}

__INLINE__ IndexedColorType PalmGraphics::RGBToIndex(const RGBColorType& _rgb)
{
    return ::WinRGBToIndex(&_rgb);
}

__INLINE__ void PalmGraphics::IndexToRGB(IndexedColorType _index, RGBColorType& _rgb)
{
  ::WinIndexToRGB(_index, &_rgb);
}

#if (__PALM_OS__ >= 0x0400)
__INLINE__ Err PalmGraphics::GetPixelRGB(Coord _x, Coord _y, RGBColorType& _rgb)
{
    return ::WinGetPixelRGB(_x, _y, &_rgb);
}

__INLINE__ Err PalmGraphics::GetPixelRGB(const Point& _pt, RGBColorType& _rgb)
{
    return ::WinGetPixelRGB(_pt.x, _pt.y, &_rgb);
}

__INLINE__ void PalmGraphics::SetForeColorRGB(const RGBColorType& _new_rgb, RGBColorType& _old_rgb)
{
  ::WinSetForeColorRGB(&_new_rgb, &_old_rgb);
}

__INLINE__ void PalmGraphics::SetBackColorRGB(const RGBColorType& _new_rgb, RGBColorType& _old_rgb)
{
  ::WinSetBackColorRGB(&_new_rgb, &_old_rgb);
}

__INLINE__ void PalmGraphics::SetTextColorRGB(const RGBColorType& _new_rgb, RGBColorType& _old_rgb)
{
  ::WinSetTextColorRGB(&_new_rgb, &_old_rgb);
}
#endif
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__
#endif // __PALM_GRAPHICS_INL__
