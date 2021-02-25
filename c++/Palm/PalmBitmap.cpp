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

#ifndef __PALM_BITMAP_INC__
#   include <PalmBitmap.inc>
#endif

#ifdef __PALM_OS__

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class PalmBitmap
// ----- ----------
PalmBitmap::PalmBitmap(BitmapType* _bitmap)
          : Bitmap(_bitmap)
{
}

PalmBitmap::~PalmBitmap()
{
}
////////////////////////////////////////////////////////////////////////////////////////
// class XPalmBitmap
// ----- -----------
void PalmBitmap::XPalmBitmap::LoadErrorDescriptions()
{
    // base class
    PalmError::LoadErrorDescriptions();
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__

