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

#ifndef __PALM_FORM_INC__
#   include <PalmForm.inc>
#endif

#ifdef __PALM_OS__

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class PalmForm
// ----- --------
BEGIN_EVENT_MAP(PalmForm, PalmEventManager)
    EVENT_HANDLER(PalmForm, frmOpenEvent,  EvOpen)
    EVENT_HANDLER(PalmForm, frmCloseEvent, EvClose)
END_EVENT_MAP(PalmForm)

PalmForm::PalmForm(uint16 _id)
        : PalmEventManager(_id)
{
}

PalmForm::~PalmForm()
{
}

bool PalmForm::Pretranslate(EventType&)
{
    return false;
}

bool PalmForm::Setup()
{
    return true;
}

bool PalmForm::Finalize()
{
    return true;
}

bool PalmForm::LoadForm()
{
  ::FrmGotoForm(ControlId);
    return true;
}

bool PalmForm::PopupForm()
{
  ::FrmPopupForm(ControlId);
    return true;
}

bool PalmForm::EvOpen(EventType&)
{
    FormType* form = ::FrmGetActiveForm();

    if(form != null)
    {
        if(Setup())
        {
          ::FrmDrawForm(form);
            return true;
        }
    }
    return false;
}

bool PalmForm::EvClose(EventType&)
{
    return Finalize();
}

bool PalmForm::AttachGadget(uint16 _gadget_id)
{
    FormType* form = ::FrmGetActiveForm();

    if(form != null)
    {
        uint16 index = ::FrmGetObjectIndex(form, _gadget_id);

        if(index == frmInvalidObjectId)
        {
            return false;
        }

      ::FrmSetGadgetHandler(form, index, PalmGadget::DispatchEvent);
        return true;
    }
    return false;
}
////////////////////////////////////////////////////////////////////////////////////////
// class XPalmForm
// ----- ---------
void PalmForm::XPalmForm::LoadErrorDescriptions()
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

