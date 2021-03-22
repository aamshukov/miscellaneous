////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PALM_NOTIFICATION_HANDLER_H__
#define __PALM_NOTIFICATION_HANDLER_H__

#ifdef __PALM_OS__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// notification macros
// ------------ ------
#define DECLARE_NOTIFICATION_HANDLER_STRUCTURE(_class)                                 \
    enum ENtfSignature                                                                 \
    {                                                                                  \
        eSigNtfTrailHandler = 0,                                                       \
        eSigNtfHandler                                                                 \
    };                                                                                 \
    class _class;                                                                      \
    typedef void (_class::*_NtfHandler)(void);                                         \
    struct _NtfEntry                                                                   \
    {                                                                                  \
        uint32        Notification;                                                    \
        ENtfSignature Signature;                                                       \
       _NtfHandler    Handler;                                                         \
    };                                                                                 \
    struct _NotificationMap                                                            \
    {                                                                                  \
        const _NotificationMap* BaseMap;                                               \
        const _NtfEntry*        Entries;                                               \
    };                                                                                 \
    union _NotificationMapFunctions                                                    \
    {                                                                                  \
       _NtfHandler GenHandler;                                                         \
        Err (_class::*NotificationHandler)(SysNotifyParamType&);                       \
    };                                                                                 \

#define DECLARE_NOTIFICATION_MAP()                                                     \
    private:                                                                           \
     static const  _NtfEntry            NotificationEntries[];                         \
    protected:                                                                         \
     static const  _NotificationMap     NotificationMap;                               \
    protected:                                                                         \
     virtual const _NotificationMap*    GetNotificationMap() const;                    \

#define NOTIFICATION_MAP_BASE(_class)                                                  \
    const _NotificationMap* _class::GetNotificationMap() const                         \
    {                                                                                  \
        return &_class::NotificationMap;                                               \
    }                                                                                  \
    const _NotificationMap _class::NotificationMap =                                   \
    { null, null };                                                                    \
    const _NtfEntry _class::NotificationEntries[] =                                    \
    {                                                                                  \
        { 0, eSigNtfTrailHandler, reinterpret_cast<_NtfHandler>(0) }                   \
    };                                                                                 \

#define BEGIN_NOTIFICATION_MAP(_class, _base_class)                                    \
    const _NotificationMap* _class::GetNotificationMap() const                         \
    {                                                                                  \
        return &_class::NotificationMap;                                               \
    }                                                                                  \
    const _NotificationMap _class::NotificationMap =                                   \
    { &_base_class::NotificationMap, &_class::NotificationEntries[0] };                \
    const _NtfEntry _class::NotificationEntries[] =                                    \
    {                                                                                  \

#define END_NOTIFICATION_MAP(_class)                                                   \
        { 0, eSigNtfTrailHandler, reinterpret_cast<_NtfHandler>(0) }                   \
    };                                                                                 \
                                                                                       
#define NOTIFICATION_HANDLER(_class, _notification, _handler)                          \
    { _notification, eSigNtfHandler,                                                   \
        (_NtfHandler)(Err (_class::*)(SysNotifyParamType&))&_handler },                \
////////////////////////////////////////////////////////////////////////////////////////
class PalmNotificationClient;
////////////////////////////////////////////////////////////////////////////////////////
// class PalmNotificationHandler
// ----- -----------------------
class __DECLSPEC__ PalmNotificationHandler //: public PalmSingleton
{
    // should be only one instance, let's say singleton ...
    typedef std::map<uint16, PalmNotificationClient*> _Clients;

    private:
     static _Clients    Clients;
    protected:
     static Err         DispatchNotification(SysNotifyParamType*); // palm os compliant
    public:
     // ctor/dtor
                        PalmNotificationHandler();
     virtual           ~PalmNotificationHandler();

     // api
     static void        AddClient(uint16, PalmNotificationClient*);
     static void        RemoveClient(uint16);

     static Err         Register(uint16, LocalID, uint32, int8, void* = null);
     static Err         Unregister(uint16, LocalID, uint32, int8);

     static Err         Broadcast(SysNotifyParamType&);
     static Err         BroadcastDeferred(SysNotifyParamType&, int16);

#if (__PALM_OS__ >= 0x0400)
     static Err         BroadcastFromInterrupt(uint32, uint32, void* = null);
#endif

    public:

    class __DECLSPEC__ XPalmNotificationHandler : public PalmError
    {
        public:

        enum EErrors
        {
            eUnableDispatchNotification = appErrorClass+'ntfc',
            eUnableAddClient,
            eUnableRemoveClient
        };

        protected:
         virtual void LoadErrorDescriptions();
    };

    friend class XPalmNotificationHandler;
};
////////////////////////////////////////////////////////////////////////////////////////
// class PalmNotificationClient
// ----- ----------------------
DECLARE_NOTIFICATION_HANDLER_STRUCTURE(PalmNotificationClient)
//
class __DECLSPEC__ PalmNotificationClient
{
    friend class PalmNotificationHandler;

    private:
     uint16             ClientID;
    protected:
     const _NtfEntry*   FindEntry(uint32);

     DECLARE_NOTIFICATION_MAP()
    public:
     // ctor/dtor
                        PalmNotificationClient(uint16);
     virtual           ~PalmNotificationClient();

     // access
     uint16             GetClientID()           const;
     void               SetClientID(uint16);
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__
#endif // __PALM_NOTIFICATION_HANDLER_H__

