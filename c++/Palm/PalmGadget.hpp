////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PALM_GADGET_H__
#define __PALM_GADGET_H__

#ifdef __PALM_OS__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
#if __PALM_OS__ >= 0x0500
typedef FormType _form_gadget_type;
#else
typedef FormGadgetType _form_gadget_type;
#endif

#define DECLARE_GADGET_HANDLER_STRUCTURE(_class)                                       \
    enum EGadgetSignature                                                              \
    {                                                                                  \
        eSigGadgetTrailHandler = 0,                                                    \
        eSigGadgetEventHandler                                                         \
    };                                                                                 \
    class _class;                                                                      \
    typedef void (_class::*_GadgetHandler)(void);                                      \
    struct _GadgetEntry                                                                \
    {                                                                                  \
        uint32           Command;                                                      \
        EGadgetSignature Signature;                                                    \
       _GadgetHandler    Handler;                                                      \
    };                                                                                 \
    struct _GadgetEventMap                                                             \
    {                                                                                  \
        const _GadgetEventMap* BaseMap;                                                \
        const _GadgetEntry*    Entries;                                                \
    };                                                                                 \
    typedef std::map<uint16, _class*> _Gadgets;                                        \
    union _GadgetEventMapFunctions                                                     \
    {                                                                                  \
       _GadgetHandler GenHandler;                                                      \
        bool (_class::*EventHandler)(_form_gadget_type&, void*);                       \
    };                                                                                 \

#define DECLARE_GADGET_EVENT_MAP()                                                     \
    private:                                                                           \
     static const  _GadgetEntry     EventEntries[];                                    \
    protected:                                                                         \
     static const  _GadgetEventMap  EventMap;                                          \
    protected:                                                                         \
     virtual const _GadgetEventMap* GetEventMap() const;                               \

#define GADGET_EVENT_MAP_BASE(_class)                                                  \
    const _GadgetEventMap* _class::GetEventMap() const                                 \
    {                                                                                  \
        return &_class::EventMap;                                                      \
    }                                                                                  \
    const _GadgetEventMap _class::EventMap =                                           \
    { null, null };                                                                    \
    const _GadgetEntry _class::EventEntries[] =                                        \
    {                                                                                  \
        { 0, eSigGadgetTrailHandler, reinterpret_cast<_GadgetHandler>(0) }             \
    };                                                                                 \

#define BEGIN_GADGET_EVENT_MAP(_class, _base_class)                                    \
    const _GadgetEventMap* _class::GetEventMap() const                                 \
    {                                                                                  \
        return &_class::EventMap;                                                      \
    }                                                                                  \
    const _EventMap _class::EventMap =                                                 \
    { &_base_class::EventMap, &_class::EventEntries[0] };                              \
    const _GadgetEntry _class::EventEntries[] =                                        \
    {                                                                                  \

#define END_GADGET_EVENT_MAP(_class)                                                   \
        { 0, eSigGadgetTrailHandler, reinterpret_cast<_GadgetHandler>(0) }             \
    };                                                                                 \
                                                                                       
#define GADGET_EVENT_HANDLER(_class, _event, _handler)                                 \
    { _event, eSigGadgetEventHandler,                                                  \
        (_GadgetHandler)(bool (_class::*)(_form_gadget_type&, void*))&_handler },      \
////////////////////////////////////////////////////////////////////////////////////////
// class PalmGadget
// ----- ----------
DECLARE_GADGET_HANDLER_STRUCTURE(PalmGadget)
//
class __DECLSPEC__ PalmGadget
{
    private:
     static _Gadgets        Gadgets;
     uint16                 ControlId;
    protected:
     const _GadgetEntry*    FindEntry(uint32);

     DECLARE_GADGET_EVENT_MAP()

     virtual bool           Setup()                     = 0;
     virtual bool           Finalize()                  = 0;

     static void            AddGadget(uint16, PalmGadget*);
     static void            RemoveGadget(uint16);
    public:
     // ctor/dtor
                            PalmGadget(uint16);
     virtual               ~PalmGadget();

     // access
     uint16                 GetControlId()              const;
     void                   SetControlId(uint16);

     // api
#if __PALM_OS__ >= 0x0500
     static Boolean         DispatchEvent(FormGadgetTypeInCallback*, UInt16, void*); // palm os compliant
#else
     static Boolean         DispatchEvent(FormGadgetType*, UInt16, void*);           // palm os compliant
#endif

    public:

    class __DECLSPEC__ XPalmGadget : public PalmError
    {
        public:

        enum EErrors
        {
            eSetupError = appErrorClass+'gdgt',
            eFinalizeError,
            eUnableDispatchEvent,
            eUnableAddGadget,
            eUnableRemoveGadget
        };

        protected:
         virtual void LoadErrorDescriptions();
    };

    friend class XPalmGadget;
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__
#endif // __PALM_GADGET_H__

