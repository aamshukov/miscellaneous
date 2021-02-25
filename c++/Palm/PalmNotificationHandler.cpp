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

#ifndef __PALM_NOTIFICATION_HANDLER_INC__
#   include <PalmNotificationHandler.inc>
#endif

#ifdef __PALM_OS__

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class PalmNotificationHandler
// ----- -----------------------
PalmNotificationHandler::_Clients PalmNotificationHandler::Clients;
//
PalmNotificationHandler::PalmNotificationHandler()
{
}

PalmNotificationHandler::~PalmNotificationHandler()
{
}

Err PalmNotificationHandler::DispatchNotification(SysNotifyParamType* _notification)
{
    if(_notification != null)
    {
        try
        {
           _Clients::const_iterator it = Clients.begin();

            for(; it != Clients.end(); it++)
            {
                PalmNotificationClient* client = (*it).second;

                if(client != null)
                {
                   _NtfEntry* e = const_cast<_NtfEntry*>(client->FindEntry(_notification->notifyType));

                    if(e != null && e->Handler != null)
                    {
                        union _NotificationMapFunctions emf;
                        emf.GenHandler = e->Handler;

                        if(e->Signature == eSigNtfHandler)
                        {
                            (client->*emf.NotificationHandler)(*_notification);
                        }
                    }
                }
            }
        }
        catch(...)
        {
            palmxassert(0, XPalmNotificationHandler::eUnableDispatchNotification, PalmNotificationHandler::XPalmNotificationHandler);
        }
    }
    return errNone;
}

void PalmNotificationHandler::AddClient(uint16 _id, PalmNotificationClient* _client)
{
    try
    {
        if(Clients.find(_id) == Clients.end())
        {
            Clients[_id] = _client;
        }
    }
    catch(...)
    {
        palmxassert(0, XPalmNotificationHandler::eUnableAddClient, PalmNotificationHandler::XPalmNotificationHandler);
    }
}

void PalmNotificationHandler::RemoveClient(uint16 _id)
{
    try
    {
        if(Clients.find(_id) != Clients.end())
        {
            Clients.erase(_id);
        }
    }
    catch(...)
    {
        palmxassert(0, XPalmNotificationHandler::eUnableRemoveClient, PalmNotificationHandler::XPalmNotificationHandler);
    }
}
////////////////////////////////////////////////////////////////////////////////////////
// class PalmNotificationClient
// ----- ----------------------
NOTIFICATION_MAP_BASE(PalmNotificationClient)
//
PalmNotificationClient::PalmNotificationClient(uint16 _id)
                      : ClientID(_id)
{
    PalmNotificationHandler::AddClient(ClientID, this);
}

PalmNotificationClient::~PalmNotificationClient()
{
    PalmNotificationHandler::RemoveClient(ClientID);
}

const _NtfEntry* PalmNotificationClient::FindEntry(uint32 _notification)
{
    for(const _NotificationMap* map = GetNotificationMap(); map != null; map = map->BaseMap)
    {
        // no BEGIN_EVENT_MAP(myclass, myclass) !
        palmxassert(map != map->BaseMap, Error::eTypeMismatch, Error);
        //
        const _NtfEntry* p_entry = map->Entries;

        while(p_entry->Signature != eSigNtfTrailHandler)
        {
            if(p_entry->Notification == _notification)
            {
                return p_entry;
            }
            p_entry++;
        }
    }
    return null;
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__

