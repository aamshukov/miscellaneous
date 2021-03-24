////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PALM_EVENT_H__
#define __PALM_EVENT_H__

#ifdef __PALM_OS__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// event macros
// ----- ------
#define DECLARE_HANDLER_STRUCTURE(_class)                                              \
    enum ESignature                                                                    \
    {                                                                                  \
        eSigTrailHandler = 0,                                                          \
        eSigEventHandler,                                                              \
        eSigCommandHandler                                                             \
    };                                                                                 \
    class _class;                                                                      \
    typedef void (_class::*_Handler)(void);                                            \
    struct _Entry                                                                      \
    {                                                                                  \
        uint32      Event;                                                             \
        ESignature  Signature;                                                         \
       _Handler     Handler;                                                           \
    };                                                                                 \
    struct _EventMap                                                                   \
    {                                                                                  \
        const _EventMap* BaseMap;                                                      \
        const _Entry*    Entries;                                                      \
    };                                                                                 \
    typedef std::map<uint16, _class*> _Forms;                                          \
    union _EventMapFunctions                                                           \
    {                                                                                  \
       _Handler GenHandler;                                                            \
        bool (_class::*EventHandler)(EventType&);                                      \
        void (_class::*CommandHandler)(uint16);                                        \
    };                                                                                 \

#define DECLARE_EVENT_MAP()                                                            \
    private:                                                                           \
     static const  _Entry       EventEntries[];                                        \
    protected:                                                                         \
     static const  _EventMap    EventMap;                                              \
    protected:                                                                         \
     virtual const _EventMap*   GetEventMap() const;                                   \

#define EVENT_MAP_BASE(_class)                                                         \
    const _EventMap* _class::GetEventMap() const                                       \
    {                                                                                  \
        return &_class::EventMap;                                                      \
    }                                                                                  \
    const _EventMap _class::EventMap =                                                 \
    { null, null };                                                                    \
    const _Entry _class::EventEntries[] =                                              \
    {                                                                                  \
        { 0, eSigTrailHandler, reinterpret_cast<_Handler>(0) }                         \
    };                                                                                 \

#define BEGIN_EVENT_MAP(_class, _base_class)                                           \
    const _EventMap* _class::GetEventMap() const                                       \
    {                                                                                  \
        return &_class::EventMap;                                                      \
    }                                                                                  \
    const _EventMap _class::EventMap =                                                 \
    { &_base_class::EventMap, &_class::EventEntries[0] };                              \
    const _Entry _class::EventEntries[] =                                              \
    {                                                                                  \

#define END_EVENT_MAP(_class)                                                          \
        { 0, eSigTrailHandler, reinterpret_cast<_Handler>(0) }                         \
    };                                                                                 \
                                                                                       
#define EVENT_HANDLER(_class, _event, _handler)                                        \
    { _event, eSigEventHandler,                                                        \
        (_Handler)(bool (_class::*)(EventType&))&_class::_handler },                   \

#define COMMAND_HANDLER(_command, _handler)                                            \
    { _event, eSigCommandHandler,                                                      \
        (_Handler)(void (_class::*)(uint16))&_class::_handler },                       \

// agil - change _command to _class, change _event to menuEvent
#define COMMAND_HANDLER2(_class, _handler)                                             \
    { menuEvent, eSigCommandHandler,                                                   \
        (_Handler)(void (_class::*)(uint16))&_class::_handler },                       \
////////////////////////////////////////////////////////////////////////////////////////
// class PalmEventManager
// ----- ----------------
DECLARE_HANDLER_STRUCTURE(PalmEventManager)
//
class __DECLSPEC__ PalmEventManager
{
    protected:
     static _Forms          Forms;
     uint16                 ControlId;
    protected:
     const _Entry*          FindEntry(uint32);
     virtual bool           Pretranslate(EventType&);

     DECLARE_EVENT_MAP()

     virtual bool           Setup()                     = 0;
     virtual bool           Finalize()                  = 0;
    public:
     // ctor/dtor
                            PalmEventManager(uint16);
     virtual               ~PalmEventManager();

     // access
     uint16                 GetControlId()              const;
     void                   SetControlId(uint16);

     // api
     static Boolean         DispatchEvent(EventType*); // palm os compliant
     static void            AddForm(uint16, PalmEventManager*);
     static void            RemoveForm(uint16);

    public:
    
    class __DECLSPEC__ XPalmEventManager : public PalmError
    {
        public:

        enum EErrors
        {
            eUnableDispatchEvent = appErrorClass+'evmg',
            eUnableAddForm,
            eUnableRemoveForm
        };

        protected:
         virtual void LoadErrorDescriptions();
    };

    friend class XPalmEventManager;
};
////////////////////////////////////////////////////////////////////////////////////////
// before preprocessing
// ------ -------------
// BEGIN_EVENT_MAP(PalmForm, PalmEventManager)
//     EVENT_HANDLER(PalmForm, frmOpenEvent,  EvOpen)
//     EVENT_HANDLER(PalmForm, frmCloseEvent, EvClose)
// END_EVENT_MAP(PalmForm)
//
// after preprocessing
// ----- -------------
// const _EventMap* PalmForm::GetEventMap() const
// {
//     return &PalmForm::EventMap;
// }
// 
// const _EventMap PalmForm::EventMap = { &PalmEventManager::EventMap, &PalmForm::EventEntries[0] };
// 
// const _Entry PalmForm::EventEntries[] =
// {
//     { frmOpenEvent,  eSigEventHandler, (_Handler)(bool (PalmForm::*)(EventType&))&EvOpen  },
//     { frmCloseEvent, eSigEventHandler, (_Handler)(bool (PalmForm::*)(EventType&))&EvClose },
//     { 0,             eSigTrailHandler, reinterpret_cast<_Handler>(0)                      }
// };
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__
#endif // __PALM_EVENT_H__

