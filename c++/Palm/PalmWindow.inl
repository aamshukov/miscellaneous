////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PALM_WINDOW_INL__
#define __PALM_WINDOW_INL__

#ifdef __PALM_OS__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class PalmWindow
// ----- ----------
__INLINE__ PalmWindow::operator const WindowType* () const
{
    return const_cast<const WindowType*>(Handle);
}

__INLINE__ PalmWindow::operator WindowType* ()
{
    return Handle;
}

__INLINE__ bool PalmWindow::IsValid() const
{
    return Handle != null;
}

__INLINE__ bool PalmWindow::IsModal() const
{
    palmxassert(Handle != null, Error::eUninitialized, PalmWindow::XPalmWindow);
    return ::WinModal(Handle);
}

__INLINE__ WinHandle PalmWindow::GetHandle() const
{
    return Handle;
}

__INLINE__ bool PalmWindow::ValidateHandle(WinHandle _handle)
{
    return ::WinValidateHandle(_handle);
}

__INLINE__ void PalmWindow::CreateWindow(const Rect& _r, FrameType _frame, bool _modal, bool _focusable, uint16& _error)
{
    Handle =::WinCreateWindow(_r, _frame, _modal, _focusable, &_error);
}

__INLINE__ void PalmWindow::CreateOffscreenWindow(Coord _w, Coord _h, WindowFormatType _format, uint16& _error)
{
    Handle = ::WinCreateOffscreenWindow(_w, _h, _format, &_error);
}

__INLINE__ void PalmWindow::CreateOffscreenWindow(const Size& _sz, WindowFormatType _format, uint16& _error)
{
    Handle = ::WinCreateOffscreenWindow(_sz.cx, _sz.cy, _format, &_error);
}

__INLINE__ void PalmWindow::CreateBitmapWindow(const PalmBitmap& _bmp, uint16& _error)
{
    Handle = ::WinCreateBitmapWindow((BitmapType*)(&_bmp), &_error);
}

__INLINE__ void PalmWindow::DestroyWindow(bool _erase)
{
    palmxassert(Handle != 0, Error::eUninitialized, PalmWindow::XPalmWindow);
  ::WinDeleteWindow(Handle, _erase), Handle = 0;
}

__INLINE__ void PalmWindow::InitializeWindow()
{
    palmxassert(Handle != 0, Error::eUninitialized, PalmWindow::XPalmWindow);
  ::WinInitializeWindow(Handle);
}

__INLINE__ void PalmWindow::AddWindow()
{
    palmxassert(Handle != 0, Error::eUninitialized, PalmWindow::XPalmWindow);
  ::WinAddWindow(Handle);
}

__INLINE__ void PalmWindow::RemoveWindow()
{
    palmxassert(Handle != 0, Error::eUninitialized, PalmWindow::XPalmWindow);
  ::WinRemoveWindow(Handle);
}

__INLINE__ void PalmWindow::MoveWindowAddr(WindowType* _new_location)
{
    palmxassert(Handle != 0, Error::eUninitialized, PalmWindow::XPalmWindow);
    palmxassert(_new_location != null, Error::eInvalidArg, PalmWindow::XPalmWindow);
  ::WinMoveWindowAddr(Handle, _new_location);
}

__INLINE__ WinHandle PalmWindow::GetActiveWindow()
{
    return ::WinGetActiveWindow();
}

__INLINE__ void PalmWindow::SetActiveWindow()
{
    palmxassert(Handle != 0, Error::eUninitialized, PalmWindow::XPalmWindow);
  ::WinSetActiveWindow(Handle);
}

__INLINE__ WinHandle PalmWindow::GetDrawWindow()
{
    return ::WinGetDrawWindow();
}

__INLINE__ WinHandle PalmWindow::SetDrawWindow()
{
    palmxassert(Handle != 0, Error::eUninitialized, PalmWindow::XPalmWindow);
    return ::WinSetDrawWindow(Handle);
}

__INLINE__ void PalmWindow::EnableWindow()
{
    palmxassert(Handle != 0, Error::eUninitialized, PalmWindow::XPalmWindow);
  ::WinEnableWindow(Handle);
}

__INLINE__ void PalmWindow::DisableWindow()
{
    palmxassert(Handle != 0, Error::eUninitialized, PalmWindow::XPalmWindow);
  ::WinDisableWindow(Handle);
}

__INLINE__ WinHandle PalmWindow::GetDisplayWindow()
{
    return ::WinGetDisplayWindow();
}

__INLINE__ WinHandle PalmWindow::GetFirstWindow()
{
    return ::WinGetFirstWindow();
}

__INLINE__ void PalmWindow::GetWindowFrameRect(Rect& _r)
{
    palmxassert(Handle != 0, Error::eUninitialized, PalmWindow::XPalmWindow);
  ::WinGetWindowFrameRect(Handle, &_r);
}

__INLINE__ void PalmWindow::EraseWindow()
{
  ::WinEraseWindow();
}

__INLINE__ void PalmWindow::DrawWindowFrame()
{
  ::WinDrawWindowFrame();
}

__INLINE__ BitmapType* PalmWindow::GetBitmap()
{
    palmxassert(Handle != 0, Error::eUninitialized, PalmWindow::XPalmWindow);
    return ::WinGetBitmap(Handle);
}

