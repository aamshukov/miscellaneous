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

#ifndef __MAPI_INC__
#   include <MAPI.inc>
#endif

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
const tchar ConstMAPIKey[]             = _T("Software\\Microsoft\\Windows Messaging Subsystem");
const tchar ConstMAPIVal[]             = _T("MAPI");
const tchar ConstMAPIXVal[]            = _T("MAPIX");
const tchar ConstMAPIKeyProfileWin[]   = _T("Software\\Microsoft\\Windows Messaging Subsystem\\Profiles");
const tchar ConstMAPIKeyProfileWinNT[] = _T("Software\\Microsoft\\Windows NT\\CurrentVersion\\Windows Messaging Subsystem\\Profiles");
const tchar ConstMAPIProfileVal[]      = _T("DefaultProfile");
////////////////////////////////////////////////////////////////////////////////////////
// class MAPIModule
// ----- ----------
MAPIModule::MAPIModule() : Module(_t("MAPI32.DLL"))
{
}

bool MAPIModule::IsMAPIPresent()
{
    try
    {
        TCharStr key_name = ConstMAPIKey;

        RegKey key(RegKey::GetLocalMachineKey(), key_name);

        AutoPtrArray<tchar> buffer = new tchar[TEXT_SIZE_SMALL];

        uint count = TEXT_SIZE_SMALL;

        key.QueryValue(ConstMAPIVal, null, reinterpret_cast<byte*>(&buffer), &count);

        if(StrCompare(buffer, _t("1")) == 0)
        {
            return true;
        }

        return false;
    }
    catch(RegKey::XRegKey&)
    {
        return false;
    }
    catch(...)
    {
        return false;
    }
}

bool MAPIModule::IsMAPIXPresent()
{
    try
    {
        TCharStr key_name = ConstMAPIKey;
        RegKey key(RegKey::GetLocalMachineKey(), key_name);

        AutoPtrArray<tchar> buffer = new tchar[TEXT_SIZE_SMALL];
        uint count = TEXT_SIZE_SMALL;
        key.QueryValue(ConstMAPIXVal, null, (byte*)&buffer, &count);

        if(StrCompare(buffer, _t("1")) == 0)
        {
            return true;
        }

        return false;
    }
    catch(RegKey::XRegKey&)
    {
        return false;
    }
    catch(...)
    {
        return false;
    }
}

TCharStr MAPIModule::GetDefaultMAPIProfile()
{
    try
    {
        TCharStr key_name = IsWinNT() ? ConstMAPIKeyProfileWinNT : ConstMAPIKeyProfileWin;

        RegKey key(RegKey::GetCurrentUserKey(), key_name);

        const short _buffer_size_ = 64; // for profiles ! ...
        AutoPtrArray<tchar> buffer = new tchar[_buffer_size_];

        uint count = _buffer_size_;

        InitMemory(&buffer, _buffer_size_);

        key.QueryValue(ConstMAPIProfileVal, null, reinterpret_cast<byte*>(&buffer), &count);
        
        return TCharStr(buffer);
    }
    catch(RegKey::XRegKey&)
    {
        return TCharStr();
    }
    catch(...)
    {
        return TCharStr();
    }
}

Module& MAPIModule::GetMAPIModule()
{
    static MAPIModule TheModule;
    return TheModule;
}

// Simple MAPI
ulong MAPIModule::MAPILogon(ulong ui_param, const tchar* profile, const tchar* password, uint flags, ulong reserved, LHANDLE* session)
{
    const char _name[] = "MAPILogon";

    static ModuleProc6<ulong, ulong, const tchar*, const tchar*, uint, ulong, LHANDLE*> MAPILogon(GetMAPIModule(), _name);
    return MAPILogon(ui_param, profile, password, flags, reserved, session);
}

ulong MAPIModule::MAPILogoff(LHANDLE session, ulong ui_param, uint flags, ulong reserved)
{
    const char _name[] = "MAPILogoff";

    static ModuleProc4<ulong, LHANDLE, ulong, uint, ulong> MAPILogoff(GetMAPIModule(), _name);
    return MAPILogoff(session, ui_param, flags, reserved);
}

ulong MAPIModule::MAPISendMail(LHANDLE session, ulong ui_param, MapiMessage* message, uint flags, ulong reserved)
{
    const char _name[] = "MAPISendMail";

    static ModuleProc5<ulong, LHANDLE, ulong, MapiMessage*, uint, ulong> MAPISendMail(GetMAPIModule(), _name);
    return MAPISendMail(session, ui_param, message, flags, reserved);
}

ulong MAPIModule::MAPISendDocuments(ulong ui_param, const tchar* delimiter, const tchar* path, const tchar* name, ulong reserved)
{
    const char _name[] = "MAPISendDocuments";

    static ModuleProc5<ulong, ulong, const tchar*, const tchar*, const tchar*, ulong> MAPISendDocuments(GetMAPIModule(), _name);
    return MAPISendDocuments(ui_param, delimiter, path, name, reserved);
}

ulong MAPIModule::MAPIFindNext(LHANDLE session, ulong ui_param, const tchar* type, const tchar* seed_id, uint flags, ulong reserved, const tchar* id)
{
    const char _name[] = "MAPIFindNext";

    static ModuleProc7<ulong, LHANDLE, ulong, const tchar*, const tchar*, uint, ulong, const tchar*> MAPIFindNext(GetMAPIModule(), _name);
    return MAPIFindNext(session, ui_param, type, seed_id, flags, reserved, id);
}

