////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PALM_TABLE_INL__
#define __PALM_TABLE_INL__

#ifdef __PALM_OS__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class PalmTable
// ----- ---------
__INLINE__ PalmTable::operator TableType* ()
{
    return reinterpret_cast<TableType*>(Control);
}

__INLINE__ PalmTable::operator const TableType* () const
{
    return const_cast<const TableType*>(Control);
}

__INLINE__ void PalmTable::DrawTable()
{
    palmxassert(Control != null, Error::eUninitialized, PalmTable::XPalmTable);
  ::TblDrawTable(reinterpret_cast<TableType*>(Control));
}

__INLINE__ void PalmTable::RedrawTable()
{
    palmxassert(Control != null, Error::eUninitialized, PalmTable::XPalmTable);
  ::TblRedrawTable(reinterpret_cast<TableType*>(Control));
}

__INLINE__ void PalmTable::EraseTable()
{
    palmxassert(Control != null, Error::eUninitialized, PalmTable::XPalmTable);
  ::TblEraseTable(reinterpret_cast<TableType*>(Control));
}

__INLINE__ void PalmTable::SetCustomDrawProcedure(int16 _column, TableDrawItemFuncType* _callback)
{
    palmxassert(Control != null, Error::eUninitialized, PalmTable::XPalmTable);
    palmxassert(_callback != null, Error::eInvalidArg, PalmTable::XPalmTable);
  ::TblSetCustomDrawProcedure(reinterpret_cast<TableType*>(Control), _column, _callback);
}

__INLINE__ void PalmTable::GetBounds(Rect& _r)
{
    palmxassert(Control != null, Error::eUninitialized, PalmTable::XPalmTable);
  ::TblGetBounds(reinterpret_cast<TableType*>(Control), &_r);
}

__INLINE__ void PalmTable::SetBounds(const Rect& _r)
{
    palmxassert(Control != null, Error::eUninitialized, PalmTable::XPalmTable);
  ::TblSetBounds(reinterpret_cast<TableType*>(Control), &_r);
}

__INLINE__ bool PalmTable::GetSelection(int16& _row, int16& _column)
{
    palmxassert(Control != null, Error::eUninitialized, PalmTable::XPalmTable);
    return ::TblGetSelection(reinterpret_cast<TableType*>(Control), &_row, &_column);
}

__INLINE__ void PalmTable::UnhighlightSelection()
{
    palmxassert(Control != null, Error::eUninitialized, PalmTable::XPalmTable);
  ::TblUnhighlightSelection(reinterpret_cast<TableType*>(Control));
}

__INLINE__ void PalmTable::MarkTableInvalid()
{
    palmxassert(Control != null, Error::eUninitialized, PalmTable::XPalmTable);
  ::TblMarkTableInvalid(reinterpret_cast<TableType*>(Control));
}

__INLINE__ bool PalmTable::Editing()
{
    palmxassert(Control != null, Error::eUninitialized, PalmTable::XPalmTable);
    return ::TblEditing(reinterpret_cast<TableType*>(Control));
}

__INLINE__ void PalmTable::HasScrollBar(bool _has)
{
    palmxassert(Control != null, Error::eUninitialized, PalmTable::XPalmTable);
  ::TblHasScrollBar(reinterpret_cast<TableType*>(Control), _has);
}

__INLINE__ void PalmTable::GrabFocus(int16 _row, int16 _column)
{
    palmxassert(Control != null, Error::eUninitialized, PalmTable::XPalmTable);
  ::TblGrabFocus(reinterpret_cast<TableType*>(Control), _row, _column);
}

__INLINE__ void PalmTable::ReleaseFocus()
{
    palmxassert(Control != null, Error::eUninitialized, PalmTable::XPalmTable);
  ::TblReleaseFocus(reinterpret_cast<TableType*>(Control));
}

__INLINE__ void PalmTable::SetLoadDataProcedure(int16 _column, TableLoadDataFuncType* _callback)
{
    palmxassert(Control != null, Error::eUninitialized, PalmTable::XPalmTable);
    palmxassert(_callback != null, Error::eInvalidArg, PalmTable::XPalmTable);
  ::TblSetLoadDataProcedure(reinterpret_cast<TableType*>(Control), _column, _callback);
}

