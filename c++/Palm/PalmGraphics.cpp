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

#ifndef __PALM_GRAPHICS_INC__
#   include <PalmGraphics.inc>
#endif

#ifdef __PALM_OS__

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class DrawState
// ----- ---------
PalmGraphics::DrawState::DrawState(WinDrawOperation _operation)
            : Operation(_operation)
{
  ::WinPushDrawState();
}

PalmGraphics::DrawState::~DrawState()
{
  ::WinPopDrawState();
}
////////////////////////////////////////////////////////////////////////////////////////
// class ClipState
// ----- ---------
PalmGraphics::ClipState::ClipState()
{
    PalmWindow::GetClip(ClipArea);
}

PalmGraphics::ClipState::~ClipState()
{
    PalmWindow::SetClip(ClipArea);
}
////////////////////////////////////////////////////////////////////////////////////////
// class PalmGraphics
// ----- ------------
PalmGraphics::PalmGraphics()
{
}

PalmGraphics::~PalmGraphics()
{
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__

