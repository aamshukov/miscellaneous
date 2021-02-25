////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  Copyright © 1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PALM_LIST_INL__
#define __PALM_LIST_INL__

#ifdef __PALM_OS__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class PalmList
// ----- --------
__INLINE__ PalmList::operator ListType* ()
{
    return static_cast<ListType*>(Control);
}

__INLINE__ PalmList::operator const ListType* () const
{
    return const_cast<const ListType*>(Control);
}

__INLINE__ int16 PalmList::GetNumberOfItems()
{
    palmxassert(Control != null, Error::eUninitialized, PalmList::XPalmList);
    return ::LstGetNumberOfItems(static_cast<ListType*>(Control));
}

__INLINE__ void PalmList::DrawList()
{
    palmxassert(Control != null, Error::eUninitialized, PalmList::XPalmList);
  ::LstDrawList(static_cast<ListType*>(Control));
}

__INLINE__ void PalmList::EraseList()
{
    palmxassert(Control != null, Error::eUninitialized, PalmList::XPalmList);
  ::LstEraseList(static_cast<ListType*>(Control));
}

__INLINE__ void PalmList::SetDrawFunction(ListDrawDataFuncType* _handler)
{
    palmxassert(Control != null, Error::eUninitialized, PalmList::XPalmList);
    palmxassert(_handler != null, Error::eInvalidArg, PalmList::XPalmList);
  ::LstSetDrawFunction(static_cast<ListType*>(Control), _handler);
}

__INLINE__ int16 PalmList::GetSelection()
{
    palmxassert(Control != null, Error::eUninitialized, PalmList::XPalmList);
    return ::LstGetSelection(static_cast<ListType*>(Control));
}

__INLINE__ void PalmList::SetSelection(int16 _item)
{
    palmxassert(Control != null, Error::eUninitialized, PalmList::XPalmList);
  ::LstSetSelection(static_cast<ListType*>(Control), _item);
}

__INLINE__ char* PalmList::GetSelectionText(int16 _item)
{
    palmxassert(Control != null, Error::eUninitialized, PalmList::XPalmList);
    return ::LstGetSelectionText(static_cast<ListType*>(Control), _item);
}

__INLINE__ void PalmList::SetHeight(int16 _visible_items)
{
    palmxassert(Control != null, Error::eUninitialized, PalmList::XPalmList);
  ::LstSetHeight(static_cast<ListType*>(Control), _visible_items);
}

__INLINE__ void PalmList::SetListChoices(char** _text, int16 _count)
{
    palmxassert(Control != null, Error::eUninitialized, PalmList::XPalmList);
    palmxassert(_text != null && _count > 0, Error::eInvalidArg, PalmList::XPalmList);
  ::LstSetListChoices(static_cast<ListType*>(Control), _text, _count);
}

__INLINE__ int16 PalmList::PopupList()
{
    palmxassert(Control != null, Error::eUninitialized, PalmList::XPalmList);
    return ::LstPopupList(static_cast<ListType*>(Control));
}

__INLINE__ void PalmList::SetTopItem(int16 _item)
{
    palmxassert(Control != null, Error::eUninitialized, PalmList::XPalmList);
  ::LstSetTopItem(static_cast<ListType*>(Control), _item);
}

__INLINE__ void PalmList::SetPosition(Coord _x, Coord _y)
{
    palmxassert(Control != null, Error::eUninitialized, PalmList::XPalmList);
  ::LstSetPosition(static_cast<ListType*>(Control), _x, _y);
}

__INLINE__ int16 PalmList::GetVisibleItems()
{
    palmxassert(Control != null, Error::eUninitialized, PalmList::XPalmList);
    return ::LstGetVisibleItems(static_cast<ListType*>(Control));
}

__INLINE__ void PalmList::MakeItemVisible(int16 _item)
{
    palmxassert(Control != null, Error::eUninitialized, PalmList::XPalmList);
  ::LstMakeItemVisible(static_cast<ListType*>(Control), _item);
}

__INLINE__ bool PalmList::ScrollList(WinDirectionType _dir, int16 _count)
{
    palmxassert(Control != null, Error::eUninitialized, PalmList::XPalmList);
    return ::LstScrollList(static_cast<ListType*>(Control), _dir, _count);
}

__INLINE__ bool PalmList::HandleEvent(const EventType& _event)
{
    palmxassert(Control != null, Error::eUninitialized, PalmList::XPalmList);
    return ::LstHandleEvent(static_cast<ListType*>(Control), &_event);
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__
#endif // __PALM_LIST_INL__
