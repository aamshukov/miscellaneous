////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PALM_BITMAP_H__
#define __PALM_BITMAP_H__

#ifdef __PALM_OS__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class PalmBitmap
// ----- ----------
class __DECLSPEC__ PalmBitmap
{
    private:
     BitmapType*        Bitmap;
    public:
     // ctor/dtor
                        PalmBitmap(BitmapType* = null);
     virtual           ~PalmBitmap();

     // access
     BitmapType*        GetBitmap()                     const;

     // operators
                        operator const BitmapType* ()   const;
                        operator BitmapType* ();

     // api
     bool               Create(Coord, Coord, uint8, ColorTableType&, uint16&);
     bool               Create(const Size&, uint8, ColorTableType&, uint16&);
     Err                Destroy();

     Err                Compress(BitmapCompressionType);

     uint16             GetSize();

     void*              GetBits();
     uint16             GetBitsSize();

     ColorTableType*    GetColortable();
     uint16             GetColortableSize();

#if (__PALM_OS__ >= 0x0400)
     void               GetSizes(uint32&, uint32&);

     void               GetDimensions(Coord&, Coord&, uint16&);
     void               GetDimensions(Size&, uint16&);

     uint8              GetBitDepth();

     BitmapType*        GetNextBitmap();
     BitmapType*        GetNextBitmap(BitmapType&);
#endif

    public:
    
    class __DECLSPEC__ XPalmBitmap : public PalmError
    {
        public:

        enum EErrors
        {
            // appErrorClass+'pbmp'
        };

        protected:
         virtual void LoadErrorDescriptions();
    };

    friend class XPalmBitmap;
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__
#endif // __PALM_BITMAP_H__
