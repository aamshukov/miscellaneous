////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PALM_ALERT_H__
#define __PALM_ALERT_H__

#ifdef __PALM_OS__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class PalmAlert
// ----- ---------
class __DECLSPEC__ PalmAlert
{
    private:
     char*          M1;
     char*          M2;
     char*          M3;
     uint16         ControlID;
     uint16         ResourceID;
    public:
     // ctor/dtor
                    PalmAlert(uint16, const char* = null, const char* = null, const char* = null);
     virtual       ~PalmAlert();

     // access
     uint16         GetControlID()          const;
     void           SetControlID(uint16);

     // api
     uint16         Alert();
     uint16         CustomAlert();

    public:

    class __DECLSPEC__ XPalmAlert : public PalmError
    {
        public:

        enum EErrors
        {
            // appErrorClass+'alrt'
        };

        protected:
         virtual void LoadErrorDescriptions();
    };
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__
#endif // __PALM_ALERT_H__