__INLINE__ void PalmTable::SetSaveDataProcedure(int16 _column, TableSaveDataFuncType* _callback)
{
    palmxassert(Control != null, Error::eUninitialized, PalmTable::XPalmTable);
    palmxassert(_callback != null, Error::eInvalidArg, PalmTable::XPalmTable);
  ::TblSetSaveDataProcedure(reinterpret_cast<TableType*>(Control), _column, _callback);
}

__INLINE__ bool PalmTable::HandleEvent(EventType& _event)
{
    palmxassert(Control != null, Error::eUninitialized, PalmTable::XPalmTable);
    return ::TblHandleEvent(reinterpret_cast<TableType*>(Control), &_event);
}

__INLINE__ FieldType* PalmTable::GetCurrentField()
{
    palmxassert(Control != null, Error::eUninitialized, PalmTable::XPalmTable);
    return ::TblGetCurrentField(reinterpret_cast<TableType*>(Control));
}

__INLINE__ void PalmTable::SetColumnUsable(int16 _column, bool _usable)
{
    palmxassert(Control != null, Error::eUninitialized, PalmTable::XPalmTable);
    return ::TblSetColumnUsable(reinterpret_cast<TableType*>(Control), _column, _usable);
}

__INLINE__ void PalmTable::SetColumnEditIndicator(int16 _column, bool _indicator)
{
    palmxassert(Control != null, Error::eUninitialized, PalmTable::XPalmTable);
  ::TblSetColumnEditIndicator(reinterpret_cast<TableType*>(Control), _column, _indicator);
}

__INLINE__ void PalmTable::SetColumnMasked(int16 _column, bool _masked)
{
    palmxassert(Control != null, Error::eUninitialized, PalmTable::XPalmTable);
  ::TblSetColumnMasked(reinterpret_cast<TableType*>(Control), _column, _masked);
}

__INLINE__ Coord PalmTable::GetColumnWidth(int16 _column)
{
    palmxassert(Control != null, Error::eUninitialized, PalmTable::XPalmTable);
    return ::TblGetColumnWidth(reinterpret_cast<TableType*>(Control), _column);
}

__INLINE__ void PalmTable::SetColumnWidth(int16 _column, Coord _width)
{
    palmxassert(Control != null, Error::eUninitialized, PalmTable::XPalmTable);
  ::TblSetColumnWidth(reinterpret_cast<TableType*>(Control), _column, _width);
}

__INLINE__ int16 PalmTable::GetColumnSpacing(int16 _column)
{
    palmxassert(Control != null, Error::eUninitialized, PalmTable::XPalmTable);
    return ::TblGetColumnSpacing(reinterpret_cast<TableType*>(Control), _column);
}

__INLINE__ void PalmTable::SetColumnSpacing(int16 _column, Coord _spacing)
{
    palmxassert(Control != null, Error::eUninitialized, PalmTable::XPalmTable);
  ::TblSetColumnSpacing(reinterpret_cast<TableType*>(Control), _column, _spacing);
}

__INLINE__ uint16 PalmTable::GetRowID(int16 _row)
{
    palmxassert(Control != null, Error::eUninitialized, PalmTable::XPalmTable);
    return ::TblGetRowID(reinterpret_cast<TableType*>(Control), _row);
}

__INLINE__ void PalmTable::SetRowID(int16 _row, uint16 _id)
{
    palmxassert(Control != null, Error::eUninitialized, PalmTable::XPalmTable);
  ::TblSetRowID(reinterpret_cast<TableType*>(Control), _row, _id);
}

__INLINE__ bool PalmTable::IsRowUsable(int16 _row)
{
    palmxassert(Control != null, Error::eUninitialized, PalmTable::XPalmTable);
    return ::TblRowUsable(reinterpret_cast<TableType*>(Control), _row);
}

__INLINE__ int16 PalmTable::GetLastUsableRow()
{
    palmxassert(Control != null, Error::eUninitialized, PalmTable::XPalmTable);
    return ::TblGetLastUsableRow(reinterpret_cast<TableType*>(Control));
}

