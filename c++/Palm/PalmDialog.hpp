////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  Copyright © 1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PALM_DIALOG_H__
#define __PALM_DIALOG_H__

#ifdef __PALM_OS__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class PalmDialog
// ----- ----------
class __DECLSPEC__ PalmDialog : public PalmEventManager
{
    private:
     mutable FormType*  Form;
    protected:
     virtual bool       Pretranslate(EventType&);
     virtual bool       Setup();
     virtual bool       Finalize();

     DECLARE_EVENT_MAP()
    public:
     // ctor/dtor
                        PalmDialog(uint16);
     virtual           ~PalmDialog();

     // operators
                        operator FormType* ();
                        operator const FormType* () const;

     // api
     uint16             DoDialog();

     bool               IsValid()                   const;
     void               Attach();
     void               Detach();

    public:
    
    class __DECLSPEC__ XPalmDialog : public PalmError
    {
        public:

        enum EErrors
        {
            eSetupError = appErrorClass+'ddlg',
            eFinalizeError
        };

        public:
         virtual void LoadErrorDescriptions();
    };

    friend class XPalmDialog;
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__
#endif // __PALM_DIALOG_H__