__INLINE__ WinHandle PalmWindow::SaveBits(const Rect& _r, uint16& _error)
{
    return ::WinSaveBits(_r, &_error);
}

__INLINE__ void PalmWindow::RestoreBits(Coord _x, Coord _y)
{
    palmxassert(Handle != 0, Error::eUninitialized, PalmWindow::XPalmWindow);
  ::WinRestoreBits(Handle, _x, _y);
}

__INLINE__ void PalmWindow::RestoreBits(const Point& _pt)
{
    palmxassert(Handle != 0, Error::eUninitialized, PalmWindow::XPalmWindow);
  ::WinRestoreBits(Handle, _pt.x, _pt.y);
}

#if (__PALM_OS__ >= 0x0400)
__INLINE__ void PalmWindow::GetDrawWindowBounds(Rect& _r)
{
  ::WinGetDrawWindowBounds(&_r);
}

__INLINE__ void PalmWindow::GetBounds(Rect& _r)
{
    palmxassert(Handle != 0, Error::eUninitialized, PalmWindow::XPalmWindow);
  ::WinGetBounds(Handle, &_r);
}

__INLINE__ void PalmWindow::SetBounds(const Rect& _r)
{
    palmxassert(Handle != 0, Error::eUninitialized, PalmWindow::XPalmWindow);
  ::WinSetBounds(Handle, &_r);
}
#else
__INLINE__ void PalmWindow::GetWindowBounds(Rect& _r)
{
  ::WinGetWindowBounds(&_r);
}

__INLINE__ void PalmWindow::SetWindowBounds(const Rect& _r)
{
    palmxassert(Handle != 0, Error::eUninitialized, PalmWindow::XPalmWindow);
  ::WinSetWindowBounds(Handle, &_r);
}
#endif

__INLINE__ void PalmWindow::CopyRectangle(WinHandle _hdst, const Rect& _src_r, Coord _dst_x, Coord _dst_y, WinDrawOperation _op)
{
    palmxassert(Handle != 0, Error::eUninitialized, PalmWindow::XPalmWindow);
  ::WinCopyRectangle(Handle, _hdst, _src_r, _dst_x, _dst_y, _op);
}

__INLINE__ void PalmWindow::CopyRectangle(WinHandle _hdst, const Rect& _src_r, const Point& _dst_pt, WinDrawOperation _op)
{
    palmxassert(Handle != 0, Error::eUninitialized, PalmWindow::XPalmWindow);
  ::WinCopyRectangle(Handle, _hdst, _src_r, _dst_pt.x, _dst_pt.y, _op);
}

__INLINE__ void PalmWindow::GetDisplayExtent(Coord& _w, Coord& _h)
{
  ::WinGetDisplayExtent(&_w, &_h);
}

__INLINE__ void PalmWindow::GetDisplayExtent(Size& _sz)
{
  ::WinGetDisplayExtent(&_sz.cx, &_sz.cy);
}

__INLINE__ void PalmWindow::GetWindowExtent(Coord& _w, Coord& _h)
{
  ::WinGetWindowExtent(&_w, &_h);
}

__INLINE__ void PalmWindow::GetWindowExtent(Size& _sz)
{
  ::WinGetWindowExtent(&_sz.cx, &_sz.cy);
}

__INLINE__ void PalmWindow::DisplayToWindowPt(Coord& _x, Coord& _y)
{
  ::WinDisplayToWindowPt(&_x, &_y);
}

__INLINE__ void PalmWindow::DisplayToWindowPt(Point& _pt)
{
  ::WinDisplayToWindowPt(&_pt.x, &_pt.y);
}

__INLINE__ void PalmWindow::WindowToDisplayPt(Coord& _x, Coord& _y)
{
  ::WinWindowToDisplayPt(&_x, &_y);
}

__INLINE__ void PalmWindow::WindowToDisplayPt(Point& _pt)
{
  ::WinWindowToDisplayPt(&_pt.x, &_pt.y);
}

__INLINE__ void PalmWindow::GetClip(Rect& _r)
{
  ::WinGetClip(&_r);
}

__INLINE__ void PalmWindow::SetClip(const Rect& _r)
{
  ::WinSetClip(&_r);
}

__INLINE__ void PalmWindow::ResetClip()
{
  ::WinResetClip();
}

__INLINE__ void PalmWindow::ClipRectangle(Rect& _r)
{
  ::WinClipRectangle(_r);
}

__INLINE__ void PalmWindow::ScrollRectangle(const Rect& _r, WinDirectionType _dir, Coord _distance, Rect& _vr)
{
  ::WinScrollRectangle(_r, _dir, _distance, _vr);
}

__INLINE__ void PalmWindow::ScreenInit()
{
  ::WinScreenInit();
}

__INLINE__ Err PalmWindow::ScreenMode(WinScreenModeOperation _op, uint32& _w, uint32& _h, uint32& _depth, bool& _is_color)
{
    return ::WinScreenMode(_op, &_w, &_h, &_depth, reinterpret_cast<Boolean*>(&_is_color));
}

__INLINE__ uint8* PalmWindow::ScreenLock(WinLockInitType _type)
{
    return ::WinScreenLock(_type);
}

__INLINE__ void PalmWindow::ScreenUnlock()
{
  ::WinScreenUnlock();
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__
#endif // __PALM_WINDOW_INL__
