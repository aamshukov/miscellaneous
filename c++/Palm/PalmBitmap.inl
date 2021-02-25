////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PALM_BITMAP_INL__
#define __PALM_BITMAP_INL__

#ifdef __PALM_OS__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class PalmBitmap
// ----- ----------
__INLINE__ BitmapType* PalmBitmap::GetBitmap() const
{
    return Bitmap;
}

__INLINE__ PalmBitmap::operator const BitmapType* () const
{
    return const_cast<const BitmapType*>(Bitmap);
}

__INLINE__ PalmBitmap::operator BitmapType* ()
{
    return Bitmap;
}

__INLINE__ bool PalmBitmap::Create(Coord _w, Coord _h, uint8 _depth, ColorTableType& _color_table, uint16& _error)
{
    Bitmap = ::BmpCreate(_w, _h, _depth, &_color_table, &_error);
    return Bitmap != null;
}

__INLINE__ bool PalmBitmap::Create(const Size& _sz, uint8 _depth, ColorTableType& _color_table, uint16& _error)
{
    Bitmap = ::BmpCreate(_sz.cx, _sz.cy, _depth, &_color_table, &_error);
    return Bitmap != null;
}

__INLINE__ Err PalmBitmap::Destroy()
{
    palmxassert(Bitmap != null, Error::eUninitialized, PalmBitmap::XPalmBitmap)
    Err err = ::BmpDelete(Bitmap), Bitmap = null;
    return err;
}

__INLINE__ Err PalmBitmap::Compress(BitmapCompressionType _type)
{
    palmxassert(Bitmap != null, Error::eUninitialized, PalmBitmap::XPalmBitmap)
    return ::BmpCompress(Bitmap, _type);
}

__INLINE__ uint16 PalmBitmap::GetSize()
{
    palmxassert(Bitmap != null, Error::eUninitialized, PalmBitmap::XPalmBitmap)
    return ::BmpSize(Bitmap);
}

__INLINE__ void* PalmBitmap::GetBits()
{
    palmxassert(Bitmap != null, Error::eUninitialized, PalmBitmap::XPalmBitmap)
    return ::BmpGetBits(Bitmap);
}

__INLINE__ uint16 PalmBitmap::GetBitsSize()
{
    palmxassert(Bitmap != null, Error::eUninitialized, PalmBitmap::XPalmBitmap)
    return ::BmpBitsSize(Bitmap);
}

__INLINE__ ColorTableType* PalmBitmap::GetColortable()
{
    palmxassert(Bitmap != null, Error::eUninitialized, PalmBitmap::XPalmBitmap)
    return ::BmpGetColortable(Bitmap);
}

__INLINE__ uint16 PalmBitmap::GetColortableSize()
{
    palmxassert(Bitmap != null, Error::eUninitialized, PalmBitmap::XPalmBitmap)
    return ::BmpColortableSize(Bitmap);
}

#if (__PALM_OS__ >= 0x0400)
__INLINE__ void PalmBitmap::GetSizes(uint32& _data_size, uint32& _header_size)
{
    palmxassert(Bitmap != null, Error::eUninitialized, PalmBitmap::XPalmBitmap)
  ::BmpGetSizes(Bitmap, &_data_size, &_header_size);
}

__INLINE__ void PalmBitmap::GetDimensions(Coord& _w, Coord& _h, uint16& _row_len)
{
    palmxassert(Bitmap != null, Error::eUninitialized, PalmBitmap::XPalmBitmap)
  ::BmpGetDimensions(Bitmap, &_w, &_h, &_row_len);
}

__INLINE__ void PalmBitmap::GetDimensions(Size& _sz, uint16& _row_len)
{
    palmxassert(Bitmap != null, Error::eUninitialized, PalmBitmap::XPalmBitmap)
  ::BmpGetDimensions(Bitmap, &_sz.cx, &_sz.cy, &_row_len);
}

__INLINE__ uint8 PalmBitmap::GetBitDepth()
{
    palmxassert(Bitmap != null, Error::eUninitialized, PalmBitmap::XPalmBitmap)
    return ::BmpGetBitDepth(Bitmap);
}

__INLINE__ BitmapType* PalmBitmap::GetNextBitmap()
{
    palmxassert(Bitmap != null, Error::eUninitialized, PalmBitmap::XPalmBitmap)
    return ::BmpGetNextBitmap(Bitmap);
}

__INLINE__ BitmapType* PalmBitmap::GetNextBitmap(BitmapType& _bmp)
{
    return ::BmpGetNextBitmap(&_bmp);
}
#endif
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__
#endif // __PALM_BITMAP_INL__
