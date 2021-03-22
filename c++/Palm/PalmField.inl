////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PALM_FIELD_INL__
#define __PALM_FIELD_INL__

#ifdef __PALM_OS__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class PalmField
// ----- ---------
__INLINE__ PalmField::operator FieldType* ()
{
    return static_cast<FieldType*>(Control);
}

__INLINE__ PalmField::operator const FieldType* () const
{
    return const_cast<const FieldType*>(Control);
}

__INLINE__ char* PalmField::GetTextPtr()
{
    palmxassert(Control != null, Error::eUninitialized, PalmField::XPalmField);
    return ::FldGetTextPtr(static_cast<FieldType*>(Control));
}

__INLINE__ void PalmField::SetTextPtr(const char* _text)
{
    palmxassert(Control != null, Error::eUninitialized, PalmField::XPalmField);
    palmxassert(_text != null, Error::eInvalidArg, PalmField::XPalmField);
  ::FldSetTextPtr(static_cast<FieldType*>(Control), const_cast<char*>(_text));
}

__INLINE__ void PalmField::SetText(MemHandle _handle, uint16 _offset, uint16 _size)
{
    palmxassert(Control != null, Error::eUninitialized, PalmField::XPalmField);
    palmxassert(_handle != 0, Error::eInvalidArg, PalmField::XPalmField);
  ::FldSetText(static_cast<FieldType*>(Control), _handle, _offset, _size);
}

__INLINE__ MemHandle PalmField::GetTextHandle()
{
    palmxassert(Control != null, Error::eUninitialized, PalmField::XPalmField);
    return ::FldGetTextHandle(static_cast<FieldType*>(Control));
}

__INLINE__ void PalmField::SetTextHandle(MemHandle _handle)
{
    palmxassert(Control != null, Error::eUninitialized, PalmField::XPalmField);
    palmxassert(_handle != 0, Error::eInvalidArg, PalmField::XPalmField);
  ::FldSetTextHandle(static_cast<FieldType*>(Control), _handle);
}

__INLINE__ uint16 PalmField::GetTextLength()
{
    palmxassert(Control != null, Error::eUninitialized, PalmField::XPalmField);
    return ::FldGetTextLength(static_cast<FieldType*>(Control));
}

__INLINE__ uint16 PalmField::GetTextHeight()
{
    palmxassert(Control != null, Error::eUninitialized, PalmField::XPalmField);
    return ::FldGetTextHeight(static_cast<FieldType*>(Control));
}

__INLINE__ uint16 PalmField::CalcFieldHeight(const char* _chars, uint16 _width)
{
    palmxassert(_chars != null, Error::eInvalidArg, PalmField::XPalmField);
    return ::FldCalcFieldHeight(_chars, _width);
}

__INLINE__ uint16 PalmField::GetMaxChars()
{
    palmxassert(Control != null, Error::eUninitialized, PalmField::XPalmField);
    return ::FldGetMaxChars(static_cast<FieldType*>(Control));
}

__INLINE__ void PalmField::SetMaxChars(uint16 _max_chars)
{
    palmxassert(Control != null, Error::eUninitialized, PalmField::XPalmField);
  ::FldSetMaxChars(static_cast<FieldType*>(Control), _max_chars);
}

__INLINE__ void PalmField::RecalculateField(bool _redraw)
{
    palmxassert(Control != null, Error::eUninitialized, PalmField::XPalmField);
  ::FldRecalculateField(static_cast<FieldType*>(Control), _redraw);
}

__INLINE__ void PalmField::CompactText()
{
    palmxassert(Control != null, Error::eUninitialized, PalmField::XPalmField);
  ::FldCompactText(static_cast<FieldType*>(Control));
}

__INLINE__ void PalmField::FreeMemory()
{
    palmxassert(Control != null, Error::eUninitialized, PalmField::XPalmField);
  ::FldFreeMemory(static_cast<FieldType*>(Control));
}

__INLINE__ uint16 PalmField::GetTextAllocatedSize()
{
    palmxassert(Control != null, Error::eUninitialized, PalmField::XPalmField);
    return ::FldGetTextAllocatedSize(static_cast<FieldType*>(Control));
}