ulong MAPIModule::MAPIReadMail(LHANDLE session, ulong ui_param, const tchar* id, uint flags, ulong reserved, MapiMessage* message)
{
    const char _name[] = "MAPIReadMail";

    static ModuleProc6<ulong, LHANDLE, ulong, const tchar*, uint, ulong, MapiMessage*> MAPIReadMail(GetMAPIModule(), _name);
    return MAPIReadMail(session, ui_param, id, flags, reserved, message);
}

ulong MAPIModule::MAPISaveMail(LHANDLE session, ulong ui_param, MapiMessage* message, uint flags, ulong reserved, const tchar* id)
{
    const char _name[] = "MAPISaveMail";

    static ModuleProc6<ulong, LHANDLE, ulong, MapiMessage*, uint, ulong, const tchar*> MAPISaveMail(GetMAPIModule(), _name);
    return MAPISaveMail(session, ui_param, message, flags, reserved, id);
}

ulong MAPIModule::MAPIDeleteMail(LHANDLE session, ulong ui_param, const tchar* id, uint flags, ulong reserved)
{
    const char _name[] = "MAPIDeleteMail";

    static ModuleProc5<ulong, LHANDLE, ulong, const tchar*, uint, ulong> MAPIDeleteMail(GetMAPIModule(), _name);
    return MAPIDeleteMail(session, ui_param, id, flags, reserved);
}

ulong MAPIModule::MAPIFreeBuffer(void* p)
{
    const char _name[] = "MAPIFreeBuffer";

    static ModuleProc1<ulong, void*> MAPIFreeBuffer(GetMAPIModule(), _name);
    return MAPIFreeBuffer(p);
}

ulong MAPIModule::MAPIAddress(LHANDLE session, ulong ui_param, const tchar* caption, ulong edit_fields, const tchar* labels, ulong recips_count, MapiRecipDesc* recips_list, uint flags, ulong reserved, ulong* new_recips_count, MapiRecipDesc* new_recips_list)
{
    const char _name[] = "MAPIAddress";

    static ModuleProc11<ulong, LHANDLE, ulong, const tchar*, ulong, const tchar*, ulong, MapiRecipDesc*, uint, ulong, ulong*, MapiRecipDesc*> MAPIAddress(GetMAPIModule(), _name);
    return MAPIAddress(session, ui_param, caption, edit_fields, labels, recips_count, recips_list, flags, reserved, new_recips_count, new_recips_list);
}

ulong MAPIModule::MAPIDetails(LHANDLE session, ulong ui_param, MapiRecipDesc* recip, uint flags, ulong reserved)
{
    const char _name[] = "MAPIDetails";

    static ModuleProc5<ulong, LHANDLE, ulong, MapiRecipDesc*, uint, ulong> MAPIDetails(GetMAPIModule(), _name);
    return MAPIDetails(session, ui_param, recip, flags, reserved);
}

ulong MAPIModule::MAPIResolveName(LHANDLE session, ulong ui_param, const tchar* name, uint flags, ulong reserved, MapiRecipDesc** recip)
{
    const char _name[] = "MAPIResolveName";

    static ModuleProc6<ulong, LHANDLE, ulong, const tchar*, uint, ulong, MapiRecipDesc**> MAPIResolveName(GetMAPIModule(), _name);
    return MAPIResolveName(session, ui_param, name, flags, reserved, recip);
}

// MAPIX
HRESULT MAPIModule::MAPIInitialize(void* init)
{
    const char _name[] = "MAPIInitialize";

    static ModuleProc1<HRESULT, void*> MAPIInitialize(GetMAPIModule(), _name);
    return MAPIInitialize(init);
}

void MAPIModule::MAPIUninitialize()
{
    const char _name[] = "MAPIUninitialize";

    static ModuleProcV0<> MAPIUninitialize(GetMAPIModule(), _name);
    MAPIUninitialize();
}

HRESULT MAPIModule::MAPILogonEx(ulong ui_parem, const tchar* profile, const tchar* password, uint flags, IMAPISession* session)
{
    const char _name[] = "MAPILogonEx";

    static ModuleProc5<HRESULT, ulong, const tchar*, const tchar*, uint, IMAPISession*> MAPILogonEx(GetMAPIModule(), _name);
    return MAPILogonEx(ui_parem, profile, password, flags, session);
}

SCODE MAPIModule::MAPIAllocateBuffer(uint count, void** buffer)
{
    const char _name[] = "MAPIAllocateBuffer";

    static ModuleProc2<SCODE, uint, void**> MAPIAllocateBuffer(GetMAPIModule(), _name);
    return MAPIAllocateBuffer(count, buffer);
}

SCODE MAPIModule::MAPIAllocateMore(uint count, void* object, void** buffer)
{
    const char _name[] = "MAPIAllocateMore";

    static ModuleProc3<SCODE, uint, void*, void**> MAPIAllocateMore(GetMAPIModule(), _name);
    return MAPIAllocateMore(count, object, buffer);
}

HRESULT MAPIModule::MAPIAdminProfiles(uint flags, IProfAdmin** admin)
{
    const char _name[] = "MAPIAdminProfiles";

    static ModuleProc2<HRESULT, uint, IProfAdmin**> MAPIAdminProfiles(GetMAPIModule(), _name);
    return MAPIAdminProfiles(flags, admin);
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__