__INLINE__ void PalmTable::SetRowUsable(int16 _row, bool _usable)
{
    palmxassert(Control != null, Error::eUninitialized, PalmTable::XPalmTable);
  ::TblSetRowUsable(reinterpret_cast<TableType*>(Control), _row, _usable);
}

__INLINE__ bool PalmTable::IsRowSelectable(int16 _row)
{
    palmxassert(Control != null, Error::eUninitialized, PalmTable::XPalmTable);
    return ::TblRowSelectable(reinterpret_cast<TableType*>(Control), _row);
}

__INLINE__ void PalmTable::SetRowSelectable(int16 _row, bool _select)
{
    palmxassert(Control != null, Error::eUninitialized, PalmTable::XPalmTable);
  ::TblSetRowSelectable(reinterpret_cast<TableType*>(Control), _row, _select);
}

__INLINE__ int16 PalmTable::GetNumberOfRows()
{
    palmxassert(Control != null, Error::eUninitialized, PalmTable::XPalmTable);
    return ::TblGetNumberOfRows(reinterpret_cast<TableType*>(Control));
}

__INLINE__ Coord PalmTable::GetRowHeight(int16 _row)
{
    palmxassert(Control != null, Error::eUninitialized, PalmTable::XPalmTable);
    return ::TblGetRowHeight(reinterpret_cast<TableType*>(Control), _row);
}

__INLINE__ void PalmTable::SetRowHeight(int16 _row, Coord _height)
{
    palmxassert(Control != null, Error::eUninitialized, PalmTable::XPalmTable);
  ::TblSetRowHeight(reinterpret_cast<TableType*>(Control), _row, _height);
}

__INLINE__ void PalmTable::SetRowStaticHeight(int16 _row, bool _static)
{
    palmxassert(Control != null, Error::eUninitialized, PalmTable::XPalmTable);
  ::TblSetRowStaticHeight(reinterpret_cast<TableType*>(Control), _row, _static);
}

__INLINE__ bool PalmTable::FindRowID(uint16 _id, int16& _row)
{
    palmxassert(Control != null, Error::eUninitialized, PalmTable::XPalmTable);
    return ::TblFindRowID(reinterpret_cast<TableType*>(Control), _id, &_row);
}

__INLINE__ bool PalmTable::FindRowData(uint32 _data, int16& _row)
{
    palmxassert(Control != null, Error::eUninitialized, PalmTable::XPalmTable);
    return ::TblFindRowData(reinterpret_cast<TableType*>(Control), _data, &_row);
}

__INLINE__ uint32 PalmTable::GetRowData(int16 _row)
{
    palmxassert(Control != null, Error::eUninitialized, PalmTable::XPalmTable);
    return ::TblGetRowData(reinterpret_cast<TableType*>(Control), _row);
}

__INLINE__ void PalmTable::SetRowData(int16 _row, uint32 _data)
{
    palmxassert(Control != null, Error::eUninitialized, PalmTable::XPalmTable);
  ::TblSetRowData(reinterpret_cast<TableType*>(Control), _row, _data);
}

__INLINE__ bool PalmTable::IsRowInvalid(int16 _row)
{
    palmxassert(Control != null, Error::eUninitialized, PalmTable::XPalmTable);
    return ::TblRowInvalid(reinterpret_cast<TableType*>(Control), _row);
}

__INLINE__ void PalmTable::MarkRowInvalid(int16 _row)
{
    palmxassert(Control != null, Error::eUninitialized, PalmTable::XPalmTable);
  ::TblMarkRowInvalid(reinterpret_cast<TableType*>(Control), _row);
}

__INLINE__ void PalmTable::InsertRow(int16 _row)
{
    palmxassert(Control != null, Error::eUninitialized, PalmTable::XPalmTable);
  ::TblInsertRow(reinterpret_cast<TableType*>(Control), _row);
}

__INLINE__ void PalmTable::RemoveRow(int16 _row)
{
    palmxassert(Control != null, Error::eUninitialized, PalmTable::XPalmTable);
  ::TblRemoveRow(reinterpret_cast<TableType*>(Control), _row);
}