__INLINE__ void PalmField::SetTextAllocatedSize(uint16 _size)
{
    palmxassert(Control != null, Error::eUninitialized, PalmField::XPalmField);
    palmxassert(_size > 0, Error::eInvalidArg, PalmField::XPalmField);
  ::FldSetTextAllocatedSize(static_cast<FieldType*>(Control), _size);
}

__INLINE__ void PalmField::GetAttributes(FieldAttrType& _attr)
{
    palmxassert(Control != null, Error::eUninitialized, PalmField::XPalmField);
  ::FldGetAttributes(static_cast<FieldType*>(Control), &_attr);
}

__INLINE__ void PalmField::SetAttributes(const FieldAttrType& _attr)
{
    palmxassert(Control != null, Error::eUninitialized, PalmField::XPalmField);
  ::FldSetAttributes(static_cast<FieldType*>(Control), &_attr);
}

__INLINE__ bool PalmField::Insert(const char* _text, uint16 _len)
{
    palmxassert(Control != null, Error::eUninitialized, PalmField::XPalmField);
    palmxassert(_text != null && _len > 0, Error::eInvalidArg, PalmField::XPalmField);
    return ::FldInsert(static_cast<FieldType*>(Control), _text, _len);
}

__INLINE__ void PalmField::Delete(uint16 _start, uint16 _end)
{
    palmxassert(Control != null, Error::eUninitialized, PalmField::XPalmField);
    palmxassert(_start <= _end, Error::eInvalidArg, PalmField::XPalmField);
  ::FldDelete(static_cast<FieldType*>(Control), _start, _end);
}

__INLINE__ void PalmField::Copy()
{
    palmxassert(Control != null, Error::eUninitialized, PalmField::XPalmField);
  ::FldCopy(static_cast<FieldType*>(Control));
}

__INLINE__ void PalmField::Cut()
{
    palmxassert(Control != null, Error::eUninitialized, PalmField::XPalmField);
  ::FldCut(static_cast<FieldType*>(Control));
}

__INLINE__ void PalmField::Paste()
{
    palmxassert(Control != null, Error::eUninitialized, PalmField::XPalmField);
  ::FldPaste(static_cast<FieldType*>(Control));
}

__INLINE__ void PalmField::Undo()
{
    palmxassert(Control != null, Error::eUninitialized, PalmField::XPalmField);
  ::FldUndo(static_cast<FieldType*>(Control));
}

__INLINE__ void PalmField::DrawField()
{
    palmxassert(Control != null, Error::eUninitialized, PalmField::XPalmField);
  ::FldDrawField(static_cast<FieldType*>(Control));
}

__INLINE__ void PalmField::EraseField()
{
    palmxassert(Control != null, Error::eUninitialized, PalmField::XPalmField);
  ::FldEraseField(static_cast<FieldType*>(Control));
}

__INLINE__ void PalmField::GetBounds(Rect& _r)
{
    palmxassert(Control != null, Error::eUninitialized, PalmField::XPalmField);
  ::FldGetBounds(static_cast<FieldType*>(Control), &_r);
}

__INLINE__ void PalmField::SetBounds(const Rect& _r)
{
    palmxassert(Control != null, Error::eUninitialized, PalmField::XPalmField);
  ::FldSetBounds(static_cast<FieldType*>(Control), &_r);
}

__INLINE__ FontID PalmField::GetFont()
{
    palmxassert(Control != null, Error::eUninitialized, PalmField::XPalmField);
    return ::FldGetFont(static_cast<FieldType*>(Control));
}

__INLINE__ void PalmField::SetFont(FontID _id)
{
    palmxassert(Control != null, Error::eUninitialized, PalmField::XPalmField);
  ::FldSetFont(static_cast<FieldType*>(Control), _id);
}

__INLINE__ void PalmField::SetUsable(bool _usable)
{
    palmxassert(Control != null, Error::eUninitialized, PalmField::XPalmField);
  ::FldSetUsable(static_cast<FieldType*>(Control), _usable);
}

__INLINE__ bool PalmField::MakeFullyVisible()
{
    palmxassert(Control != null, Error::eUninitialized, PalmField::XPalmField);
    return ::FldMakeFullyVisible(static_cast<FieldType*>(Control));
}

