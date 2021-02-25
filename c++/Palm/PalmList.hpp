////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  Copyright © 1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PALM_LIST_H__
#define __PALM_LIST_H__

#ifdef __PALM_OS__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class PalmList
// ----- --------
class __DECLSPEC__ PalmList : public PalmControl
{
    public:
     // ctor/dtor
                    PalmList(ListType* = null);
     virtual       ~PalmList();

     // operators
                    operator ListType* ();
                    operator const ListType* () const;

     // api
     int16          GetNumberOfItems();

     void           DrawList();
     void           EraseList();
     void           SetDrawFunction(ListDrawDataFuncType*);

     int16          GetSelection();
     void           SetSelection(int16);
     char*          GetSelectionText(int16);

     void           SetHeight(int16);

     void           SetListChoices(char**, int16);
     int16          PopupList();

     void           SetTopItem(int16);
     void           SetPosition(Coord, Coord);

     int16          GetVisibleItems();
     void           MakeItemVisible(int16);
     bool           ScrollList(WinDirectionType, int16);

     bool           HandleEvent(const EventType&);

    public:

    class __DECLSPEC__ XPalmList : public XPalmControl
    {
        public:

        enum EErrors
        {
            // appErrorClass+'list'
        };

        protected:
         virtual void LoadErrorDescriptions();
    };

    friend class XPalmList;
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__
#endif // __PALM_LIST_H__

