////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __AIL_H__
#   include <ail.hpp>
#endif

#ifndef __PALM_EVENT_INC__
#   include <PalmEvent.inc>
#endif

#ifdef __PALM_OS__

using namespace std;

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class PalmEventManager
// ----- ----------------
_Forms PalmEventManager::Forms;
//
EVENT_MAP_BASE(PalmEventManager)
//
PalmEventManager::PalmEventManager(uint16 _id)
                : ControlId(_id)
{
    PalmEventManager::AddForm(ControlId, this);
}

PalmEventManager::~PalmEventManager()
{
    PalmEventManager::RemoveForm(ControlId);
}

bool PalmEventManager::Pretranslate(EventType&)
{
    return false;
}

Boolean PalmEventManager::DispatchEvent(EventType* _event)
{
    bool rc = false;
    
    if(_event != null)
    {
        try
        {
            FormType* form = ::FrmGetActiveForm();

            if(form != null)
            {
#ifdef ALLOW_ACCESS_TO_INTERNALS_OF_FORMS
               _Forms::const_iterator it = Forms.find(form->formId);
#else
               _Forms::const_iterator it = Forms.find(::FrmGetActiveFormID());
#endif
                if(it != Forms.end())
                {
                    PalmEventManager* pform = (*it).second;

                    if(pform != null)
                    {
                        if(!pform->Pretranslate(*_event))
                        {
                           _Entry* e = const_cast<_Entry*>(pform->FindEntry(_event->eType));

                            if(e != null && e->Handler != null)
                            {
                                union _EventMapFunctions emf;
                                emf.GenHandler = e->Handler;

                                if(_event->eType == menuEvent)
                                {
                                    // commands
                                    if(e->Signature == eSigCommandHandler)
                                    {
                                        (pform->*emf.CommandHandler)(_event->data.menu.itemID);
                                        rc = true;
                                    }
                                }
                                else
                                {
                                    // regular events
                                    if(e->Signature == eSigEventHandler)
                                    {
                                        rc = (pform->*emf.EventHandler)(*_event);
                                    }
                                }
                            }
                        }
                    }
                }

                rc = ::FrmHandleEvent(form, _event);
            }
        }
        catch(...)
        {
            palmxassert(0, XPalmEventManager::eUnableDispatchEvent, PalmEventManager::XPalmEventManager);
        }
    }
    return rc;
}

const _Entry* PalmEventManager::FindEntry(uint32 _event_type)
{
    for(const _EventMap* map = GetEventMap(); map != null; map = map->BaseMap)
    {
        // no BEGIN_EVENT_MAP(myclass, myclass) !
        palmxassert(map != map->BaseMap, Error::eTypeMismatch, PalmEventManager::XPalmEventManager);
        //
        const _Entry* p_entry = map->Entries;

        // agil - to avoid simulator exception
        if(p_entry == null)
        {
            return null;
        }

        while(p_entry->Signature != eSigTrailHandler)
        {
            if(p_entry->Event == _event_type)
            {
                return p_entry;
            }
            p_entry++;
        }
    }
    return null;
}

void PalmEventManager::AddForm(uint16 _id, PalmEventManager* _form)
{
    try
    {
        if(Forms.find(_id) == Forms.end())
        {
            Forms[_id] = _form;
        }
    }
    catch(...)
    {
        palmxassert(0, XPalmEventManager::eUnableAddForm, PalmEventManager::XPalmEventManager);
    }
}

void PalmEventManager::RemoveForm(uint16 _id)
{
    try
    {
        if(Forms.find(_id) != Forms.end())
        {
            Forms.erase(_id);
        }
    }
    catch(...)
    {
        palmxassert(0, XPalmEventManager::eUnableRemoveForm, PalmEventManager::XPalmEventManager);
    }
}
////////////////////////////////////////////////////////////////////////////////////////
// class XPalmEventManager
// ----- -----------------
void PalmEventManager::XPalmEventManager::LoadErrorDescriptions()
{
    // base class
    PalmError::LoadErrorDescriptions();

    GetDescriptions()[eUnableDispatchEvent] = "Unable to dispatch an event";
    GetDescriptions()[eUnableAddForm]       = "Unable to add a form";
    GetDescriptions()[eUnableRemoveForm]    = "Unable to remove a form";
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__

