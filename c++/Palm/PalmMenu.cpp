////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  Copyright © 1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __AIL_H__
#   include <ail.hpp>
#endif

#ifndef __PALM_MENU_INC__
#   include <PalmMenu.inc>
#endif

#ifdef __PALM_OS__

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class PalmMenu
// ----- --------
PalmMenu::PalmMenu(MenuBarType* _menu)
        : Menu(_menu)
{
}

PalmMenu::~PalmMenu()
{
}
////////////////////////////////////////////////////////////////////////////////////////
// class XPalmMenu
// ----- ---------
void PalmMenu::XPalmMenu::LoadErrorDescriptions()
{
    // base class
    PalmError::LoadErrorDescriptions();

    GetDescriptions()[menuErrNoMenu]       = "No error";
    GetDescriptions()[menuErrNotFound]     = "Item not found";
    GetDescriptions()[menuErrSameId]       = "Item exist (same id)";
    GetDescriptions()[menuErrTooManyItems] = "Too many items";
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__

