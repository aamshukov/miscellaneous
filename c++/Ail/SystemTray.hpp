////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __SYSTEMTRAY_H__
#define __SYSTEMTRAY_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class SystemTray
// ----- ----------
class __DECLSPEC__ SystemTray
{
    private:
     bool               Valid;
     bool               Visible;

     NOTIFYICONDATA     Data;
    protected:
     virtual LRESULT    OnTrayNotification(WPARAM, LPARAM);
    public:
                        SystemTray();
                        SystemTray(HWND, uint, const tchar*, HICON, uint);
     virtual           ~SystemTray();

     void               Init(HWND, uint, const tchar*, HICON, uint, bool = true);

     bool               IsValid()                           const;
     bool               IsVisible()                         const;

     NOTIFYICONDATA&    GetData()                           const;

     HICON              GetIcon()                           const;
     bool               SetIcon(HICON);
     bool               SetIcon(const tchar*);
     bool               SetIcon(uint);
     bool               SetSystemIcon(const tchar*);
     bool               SetSystemIcon(uint);
     void               ShowIcon(bool = true);
     void               MoveToRight();
     void               RemoveIcon();

     bool               SetTooltipText(const tchar*);
     TCharStr           GetTooltipText()                    const;

     HWND               GetNotificationWnd()                const;
     bool               SetNotificationWnd(HWND);
    public:

    class __DECLSPEC__ XSystemTray : public X
    {
        public:

        enum EFlag
        {
            NotSupported        = 0x00000100,
            BadWindow           = 0x00000200,
            BadCallbackMessage  = 0x00000400,
            BadToolTipText      = 0x00000800,
            AddIcon             = 0x00001000
        };

        public:
            XSystemTray(uint = X::Failure);
    };

    friend class XSystemTray;
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __SYSTEMTRAY_H__
