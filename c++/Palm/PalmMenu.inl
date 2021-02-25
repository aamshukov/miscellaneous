////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PALM_MENU_INL__
#define __PALM_MENU_INL__

#ifdef __PALM_OS__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class PalmMenu
// ----- --------
__INLINE__ PalmMenu::operator MenuBarType* ()
{
    return static_cast<MenuBarType*>(Menu);
}

__INLINE__ PalmMenu::operator const MenuBarType* () const
{
    return const_cast<const MenuBarType*>(Menu);
}

__INLINE__ bool PalmMenu::IsValid() const
{
    return Menu != null;
}

__INLINE__ void PalmMenu::Attach()
{
    Menu = ::MenuGetActiveMenu();
}

__INLINE__ void PalmMenu::Detach()
{
    Menu = null;
}

__INLINE__ bool PalmMenu::Init(uint16 _id)
{
    Menu = ::MenuInit(_id);
    return Menu != null;
}

__INLINE__ void PalmMenu::Dispose()
{
    palmxassert(Menu != null, Error::eUninitialized, PalmMenu::XPalmMenu);
  ::MenuDispose(Menu), Menu = null;
}

__INLINE__ MenuBarType* PalmMenu::GetActiveMenu()
{
    return ::MenuGetActiveMenu();
}

__INLINE__ MenuBarType* PalmMenu::SetActiveMenu()
{
    palmxassert(Menu != null, Error::eUninitialized, PalmMenu::XPalmMenu);
    return ::MenuSetActiveMenu(Menu);
}

__INLINE__ void PalmMenu::SetActiveMenuRscID(uint16 _id)
{
  ::MenuSetActiveMenuRscID(_id);
}

__INLINE__ void PalmMenu::DrawMenu()
{
    palmxassert(Menu != null, Error::eUninitialized, PalmMenu::XPalmMenu);
  ::MenuDrawMenu(Menu);
}

__INLINE__ void PalmMenu::EraseStatus()
{
    palmxassert(Menu != null, Error::eUninitialized, PalmMenu::XPalmMenu);
  ::MenuEraseStatus(Menu);
}

__INLINE__ Err PalmMenu::AddItem(uint16 _position_id, uint16 _id, char _cmd, const char* _text)
{
    palmxassert(_text != null, Error::eInvalidArg, PalmMenu::XPalmMenu)
    return ::MenuAddItem(_position_id, _id, _cmd, _text);
}

__INLINE__ bool PalmMenu::ShowItem(uint16 _id)
{
    return ::MenuShowItem(_id);
}

__INLINE__ bool PalmMenu::HideItem(uint16 _id)
{
    return ::MenuHideItem(_id);
}

__INLINE__ Err PalmMenu::CmdBarAddButton(uint8 _where, uint16 _bmp_id, MenuCmdBarResultType _type, uint32 _result, char* _name)
{
    palmxassert(_name != null, Error::eInvalidArg, PalmMenu::XPalmMenu);
    return ::MenuCmdBarAddButton(_where, _bmp_id, _type, _result, _name);
}

__INLINE__ bool PalmMenu::CmdBarGetButtonData(int16 _button_index, uint16& _bmp_id, MenuCmdBarResultType& _type, uint32& _result, char* _name)
{
    palmxassert(_name != null, Error::eInvalidArg, PalmMenu::XPalmMenu);
    return ::MenuCmdBarGetButtonData(_button_index, &_bmp_id, &_type, &_result, _name);
}

__INLINE__ void PalmMenu::CmdBarDisplay()
{
  ::MenuCmdBarDisplay();
}

__INLINE__ bool PalmMenu::HandleEvent(EventType& _event, uint16& _error)
{
    palmxassert(Menu != null, Error::eUninitialized, PalmMenu::XPalmMenu);
    return ::MenuHandleEvent(Menu, &_event, &_error);
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__
#endif // __PALM_MENU_INL__
