////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PALM_NOTIFICATION_HANDLER_INL__
#define __PALM_NOTIFICATION_HANDLER_INL__

#ifdef __PALM_OS__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class PalmNotificationHandler
// ----- -----------------------
__INLINE__ Err PalmNotificationHandler::Register(uint16 _card_no, LocalID _db_id, uint32 _notification, int8 _priority, void* _data)
{
    return ::SysNotifyRegister(_card_no, _db_id, _notification, PalmNotificationHandler::DispatchNotification, _priority, _data);
}

__INLINE__ Err PalmNotificationHandler::Unregister(uint16 _card_no, LocalID _db_id, uint32 _notification, int8 _priority)
{
    return ::SysNotifyUnregister(_card_no, _db_id, _notification, _priority);
}

__INLINE__ Err PalmNotificationHandler::Broadcast(SysNotifyParamType& _notification)
{
    return ::SysNotifyBroadcast(&_notification);
}

__INLINE__ Err PalmNotificationHandler::BroadcastDeferred(SysNotifyParamType& _notification, int16 _size)
{
    return ::SysNotifyBroadcastDeferred(&_notification, _size);
}

#if (__PALM_OS__ >= 0x0400)
__INLINE__ Err PalmNotificationHandler::BroadcastFromInterrupt(uint32 _notification, uint32 _broadcaster, void* _details)
{
    return ::SysNotifyBroadcastFromInterrupt(_notification, _broadcaster, _details);
}
#endif
////////////////////////////////////////////////////////////////////////////////////////
// class PalmNotificationClient
// ----- ----------------------
__INLINE__ uint16 PalmNotificationClient::GetClientID() const
{
    return ClientID;
}

__INLINE__ void PalmNotificationClient::SetClientID(uint16 _id)
{
    ClientID = _id;
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__
#endif // __PALM_NOTIFICATION_HANDLER_INL__
