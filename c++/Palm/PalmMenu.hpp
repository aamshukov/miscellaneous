////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PALM_MENU_H__
#define __PALM_MENU_H__

#ifdef __PALM_OS__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class PalmMenu
// ----- --------
class __DECLSPEC__ PalmMenu
{
    private:
     MenuBarType*   Menu;
    protected:
     void           LoadErrorDescriptions();
    public:
     // ctor/dtor
                    PalmMenu(MenuBarType* = null);
     virtual       ~PalmMenu();

     // operators
                    operator MenuBarType* ();
                    operator const MenuBarType* ()  const;

     // api
     bool           IsValid()                       const;
     void           Attach();
     void           Detach();

     bool           Init(uint16);
     void           Dispose();

     MenuBarType*   GetActiveMenu();
     MenuBarType*   SetActiveMenu();

     static void    SetActiveMenuRscID(uint16);

     void           DrawMenu();
     void           EraseStatus();

     Err            AddItem(uint16, uint16, char, const char*);
     bool           ShowItem(uint16);
     bool           HideItem(uint16);

     static Err     CmdBarAddButton(uint8, uint16, MenuCmdBarResultType, uint32, char*);
     static bool    CmdBarGetButtonData(int16, uint16&, MenuCmdBarResultType&, uint32&, char*);
     static void    CmdBarDisplay();

     bool           HandleEvent(EventType&, uint16&);

    public:

    class __DECLSPEC__ XPalmMenu : public PalmError
    {
        public:

        enum EErrors
        {
            // appErrorClass+'menu'
        };

        protected:
         virtual void LoadErrorDescriptions();
    };

    friend class XPalmMenu;
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__
#endif // __PALM_MENU_H__
