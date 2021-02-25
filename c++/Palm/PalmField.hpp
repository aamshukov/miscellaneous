////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PALM_FIELD_H__
#define __PALM_FIELD_H__

#ifdef __PALM_OS__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class PalmField
// ----- ---------
class __DECLSPEC__ PalmField : public PalmControl
{
    public:
     // ctor/dtor
                        PalmField(FieldType* = null);
     virtual           ~PalmField();

     // operators
                        operator FieldType* ();
                        operator const FieldType* ()    const;

     // api
     char*              GetTextPtr();
     void               SetTextPtr(const char*);
     void               SetText(MemHandle, uint16, uint16);

     MemHandle          GetTextHandle();
     void               SetTextHandle(MemHandle);

     uint16             GetTextLength();
     uint16             GetTextHeight();
     static uint16      CalcFieldHeight(const char*, uint16);

     uint16             GetMaxChars();
     void               SetMaxChars(uint16);

     void               RecalculateField(bool);

     void               CompactText();
     void               FreeMemory();

     uint16             GetTextAllocatedSize();
     void               SetTextAllocatedSize(uint16);

     void               GetAttributes(FieldAttrType&);
     void               SetAttributes(const FieldAttrType&);

     bool               Insert(const char*, uint16);
     void               Delete(uint16, uint16);

     void               Copy();
     void               Cut();
     void               Paste();
     void               Undo();

     void               DrawField();
     void               EraseField();

     void               GetBounds(Rect&);
     void               SetBounds(const Rect&);

     FontID             GetFont();
     void               SetFont(FontID);

     void               SetUsable(bool);
     bool               MakeFullyVisible();
     uint16             GetNumberOfBlankLines();

     void               GrabFocus();
     void               ReleaseFocus();

     void               GetSelection(uint16&, uint16&);
     void               SetSelection(uint16, uint16);
                        
     uint16             GetInsPtPosition();
     void               SetInsPtPosition(uint16);
     void               SetInsertionPoint(uint16);
                        
     bool               IsScrollable(WinDirectionType);
     void               ScrollField(uint16, WinDirectionType);
     uint16             GetScrollPosition();
     void               SetScrollPosition(uint16);
     void               GetScrollValues(uint16&, uint16&, uint16&);
                        
     uint16             GetVisibleLines();
     static uint16      WordWrap(const char*, int16);
                        
     bool               Dirty();
     void               SetDirty(bool);
                        
     void               SendChangeNotification();
     void               SendHeightChangeNotification(uint16, int16);
                        
     bool               HandleEvent(EventType&);

#if (__PALM_OS__ >= 0x0400)
     void               SetMaxVisibleLines(uint8);
#endif

     FieldType*         Clone(uint16, Coord, Coord, Coord, Coord, FontID, uint32, bool, bool, bool, bool, JustificationType, bool, bool, bool);
     FieldType*         Clone(uint16, const Point&, const Size&, FontID, uint32, bool, bool, bool, bool, JustificationType, bool, bool, bool);
     static FieldType*  Clone(void**, uint16, Coord, Coord, Coord, Coord, FontID, uint32, bool, bool, bool, bool, JustificationType, bool, bool, bool);
     static FieldType*  Clone(void**, uint16, const Point&, const Size&, FontID, uint32, bool, bool, bool, bool, JustificationType, bool, bool, bool);

    public:

    class __DECLSPEC__ XPalmField : public XPalmControl
    {
        public:

        enum EErrors
        {
            // appErrorClass+'fild'
        };

        protected:
         virtual void LoadErrorDescriptions();
    };
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__
#endif // __PALM_FIELD_H__

