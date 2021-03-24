////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __CHAT_ROOM_INL__
#define __CHAT_ROOM_INL__

#pragma once

__BEGIN_NAMESPACE__
__BEGIN_RRT_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class ChatRoom
// ----- --------
__INLINE__ uint ChatRoom::GetID() const
{
    return ID;
}

__INLINE__ void ChatRoom::SetID(uint _id)
{
    ID = _id;
}

__INLINE__ const tchar* ChatRoom::GetSubject() const
{
    return Subject;
}

__INLINE__ void ChatRoom::SetSubject(const tchar* _subject)
{
    Subject = StrClone(_subject);
}
////////////////////////////////////////////////////////////////////////////////////////
__END_RRT_NAMESPACE__
__END_NAMESPACE__

#endif // __CHAT_ROOM_INL__
