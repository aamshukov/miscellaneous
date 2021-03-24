////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PALM_ALERT_INL__
#define __PALM_ALERT_INL__

#ifdef __PALM_OS__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class PalmAlert
// ----- ---------
__INLINE__ uint16 PalmAlert::GetControlID() const
{
    return ControlID;
}

__INLINE__ void PalmAlert::SetControlID(uint16 _id)
{
    ControlID = _id;
}

__INLINE__ uint16 PalmAlert::Alert()
{
    palmxassert(ControlID != PalmOS::eUnknownCtrlID, PalmError::eUnknownCtrl, PalmAlert::XPalmAlert);
    return ::FrmAlert(ControlID);
}

__INLINE__ uint16 PalmAlert::CustomAlert()
{
    palmxassert(ResourceID != 0, PalmError::eUnknownRes, PalmAlert::XPalmAlert);
    return ::FrmCustomAlert(ResourceID, M1 != null ? M1 : PalmOS::StringStub,
                                        M2 != null ? M2 : PalmOS::StringStub,
                                        M3 != null ? M3 : PalmOS::StringStub);
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__
#endif // __PALM_ALERT_INL__
