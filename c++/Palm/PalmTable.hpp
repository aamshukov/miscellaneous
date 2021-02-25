////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PALM_TABLE_H__
#define __PALM_TABLE_H__

#ifdef __PALM_OS__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class PalmTable
// ----- ---------
class __DECLSPEC__ PalmTable : public PalmControl
{
    public:
     // ctor/dtor
                    PalmTable(TableType* = null);
     virtual       ~PalmTable();

     // operators
                    operator TableType* ();
                    operator const TableType* ()    const;

     // drawing
     void           DrawTable();
     void           RedrawTable();
     void           EraseTable();

     void           SetCustomDrawProcedure(int16, TableDrawItemFuncType*);

     // table
     void           GetBounds(Rect&);
     void           SetBounds(const Rect&);

     bool           GetSelection(int16&, int16&);
     void           UnhighlightSelection();

     void           MarkTableInvalid();

     bool           Editing();

     void           HasScrollBar(bool);

     void           GrabFocus(int16, int16);
     void           ReleaseFocus();

     void           SetLoadDataProcedure(int16, TableLoadDataFuncType*);
     void           SetSaveDataProcedure(int16, TableSaveDataFuncType*);

     bool           HandleEvent(EventType&);

     // column
     FieldType*     GetCurrentField();
     void           SetColumnUsable(int16, bool);
     void           SetColumnEditIndicator(int16, bool);
     void           SetColumnMasked(int16, bool);

     Coord          GetColumnWidth(int16);
     void           SetColumnWidth(int16, Coord);

     Coord          GetColumnSpacing(int16);
     void           SetColumnSpacing(int16, Coord);

     // row
     uint16         GetRowID(int16);
     void           SetRowID(int16, uint16);

     bool           IsRowUsable(int16);
     int16          GetLastUsableRow();
     void           SetRowUsable(int16, bool);

     bool           IsRowSelectable(int16);
     void           SetRowSelectable(int16, bool);

     int16          GetNumberOfRows();

     Coord          GetRowHeight(int16);
     void           SetRowHeight(int16, Coord);
     void           SetRowStaticHeight(int16, bool);

     bool           FindRowID(uint16, int16&);
     bool           FindRowData(uint32, int16&);

     uint32         GetRowData(int16);
     void           SetRowData(int16, uint32);

     bool           IsRowInvalid(int16);
     void           MarkRowInvalid(int16);

     void           InsertRow(int16);
     void           RemoveRow(int16);

     bool           IsRowMasked(int16);
     void           SetRowMasked(int16, bool);

     // cell
     void*          GetItemPtr(int16, int16);
     void           SetItemPtr(int16, int16, void*);

     int16          GetItemInt(int16, int16);
     void           SetItemInt(int16, int16, int16);

     FontID         GetItemFont(int16, int16);
     void           SetItemFont(int16, int16, FontID);

     void           GetItemBounds(int16, int16, Rect&);
     void           SetItemStyle(int16, int16, TableItemStyleType);

     void           SelectItem(int16, int16);

#if (__PALM_OS__ >= 0x0400)
     int16          GetNumberOfColumns();
     int16          GetTopRow();
     void           SetSelection(int16, int16);
#endif

    public:

    class __DECLSPEC__ XPalmTable : public XPalmControl
    {
        public:

        enum EErrors
        {
            // appErrorClass+'pvfs'
        };

        protected:
         virtual void LoadErrorDescriptions();
    };

    friend class XPalmTable;
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__
#endif // __PALM_TABLE_H__