__INLINE__ uint16 PalmField::GetNumberOfBlankLines()
{
    palmxassert(Control != null, Error::eUninitialized, PalmField::XPalmField);
    return ::FldGetNumberOfBlankLines(static_cast<FieldType*>(Control));
}

__INLINE__ void PalmField::GrabFocus()
{
    palmxassert(Control != null, Error::eUninitialized, PalmField::XPalmField);
  ::FldGrabFocus(static_cast<FieldType*>(Control));
}

__INLINE__ void PalmField::ReleaseFocus()
{
    palmxassert(Control != null, Error::eUninitialized, PalmField::XPalmField);
  ::FldReleaseFocus(static_cast<FieldType*>(Control));
}

__INLINE__ void PalmField::GetSelection(uint16& _start, uint16& _end)
{
    palmxassert(Control != null, Error::eUninitialized, PalmField::XPalmField);
  ::FldGetSelection(static_cast<FieldType*>(Control), &_start, &_end);
}

__INLINE__ void PalmField::SetSelection(uint16 _start, uint16 _end)
{
    palmxassert(Control != null, Error::eUninitialized, PalmField::XPalmField);
    palmxassert(_start <= _end, Error::eInvalidArg, PalmField::XPalmField);
  ::FldSetSelection(static_cast<FieldType*>(Control), _start, _end);
}

__INLINE__ uint16 PalmField::GetInsPtPosition()
{
    palmxassert(Control != null, Error::eUninitialized, PalmField::XPalmField);
    return ::FldGetInsPtPosition(static_cast<FieldType*>(Control));
}

__INLINE__ void PalmField::SetInsPtPosition(uint16 _pos)
{
    palmxassert(Control != null, Error::eUninitialized, PalmField::XPalmField);
  ::FldSetInsPtPosition(static_cast<FieldType*>(Control), _pos);
}

__INLINE__ void PalmField::SetInsertionPoint(uint16 _pos)
{
    palmxassert(Control != null, Error::eUninitialized, PalmField::XPalmField);
  ::FldSetInsertionPoint(static_cast<FieldType*>(Control), _pos);
}

__INLINE__ bool PalmField::IsScrollable(WinDirectionType _dir)
{
    palmxassert(Control != null, Error::eUninitialized, PalmField::XPalmField);
    return ::FldScrollable(static_cast<FieldType*>(Control), _dir);
}

__INLINE__ void PalmField::ScrollField(uint16 _count, WinDirectionType _dir)
{
    palmxassert(Control != null, Error::eUninitialized, PalmField::XPalmField);
  ::FldScrollField(static_cast<FieldType*>(Control), _count, _dir);
}

__INLINE__ uint16 PalmField::GetScrollPosition()
{
    palmxassert(Control != null, Error::eUninitialized, PalmField::XPalmField);
    return ::FldGetScrollPosition(static_cast<FieldType*>(Control));
}

__INLINE__ void PalmField::SetScrollPosition(uint16 _pos)
{
    palmxassert(Control != null, Error::eUninitialized, PalmField::XPalmField);
  ::FldSetScrollPosition(static_cast<FieldType*>(Control), _pos);
}

__INLINE__ void PalmField::GetScrollValues(uint16& _scroll_pos, uint16& _text_height, uint16& _field_height)
{
    palmxassert(Control != null, Error::eUninitialized, PalmField::XPalmField);
  ::FldGetScrollValues(static_cast<FieldType*>(Control), &_scroll_pos, &_text_height, &_field_height);
}

__INLINE__ uint16 PalmField::GetVisibleLines()
{
    palmxassert(Control != null, Error::eUninitialized, PalmField::XPalmField);
    return ::FldGetVisibleLines(static_cast<FieldType*>(Control));
}

__INLINE__ uint16 PalmField::WordWrap(const char* _text, int16 _len)
{
    palmxassert(_text != null, Error::eInvalidArg, PalmField::XPalmField);
    return ::FldWordWrap(_text, _len);
}

__INLINE__ bool PalmField::Dirty()
{
    palmxassert(Control != null, Error::eUninitialized, PalmField::XPalmField);
    return ::FldDirty(static_cast<FieldType*>(Control));
}

