////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __MAPI_H__
#define __MAPI_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class MAPIModule
// ----- ----------
class __DECLSPEC__ MAPIModule : public Module
{
    public:
                     MAPIModule();

     static bool     IsMAPIPresent();
     static bool     IsMAPIXPresent();

     static TCharStr GetDefaultMAPIProfile();
     static Module&  GetMAPIModule();

     // Simple MAPI
     static ulong    MAPILogon(ulong, const tchar*, const tchar*, uint, ulong, LHANDLE*);
     static ulong    MAPILogoff(LHANDLE, ulong, uint, ulong);
     static ulong    MAPISendMail(LHANDLE, ulong, MapiMessage*, uint, ulong);
     static ulong    MAPISendDocuments(ulong, const tchar*, const tchar*, const tchar*, ulong);
     static ulong    MAPIFindNext(LHANDLE, ulong, const tchar*, const tchar*, uint, ulong, const tchar*);
     static ulong    MAPIReadMail(LHANDLE, ulong, const tchar*, uint, ulong, MapiMessage*);
     static ulong    MAPISaveMail(LHANDLE, ulong, MapiMessage*, uint, ulong, const tchar*);
     static ulong    MAPIDeleteMail(LHANDLE, ulong, const tchar*, uint, ulong);
     static ulong    MAPIFreeBuffer(void*);
     static ulong    MAPIAddress(LHANDLE, ulong, const tchar*, ulong, const tchar*, ulong, MapiRecipDesc*, uint, ulong, ulong*, MapiRecipDesc*);
     static ulong    MAPIDetails(LHANDLE, ulong, MapiRecipDesc*, uint, ulong);
     static ulong    MAPIResolveName(LHANDLE, ulong, const tchar*, uint, ulong, MapiRecipDesc**);

     // MAPIX
     static HRESULT  MAPIInitialize(void*);
     static void     MAPIUninitialize();
     static HRESULT  MAPILogonEx(ulong, const tchar*, const tchar*, uint, IMAPISession*);
     static SCODE    MAPIAllocateBuffer(uint, void**);
     static SCODE    MAPIAllocateMore(uint, void*, void**);
     static HRESULT  MAPIAdminProfiles(uint, IProfAdmin**);
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __MAPI_H__
