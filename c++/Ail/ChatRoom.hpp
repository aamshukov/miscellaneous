////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __CHAT_ROOM_H__
#define __CHAT_ROOM_H__

#pragma once

__BEGIN_NAMESPACE__
__BEGIN_RRT_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class ChatRoom
// ----- --------
class __DECLSPEC__ ChatRoom
{
    typedef AutoPtrArray<tchar> _Array;

    private:
     uint           ID;
    _Array          Subject;
    private:
                    ChatRoom(const ChatRoom&);
     ChatRoom&      operator = (const ChatRoom&);
    public:
     // ctor/dtor
                    ChatRoom(uint, const tchar* = null);
     virtual       ~ChatRoom();

     // access
     uint           GetID()                     const;
     void           SetID(uint);

     const tchar*   GetSubject()                const;
     void           SetSubject(const tchar*);
};
////////////////////////////////////////////////////////////////////////////////////////
__END_RRT_NAMESPACE__
__END_NAMESPACE__

#endif // __CHAT_ROOM_H__