__INLINE__ void PalmField::SetDirty(bool _dirty)
{
    palmxassert(Control != null, Error::eUninitialized, PalmField::XPalmField);
  ::FldSetDirty(static_cast<FieldType*>(Control), _dirty);
}

__INLINE__ void PalmField::SendChangeNotification()
{
    palmxassert(Control != null, Error::eUninitialized, PalmField::XPalmField);
  ::FldSendChangeNotification(static_cast<FieldType*>(Control));
}

__INLINE__ void PalmField::SendHeightChangeNotification(uint16 _pos, int16 _num_lines)
{
    palmxassert(Control != null, Error::eUninitialized, PalmField::XPalmField);
  ::FldSendHeightChangeNotification(static_cast<FieldType*>(Control), _pos, _num_lines);
}

__INLINE__ bool PalmField::HandleEvent(EventType& _event)
{
    palmxassert(Control != null, Error::eUninitialized, PalmField::XPalmField);
    return ::FldHandleEvent(static_cast<FieldType*>(Control), &_event);
}

#if (__PALM_OS__ >= 0x0400)
__INLINE__ void PalmField::SetMaxVisibleLines(uint8 _max_lines)
{
    palmxassert(Control != null, Error::eUninitialized, PalmField::XPalmField);
  ::FldSetMaxVisibleLines(static_cast<FieldType*>(Control), _max_lines);
}
#endif

__INLINE__ FieldType* PalmField::Clone(uint16 _id,
                                       Coord _x, Coord _y, Coord _w, Coord _h,
                                       FontID _font_id, uint32 _max_chars, bool _editable,
                                       bool _underlined, bool _single_line, bool _dynamic,
                                       JustificationType _justification, bool _autoshift,
                                       bool _has_scrollbars, bool _numeric)
{
    palmxassert(Control != null, Error::eUninitialized, PalmField::XPalmField);
    return ::FldNewField(&Control, _id, _x, _y, _w, _h, _font_id, _max_chars, _editable, _underlined, _single_line, _dynamic, _justification, _autoshift, _has_scrollbars, _numeric);
}

__INLINE__ FieldType* PalmField::Clone(uint16 _id,
                                       const Point& _pt, const Size& _sz,
                                       FontID _font_id, uint32 _max_chars, bool _editable,
                                       bool _underlined, bool _single_line, bool _dynamic,
                                       JustificationType _justification, bool _autoshift,
                                       bool _has_scrollbars, bool _numeric)
{
    palmxassert(Control != null, Error::eUninitialized, PalmField::XPalmField);
    return ::FldNewField(&Control, _id, _pt.x, _pt.y, _sz.cx, _sz.cy, _font_id, _max_chars, _editable, _underlined, _single_line, _dynamic, _justification, _autoshift, _has_scrollbars, _numeric);
}

__INLINE__ FieldType* PalmField::Clone(void** _form, uint16 _id,
                                       Coord _x, Coord _y, Coord _w, Coord _h,
                                       FontID _font_id, uint32 _max_chars, bool _editable,
                                       bool _underlined, bool _single_line, bool _dynamic,
                                       JustificationType _justification, bool _autoshift,
                                       bool _has_scrollbars, bool _numeric)
{
    palmxassert(_form != null, Error::eInvalidArg, PalmField::XPalmField);
    return ::FldNewField(_form, _id, _x, _y, _w, _h, _font_id, _max_chars, _editable, _underlined, _single_line, _dynamic, _justification, _autoshift, _has_scrollbars, _numeric);
}

__INLINE__ FieldType* PalmField::Clone(void** _form, uint16 _id,
                                       const Point& _pt, const Size& _sz,
                                       FontID _font_id, uint32 _max_chars, bool _editable,
                                       bool _underlined, bool _single_line, bool _dynamic,
                                       JustificationType _justification, bool _autoshift,
                                       bool _has_scrollbars, bool _numeric)
{
    palmxassert(_form != null, Error::eInvalidArg, PalmField::XPalmField);
    return ::FldNewField(_form, _id, _pt.x, _pt.y, _sz.cx, _sz.cy, _font_id, _max_chars, _editable, _underlined, _single_line, _dynamic, _justification, _autoshift, _has_scrollbars, _numeric);
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__
#endif // __PALM_FIELD_INL__
