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

#ifndef __SYSTEMTRAY_INC__
#   include <SystemTray.inc>
#endif

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class SystemTray
// ----- ----------
SystemTray::SystemTray()
{
    Visible = false;

    InitMemory(&Data, sizeof(Data));
}

SystemTray::SystemTray(HWND hwnd, uint callback_message, const tchar* tooltip_text, HICON hicon, uint id)
{
    Init(hwnd, callback_message, tooltip_text, hicon, id);

    Visible = true;
}

void SystemTray::Init(HWND hwnd, uint callback_message, const tchar* tooltip_text, HICON hicon, uint id, bool show)
{
    const short tooltip_text_size = 64;

    if((::GetVersion() & 0xFF) < 4)
    {
        throw SystemTray::XSystemTray(XSystemTray::NotSupported);
    }

    if(!hwnd || !::IsWindow(hwnd))
    {
        throw SystemTray::XSystemTray(XSystemTray::BadWindow);
    }
    
    if(callback_message < WM_USER)
    {
        throw SystemTray::XSystemTray(XSystemTray::BadCallbackMessage);
    }

    if(tooltip_text == null || StrLen(tooltip_text) > tooltip_text_size)
    {
        throw SystemTray::XSystemTray(XSystemTray::BadToolTipText);
    }

    Data.cbSize           = sizeof(NOTIFYICONDATA);
    Data.hWnd             = hwnd;
    Data.uID              = id;
    Data.hIcon            = hicon;
    Data.uFlags           = NIF_MESSAGE | NIF_ICON | NIF_TIP;
    Data.uCallbackMessage = callback_message;

    StrCopy(Data.szTip, tooltip_text);

    if(show)
    {
        if(!::Shell_NotifyIcon(NIM_ADD, &Data))
        {
            throw SystemTray::XSystemTray(XSystemTray::AddIcon);
        }
    }

    Valid = true;
}

SystemTray::~SystemTray()
{
    RemoveIcon();
}

LRESULT SystemTray::OnTrayNotification(WPARAM wParam, LPARAM lParam) 
{
    if(wParam != Data.uID)
    {
        return 0;
    }

    // LOWORD(lParam) is: WM_LBUTTONUP, WM_RBUTTONUP, WM_MOSEMOVE and so on ...
    return 1;
}

SystemTray::XSystemTray::XSystemTray(uint _error) : X(_error)
{
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__
