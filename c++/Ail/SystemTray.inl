////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __SYSTEMTRAY_INL__
#define __SYSTEMTRAY_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class SystemTray
// ----- ----------
__INLINE__ bool SystemTray::IsValid() const
{
    return Valid;
}

__INLINE__ bool SystemTray::IsVisible() const
{
    return Visible;
}

__INLINE__ NOTIFYICONDATA& SystemTray::GetData() const
{
    return (NOTIFYICONDATA&)Data;
}

__INLINE__ HICON SystemTray::GetIcon() const
{
    return Data.hIcon;
}

__INLINE__ bool SystemTray::SetIcon(HICON hicon)
{
    if(hicon)
    {
        Data.uFlags = NIF_ICON;
        Data.hIcon  = hicon;
    
        return ::Shell_NotifyIcon(NIM_MODIFY, &Data) > 0;
    }
    return false;
}

__INLINE__ bool SystemTray::SetIcon(const tchar* icon_name)
{
    if(icon_name)
    {
        return SetIcon(AfxGetApp()->LoadIcon(icon_name));
    }
    return false;
}

__INLINE__ bool SystemTray::SetIcon(uint id)
{
    if(id)
    {
        return SetIcon(AfxGetApp()->LoadIcon(id));
    }
    return false;
}

__INLINE__ bool SystemTray::SetSystemIcon(const tchar* icon_name)
{
    if(icon_name)
    {
        return SetIcon(::LoadIcon(null, icon_name));
    }
    return false;
}

__INLINE__ bool SystemTray::SetSystemIcon(uint id)
{
    if(id)
    {
        return SetIcon(::LoadIcon(null, MAKEINTRESOURCE(id)));
    }
    return false;
}

__INLINE__ void SystemTray::ShowIcon(bool show)
{
    if(Visible != show)
    {
        Data.uFlags = NIF_ICON | (show ? (NIF_MESSAGE | NIF_TIP) : 0);
      ::Shell_NotifyIcon(show ? NIM_ADD : NIM_DELETE, &Data);
        Visible = show;
    }
}

__INLINE__ void SystemTray::MoveToRight()
{
    ShowIcon(false);
    ShowIcon(true);
}

__INLINE__ void SystemTray::RemoveIcon()
{
    Data.uFlags = 0;
  ::Shell_NotifyIcon(NIM_DELETE, &Data);
    Visible = false;
}

__INLINE__ bool SystemTray::SetTooltipText(const tchar* tooltip_text)
{
    Data.uFlags = NIF_TIP;
    StrCopy(Data.szTip, tooltip_text);
    return ::Shell_NotifyIcon(NIM_MODIFY, &Data) > 0;
}

__INLINE__ TCharStr SystemTray::GetTooltipText() const
{
    return TCharStr(Data.szTip);
}

__INLINE__ HWND SystemTray::GetNotificationWnd() const
{
    return Data.hWnd;
}

__INLINE__ bool SystemTray::SetNotificationWnd(HWND hwnd)
{
    if(!hwnd || !::IsWindow(hwnd))
    {
        throw SystemTray::XSystemTray(XSystemTray::BadWindow);
    }

    Data.hWnd   = hwnd;
    Data.uFlags = 0;
    return ::Shell_NotifyIcon(NIM_MODIFY, &Data) > 0;
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __SYSTEMTRAY_INL__
