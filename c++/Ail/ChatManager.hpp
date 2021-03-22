////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __CHAT_MANAGER_H__
#define __CHAT_MANAGER_H__

#pragma once

__BEGIN_NAMESPACE__
__BEGIN_RRT_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class ChatManager
// ----- -----------
class __DECLSPEC__ ChatManager : public RRManager, public Singleton<ChatManager>
{
    public:

    enum EType
    {
        TrChatMessage      = 'cmsg',
        TrInviteToChat     = 'invt',
        TrRejectChatInvite = 'rjin',
        TrJoinChat         = 'jnch',
        TrLeaveChat        = 'lvch',
        TrCloseChat        = 'clsc',
        TrUserJoined       = 'usrj',
        TrGetChatSubject   = 'gsbj',
        TrSetChatSubject   = 'ssbj'
    };

    public:
     // ctor/dtor
                    ChatManager();
     virtual       ~ChatManager();

     // protocol
     virtual bool   CanHandle(const RRTransaction*);
     virtual void   Process(const RRTransaction*);
};
////////////////////////////////////////////////////////////////////////////////////////
__END_RRT_NAMESPACE__
__END_NAMESPACE__

#endif // __CHAT_MANAGER_H__
