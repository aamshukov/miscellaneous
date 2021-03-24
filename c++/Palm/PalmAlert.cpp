////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __AIL_H__
#   include <ail.hpp>
#endif

#ifndef __PALM_ALERT_INC__
#   include <PalmAlert.inc>
#endif

#ifdef __PALM_OS__

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class PalmAlert
// ----- ---------
PalmAlert::PalmAlert(uint16 _res_id, const char* _m1, const char* _m2, const char* _m3)
         : M1(const_cast<char*>(_m1)),
           M2(const_cast<char*>(_m2)),
           M3(const_cast<char*>(_m3)),
           ControlID(PalmOS::eUnknownCtrlID),
           ResourceID(_res_id)
{
}

PalmAlert::~PalmAlert()
{
}
////////////////////////////////////////////////////////////////////////////////////////
// class XPalmAlert
// ----- ----------
void PalmAlert::XPalmAlert::LoadErrorDescriptions()
{
    // base class
    PalmError::LoadErrorDescriptions();
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__

