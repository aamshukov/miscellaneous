////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PALM_WINDOW_H__
#define __PALM_WINDOW_H__

#ifdef __PALM_OS__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class PalmWindow
// ----- ----------
class __DECLSPEC__ PalmWindow
{
    private:
     WinHandle          Handle;
    public:
     // ctor/dtor
                        PalmWindow(WinHandle = 0);
                       ~PalmWindow();
     
     // operators
                        operator const WindowType* ()   const;
                        operator WindowType* ();
     
     // access
     bool               IsValid()                       const;
     bool               IsModal()                       const;

     WinHandle          GetHandle()                     const;

     // api
     bool               ValidateHandle(WinHandle);

     void               CreateWindow(const Rect&, FrameType, bool, bool, uint16&);
     void               CreateOffscreenWindow(Coord, Coord, WindowFormatType, uint16&);
     void               CreateOffscreenWindow(const Size&, WindowFormatType, uint16&);
     void               CreateBitmapWindow(const PalmBitmap&, uint16&);
     void               DestroyWindow(bool = true);
                        
     void               InitializeWindow();

     void               AddWindow();
     void               RemoveWindow();

     void               MoveWindowAddr(WindowType*);

     static WinHandle   GetActiveWindow();
     void               SetActiveWindow();

     static WinHandle   GetDrawWindow();
     WinHandle          SetDrawWindow();

     void               EnableWindow();
     void               DisableWindow();

     static WinHandle   GetDisplayWindow();
     static WinHandle   GetFirstWindow();

     void               GetWindowFrameRect(Rect&);

     static void        EraseWindow();
     static void        DrawWindowFrame();

     BitmapType*        GetBitmap();

     static WinHandle   SaveBits(const Rect&, uint16&);
     void               RestoreBits(Coord, Coord);
     void               RestoreBits(const Point&);

#if (__PALM_OS__ >= 0x0400)
     static void        GetDrawWindowBounds(Rect&);
     void               GetBounds(Rect&);
     void               SetBounds(const Rect&);
#else
     static void        GetWindowBounds(Rect&);
     void               SetWindowBounds(const Rect&);
#endif

     void               CopyRectangle(WinHandle, const Rect&, Coord, Coord, WinDrawOperation);
     void               CopyRectangle(WinHandle, const Rect&, const Point&, WinDrawOperation);

     static void        GetDisplayExtent(Coord&, Coord&);
     static void        GetDisplayExtent(Size&);

     static void        GetWindowExtent(Coord&, Coord&);
     static void        GetWindowExtent(Size&);

     static void        DisplayToWindowPt(Coord&, Coord&);
     static void        DisplayToWindowPt(Point&);

     static void        WindowToDisplayPt(Coord&, Coord&);
     static void        WindowToDisplayPt(Point&);

     static void        GetClip(Rect&);
     static void        SetClip (const Rect&);
     static void        ResetClip();
     static void        ClipRectangle(Rect&);

     static void        ScrollRectangle(const Rect&, WinDirectionType, Coord, Rect&);

     static void        ScreenInit();
     static Err         ScreenMode(WinScreenModeOperation, uint32&, uint32&, uint32&, bool&);

     static uint8*      ScreenLock(WinLockInitType);
     static void        ScreenUnlock();

    public:

    class __DECLSPEC__ XPalmWindow : public PalmError
    {
        public:

        enum EErrors
        {
            // appErrorClass+'wind'
        };

        protected:
         virtual void LoadErrorDescriptions();
    };

    friend class XPalmWindow;
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__
#endif // __PALM_WINDOW_H__

