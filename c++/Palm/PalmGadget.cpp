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

#ifndef __PALM_GADGET_INC__
#   include <PalmGadget.inc>
#endif

#ifdef __PALM_OS__

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class PalmGadget
// ----- ----------
_Gadgets PalmGadget::Gadgets;
//
GADGET_EVENT_MAP_BASE(PalmGadget)
//
PalmGadget::PalmGadget(uint16 _id)
          : ControlId(_id)
{
    PalmGadget::AddGadget(ControlId, this);
}

PalmGadget::~PalmGadget()
{
    PalmGadget::RemoveGadget(ControlId);
}

#if __PALM_OS__ >= 0x0500
Boolean PalmGadget::DispatchEvent(FormGadgetTypeInCallback* _gadget, UInt16 _command, void* _params)
#else
Boolean PalmGadget::DispatchEvent(FormGadgetType* _gadget, UInt16 _command, void* _params)
#endif
{
    bool rc = false;

    if(_gadget != null)
    {
        try
        {
            int16 index = frmInvalidObjectId;

            FormType* form = ::FrmGetActiveForm();

            if(form != null)
            {
#ifdef ALLOW_ACCESS_TO_INTERNALS_OF_FORMS
                for(uint16 i = 0, n = ::FrmGetNumberOfObjects(form); i < n; i++)
                {
                    if(::FrmGetObjectPtr(i) == _gadget)
                    {
                        index = i;
                        break;
                    }
                }
#else
                int16 index = ::FrmGetObjectIndexFromPtr(form, _gadget);
#endif
                int16 id = ::FrmGetObjectId(form, index);

               _Gadgets::const_iterator it = Gadgets.find(id);

                if(it != Gadgets.end())
                {
                    PalmGadget* pgadget = (*it).second;

                    if(pgadget != null)
                    {
                       _GadgetEntry* e = const_cast<_GadgetEntry*>(pgadget->FindEntry(_command));

                        if(e != null && e->Handler != null)
                        {
                            union _GadgetEventMapFunctions emf;
                            emf.GenHandler = e->Handler;

                            // commands
                            if(e->Signature == eSigGadgetEventHandler)
                            {
                                rc = (pgadget->*emf.EventHandler)(*form, _params);
                            }
                        }
                    }

                    rc = true;
                }
            }
        }
        catch(...)
        {
            palmxassert(0, XPalmGadget::eUnableDispatchEvent, PalmGadget::XPalmGadget);
        }
    }
    return rc;
}

const _GadgetEntry* PalmGadget::FindEntry(uint32 _command)
{
    for(const _GadgetEventMap* map = GetEventMap(); map != null; map = map->BaseMap)
    {
        // no BEGIN_EVENT_MAP(myclass, myclass) !
        palmxassert(map != map->BaseMap, Error::eTypeMismatch, PalmGadget::XPalmGadget);
        //
        const _GadgetEntry* p_entry = map->Entries;

        while(p_entry->Signature != eSigGadgetTrailHandler)
        {
            if(p_entry->Command == _command)
            {
                return p_entry;
            }
            p_entry++;
        }
    }
    return null;
}

void PalmGadget::AddGadget(uint16 _id, PalmGadget* _form)
{
    try
    {
        if(Gadgets.find(_id) == Gadgets.end())
        {
            Gadgets[_id] = _form;
        }
    }
    catch(...)
    {
        palmxassert(0, XPalmGadget::eUnableAddGadget, PalmGadget::XPalmGadget);
    }
}

void PalmGadget::RemoveGadget(uint16 _id)
{
    try
    {
        if(Gadgets.find(_id) != Gadgets.end())
        {
            Gadgets.erase(_id);
        }
    }
    catch(...)
    {
        palmxassert(0, XPalmGadget::eUnableRemoveGadget, PalmGadget::XPalmGadget);
    }
}
////////////////////////////////////////////////////////////////////////////////////////
// class XPalmGadget
// ----- -----------
void PalmGadget::XPalmGadget::LoadErrorDescriptions()
{
    // base class
    PalmError::LoadErrorDescriptions();

    // form errors
    GetDescriptions()[eSetupError]    = "An error occurs: Setup()";
    GetDescriptions()[eFinalizeError] = "An error occurs: Finalize()";
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__

