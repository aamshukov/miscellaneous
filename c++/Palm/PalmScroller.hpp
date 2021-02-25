////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  Copyright © 1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PALM_SCROLLER_H__
#define __PALM_SCROLLER_H__

#ifdef __PALM_OS__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class PalmScroller
// ----- ------------
class __DECLSPEC__ PalmScroller : public PalmControl
{
    public:
     // ctor/dtor
                        PalmScroller(ScrollBarType* = null);
     virtual           ~PalmScroller();

     // operators
                        operator ScrollBarType* ();
                        operator const ScrollBarType* ()    const;

     // api
     void               GetScrollBar(int16&, int16&, int16&, int16&);
     void               SetScrollBar(int16, int16, int16, int16);
     void               DrawScrollBar();
     bool               HandleEvent(const EventType&);

    public:

    class __DECLSPEC__ XPalmScroller : public XPalmControl
    {
        public:

        enum EErrors
        {
            // appErrorClass+'scrl'
        };

        protected:
         virtual void LoadErrorDescriptions();
    };

    friend class XPalmScroller;
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__
#endif // __PALM_SCROLLER_H__

