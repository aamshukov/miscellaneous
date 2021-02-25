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

#ifndef __PALM_DIALOG_INC__
#   include <PalmDialog.inc>
#endif

#ifdef __PALM_OS__

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class PalmDialog
// ----- ----------
BEGIN_EVENT_MAP(PalmDialog, PalmEventManager)
END_EVENT_MAP(PalmDialog)

PalmDialog::PalmDialog(uint16 _id)
          : PalmEventManager(_id)
{
}

PalmDialog::~PalmDialog()
{
}

bool PalmDialog::Pretranslate(EventType&)
{
    return false;
}

bool PalmDialog::Setup()
{
    return true;
}

bool PalmDialog::Finalize()
{
    return true;
}

uint16 PalmDialog::DoDialog()
{
    uint16 rc = Error::eInvalidArg;

    if(ControlId != PalmOS::eUnknownCtrlID)
    {
        try
        {
            FormType* prev_form = ::FrmGetActiveForm();
            FormType* form = ::FrmInitForm(ControlId);
        
            if(form != null)
            {
                PalmEventManager::AddForm(ControlId, this);
              ::FrmSetEventHandler(form, PalmEventManager::DispatchEvent);
              ::FrmSetActiveForm(form);

                if(!Setup())
                {
                    rc = XPalmDialog::eSetupError;
                }

                rc = ::FrmDoDialog(form);

                if(!Finalize())
                {
                    rc = XPalmDialog::eFinalizeError;
                }

                // restore prev active form
                if(prev_form != null)
                {
                  ::FrmSetActiveForm(prev_form);
                }
            }
            PalmEventManager::RemoveForm(ControlId);
          ::FrmDeleteForm(form);
        }
        catch(...)
        {
            return Error::eUnknown;
        }
    }
    return rc;
}
////////////////////////////////////////////////////////////////////////////////////////
// class XPalmDialog
// ----- -----------
void PalmDialog::XPalmDialog::LoadErrorDescriptions()
{
    // base class
    PalmError::LoadErrorDescriptions();
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__