__INLINE__ bool PalmTable::IsRowMasked(int16 _row)
{
    palmxassert(Control != null, Error::eUninitialized, PalmTable::XPalmTable);
    return ::TblRowMasked(reinterpret_cast<TableType*>(Control), _row);
}

__INLINE__ void PalmTable::SetRowMasked(int16 _row, bool _masked)
{
    palmxassert(Control != null, Error::eUninitialized, PalmTable::XPalmTable);
  ::TblSetRowMasked(reinterpret_cast<TableType*>(Control), _row, _masked);
}

__INLINE__ void* PalmTable::GetItemPtr(int16 _row, int16 _column)
{
    palmxassert(Control != null, Error::eUninitialized, PalmTable::XPalmTable);
    return ::TblGetItemPtr(reinterpret_cast<TableType*>(Control), _row, _column);
}

__INLINE__ void PalmTable::SetItemPtr(int16 _row, int16 _column, void* _p)
{
    palmxassert(Control != null, Error::eUninitialized, PalmTable::XPalmTable);
    palmxassert(_p != null, Error::eInvalidArg, PalmTable::XPalmTable);
  ::TblSetItemPtr(reinterpret_cast<TableType*>(Control), _row, _column, _p);
}

__INLINE__ int16 PalmTable::GetItemInt(int16 _row, int16 _column)
{
    palmxassert(Control != null, Error::eUninitialized, PalmTable::XPalmTable);
    return ::TblGetItemInt(reinterpret_cast<TableType*>(Control), _row, _column);
}

__INLINE__ void PalmTable::SetItemInt(int16 _row, int16 _column, int16 _value)
{
    palmxassert(Control != null, Error::eUninitialized, PalmTable::XPalmTable);
  ::TblSetItemInt(reinterpret_cast<TableType*>(Control), _row, _column, _value);
}

__INLINE__ FontID PalmTable::GetItemFont(int16 _row, int16 _column)
{
    palmxassert(Control != null, Error::eUninitialized, PalmTable::XPalmTable);
    return ::TblGetItemFont(reinterpret_cast<TableType*>(Control), _row, _column);
}

__INLINE__ void PalmTable::SetItemFont(int16 _row, int16 _column, FontID _id)
{
    palmxassert(Control != null, Error::eUninitialized, PalmTable::XPalmTable);
  ::TblSetItemFont(reinterpret_cast<TableType*>(Control), _row, _column, _id);
}

__INLINE__ void PalmTable::GetItemBounds(int16 _row, int16 _column, Rect& _r)
{
    palmxassert(Control != null, Error::eUninitialized, PalmTable::XPalmTable);
  ::TblGetItemBounds(reinterpret_cast<TableType*>(Control), _row, _column, &_r);
}

__INLINE__ void PalmTable::SetItemStyle(int16 _row, int16 _column, TableItemStyleType _style)
{
    palmxassert(Control != null, Error::eUninitialized, PalmTable::XPalmTable);
  ::TblSetItemStyle(reinterpret_cast<TableType*>(Control), _row, _column, _style);
}

__INLINE__ void PalmTable::SelectItem(int16 _row, int16 _column)
{
    palmxassert(Control != null, Error::eUninitialized, PalmTable::XPalmTable);
  ::TblSelectItem(reinterpret_cast<TableType*>(Control), _row, _column);
}

#if (__PALM_OS__ >= 0x0400)
__INLINE__ int16 PalmTable::GetNumberOfColumns()
{
    palmxassert(Control != null, Error::eUninitialized, PalmTable::XPalmTable);
    return ::TblGetNumberOfColumns(reinterpret_cast<TableType*>(Control));
}

__INLINE__ int16 PalmTable::GetTopRow()
{
    palmxassert(Control != null, Error::eUninitialized, PalmTable::XPalmTable);
    return ::TblGetTopRow(reinterpret_cast<TableType*>(Control));
}

__INLINE__ void PalmTable::SetSelection(int16 _row, int16 _column)
{
    palmxassert(Control != null, Error::eUninitialized, PalmTable::XPalmTable);
  ::TblSetSelection(reinterpret_cast<TableType*>(Control), _row, _column);
}
#endif
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__
#endif // __PALM_TABLE_INL__
