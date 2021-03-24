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

#ifndef __RAS_INC__
#   include <RAS.inc>
#endif

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class RASModule
// ----- ---------
RASModule::RASModule() : Module(_t("RASAPI32.DLL"))
{
}

Module& RASModule::GetRASModule()
{
    static RASModule TheModule;
    return TheModule;
}

ulong RASModule::RasDial(RASDIALEXTENSIONS* ext, tchar* phonebook, RASDIALPARAMS* param, ulong notify_type, void* handler_event, HRASCONN* handle)
{
#ifdef _UNICODE
    const char _name[] = "RasDialW";

    static ModuleProc6<ulong, RASDIALEXTENSIONS*, tchar*, RASDIALPARAMS*, ulong, void*, HRASCONN*> RasDial(GetRASModule(), _name);
#else
    const char _name[] = "RasDialA";

    static ModuleProc6<ulong, RASDIALEXTENSIONS*, tchar*, RASDIALPARAMS*, ulong, void*, HRASCONN*> RasDial(GetRASModule(), _name);
#endif
    return RasDial(ext, phonebook, param, notify_type, handler_event, handle);
}

ulong RASModule::RasEnumConnections(RASCONN* data, ulong* size, ulong* count)
{
#ifdef _UNICODE
    const char _name[] = "RasEnumConnectionsW";

    static ModuleProc3<ulong, RASCONN*, ulong*, ulong*> RasEnumConnections(GetRASModule(), _name);
#else
    const char _name[] = "RasEnumConnectionsA";

    static ModuleProc3<ulong, RASCONN*, ulong*, ulong*> RasEnumConnections(GetRASModule(), _name);
#endif
    return RasEnumConnections(data, size, count);
}

ulong RASModule::RasEnumEntries(tchar* reserved, tchar* phonebook, RASENTRYNAME* entry_name, ulong* size, ulong* count)
{
#ifdef _UNICODE
    const char _name[] = "RasEnumEntriesW";

    static ModuleProc5<ulong, tchar*, tchar*, RASENTRYNAME*, ulong*, ulong*> RasEnumEntries(GetRASModule(), _name);
#else
    const char _name[] = "RasEnumEntriesA";

    static ModuleProc5<ulong, tchar*, tchar*, RASENTRYNAME*, ulong*, ulong*> RasEnumEntries(GetRASModule(), _name);
#endif
    return RasEnumEntries(reserved, phonebook, entry_name, size, count);
}

ulong RASModule::RasGetConnectStatus(HRASCONN handle, RASCONNSTATUS* status_data)
{
#ifdef _UNICODE
    const char _name[] = "RasGetConnectStatusW";

    static ModuleProc2<ulong, HRASCONN, RASCONNSTATUS*> RasGetConnectStatus(GetRASModule(), _name);
#else
    const char _name[] = "RasGetConnectStatusA";

    static ModuleProc2<ulong, HRASCONN, RASCONNSTATUS*> RasGetConnectStatus(GetRASModule(), _name);
#endif
    return RasGetConnectStatus(handle, status_data);
}

ulong RASModule::RasGetErrorString(ulong errorvalue, tchar* errorstring, ulong count)
{
#ifdef _UNICODE
    const char _name[] = "RasGetErrorStringW";

    static ModuleProc3<ulong, ulong, tchar*, ulong> RasGetErrorString(GetRASModule(), _name);
#else
    const char _name[] = "RasGetErrorStringA";

    static ModuleProc3<ulong, ulong, tchar*, ulong> RasGetErrorString(GetRASModule(), _name);
#endif
    return RasGetErrorString(errorvalue, errorstring, count);
}

ulong RASModule::RasHangUp(HRASCONN handle)
{
#ifdef _UNICODE
    const char _name[] = "RasHangUpW";

    static ModuleProc1<ulong, HRASCONN> RasHangUp(GetRASModule(), _name);
#else
    const char _name[] = "RasHangUpA";

    static ModuleProc1<ulong, HRASCONN> RasHangUp(GetRASModule(), _name);
#endif
    return RasHangUp(handle);
}

ulong RASModule::RasGetProjectionInfo(HRASCONN handle, RASPROJECTION projection, void* buffer, ulong* count)
{
#ifdef _UNICODE
    const char _name[] = "RasGetProjectionInfoW";

    static ModuleProc4<ulong, HRASCONN, RASPROJECTION, void*, ulong*> RasGetProjectionInfo(GetRASModule(), _name);
#else
    const char _name[] = "RasGetProjectionInfoA";

    static ModuleProc4<ulong, HRASCONN, RASPROJECTION, void*, ulong*> RasGetProjectionInfo(GetRASModule(), _name);
#endif
    return RasGetProjectionInfo(handle, projection, buffer, count);
}

ulong RASModule::RasCreatePhonebookEntry(HWND hwnd, tchar* phonebook)
{
#ifdef _UNICODE
    const char _name[] = "RasCreatePhonebookEntryW";

    static ModuleProc2<ulong, HWND, tchar*> RasCreatePhonebookEntry(GetRASModule(), _name);
#else
    const char _name[] = "RasCreatePhonebookEntryA";

    static ModuleProc2<ulong, HWND, tchar*> RasCreatePhonebookEntry(GetRASModule(), _name);
#endif
    return RasCreatePhonebookEntry(hwnd, phonebook);
}

ulong RASModule::RasEditPhonebookEntry(HWND hwnd, tchar* phonebook, tchar* entryname)
{
#ifdef _UNICODE
    const char _name[] = "RasEditPhonebookEntryW";

    static ModuleProc3<ulong, HWND, tchar*, tchar*> RasEditPhonebookEntry(GetRASModule(), _name);
#else
    const char _name[] = "RasEditPhonebookEntryA";

    static ModuleProc3<ulong, HWND, tchar*, tchar*> RasEditPhonebookEntry(GetRASModule(), _name);
#endif
    return RasEditPhonebookEntry(hwnd, phonebook, entryname);
}

ulong RASModule::RasSetEntryDialParams(tchar* phonebook, RASDIALPARAMS* param, bool remove_password)
{
#ifdef _UNICODE
    const char _name[] = "RasSetEntryDialParamsW";

    static ModuleProc3<ulong, tchar*, RASDIALPARAMS*, bool> RasSetEntryDialParams(GetRASModule(), _name);
#else
    const char _name[] = "RasSetEntryDialParamsA";

    static ModuleProc3<ulong, tchar*, RASDIALPARAMS*, bool> RasSetEntryDialParams(GetRASModule(), _name);
#endif
    return RasSetEntryDialParams(phonebook, param, remove_password ? TRUE : FALSE);
}

ulong RASModule::RasGetEntryDialParams(tchar* phonebook, RASDIALPARAMS* param, bool* remove_password)
{
#ifdef _UNICODE
    const char _name[] = "RasGetEntryDialParamsW";

    static ModuleProc3<ulong, tchar*, RASDIALPARAMS*, BOOL*> RasGetEntryDialParams(GetRASModule(), _name);
#else
    const char _name[] = "RasGetEntryDialParamsA";

    static ModuleProc3<ulong, tchar*, RASDIALPARAMS*, BOOL*> RasGetEntryDialParams(GetRASModule(), _name);
#endif    

    BOOL  tmp;
    ulong rc = RasGetEntryDialParams(phonebook, param, &tmp);
    *remove_password = tmp == TRUE ? true : false;
    return rc;
}

ulong RASModule::RasEnumDevices(RASDEVINFO* info, ulong* size, ulong* count)
{
#ifdef _UNICODE
    const char _name[] = "RasEnumDevicesW";

    static ModuleProc3<ulong, RASDEVINFO*, ulong*, ulong*> RasEnumDevices(GetRASModule(), _name);
#else
    const char _name[] = "RasEnumDevicesA";

    static ModuleProc3<ulong, RASDEVINFO*, ulong*, ulong*> RasEnumDevices(GetRASModule(), _name);
#endif
    return RasEnumDevices(info, size, count);
}

ulong RASModule::RasGetCountryInfo(RASCTRYINFO* info, ulong* count)
{
#ifdef _UNICODE
    const char _name[] = "RasGetCountryInfoW";

    static ModuleProc2<ulong, RASCTRYINFO*, ulong*> RasGetCountryInfo(GetRASModule(), _name);
#else
    const char _name[] = "RasGetCountryInfoA";

    static ModuleProc2<ulong, RASCTRYINFO*, ulong*> RasGetCountryInfo(GetRASModule(), _name);
#endif
    return RasGetCountryInfo(info, count);
}

ulong RASModule::RasGetEntryProperties(tchar* phonebook, tchar* entry, RASENTRY* ras_entry, ulong* size, byte* buffer, ulong* count)
{
#ifdef _UNICODE
    const char _name[] = "RasGetEntryPropertiesW";

    static ModuleProc6<ulong, tchar*, tchar*, RASENTRY*, ulong*, byte*, ulong*> RasGetEntryProperties(GetRASModule(), _name);
#else
    const char _name[] = "RasGetEntryPropertiesA";

    static ModuleProc6<ulong, tchar*, tchar*, RASENTRY*, ulong*, byte*, ulong*> RasGetEntryProperties(GetRASModule(), _name);
#endif
    return RasGetEntryProperties(phonebook, entry, ras_entry, size, buffer, count);
}

ulong RASModule::RasSetEntryProperties(tchar* phonebook, tchar* entry, RASENTRY* ras_entry, ulong size, byte* buffer, ulong count)
{
#ifdef _UNICODE
    const char _name[] = "RasSetEntryPropertiesW";

    static ModuleProc6<ulong, tchar*, tchar*, RASENTRY*, ulong, byte*, ulong> RasSetEntryProperties(GetRASModule(), _name);
#else
    const char _name[] = "RasSetEntryPropertiesA";

    static ModuleProc6<ulong, tchar*, tchar*, RASENTRY*, ulong, byte*, ulong> RasSetEntryProperties(GetRASModule(), _name);
#endif
    return RasSetEntryProperties(phonebook, entry, ras_entry, size, buffer, count);
}

ulong RASModule::RasRenameEntry(tchar* phonebook, tchar* oldentry, tchar* newentry)
{
    const char _name[] = "RasRenameEntry";

    static ModuleProc3<ulong, tchar*, tchar*, tchar*> RasRenameEntry(GetRASModule(), _name);
    return RasRenameEntry(phonebook, oldentry, newentry);
}

ulong RASModule::RasDeleteEntry(tchar* phonebook, tchar* entry)
{
#ifdef _UNICODE
    const char _name[] = "RasDeleteEntryW";

    static ModuleProc2<ulong, tchar*, tchar*> RasDeleteEntry(GetRASModule(), _name);
#else
    const char _name[] = "RasDeleteEntryA";

    static ModuleProc2<ulong, tchar*, tchar*> RasDeleteEntry(GetRASModule(), _name);
#endif
    return RasDeleteEntry(phonebook, entry);
}

ulong RASModule::RasValidateEntryName(tchar* phonebook, tchar* entry)
{
#ifdef _UNICODE
    const char _name[] = "RasValidateEntryNameW";

    static ModuleProc2<ulong, tchar*, tchar*> RasValidateEntryName(GetRASModule(), _name);
#else
    const char _name[] = "RasValidateEntryNameA";

    static ModuleProc2<ulong, tchar*, tchar*> RasValidateEntryName(GetRASModule(), _name);
#endif
    return RasValidateEntryName(phonebook, entry);
}

#if (WINVER >= 0x401)
ulong RASModule::RasGetSubEntryHandle(HRASCONN handle, ulong subentry, HRASCONN* handle2)
{
#ifdef _UNICODE
    const char _name[] = "RasGetSubEntryHandleW";

    static ModuleProc3<ulong, HRASCONN, ulong, HRASCONN*> RasGetSubEntryHandle(GetRASModule(), _name);
#else
    const char _name[] = "RasGetSubEntryHandleA";

    static ModuleProc3<ulong, HRASCONN, ulong, HRASCONN*> RasGetSubEntryHandle(GetRASModule(), _name);
#endif
    return RasGetSubEntryHandle(handle, subentry, handle2);
}

ulong RASModule::RasGetCredentials(tchar* phonebook, tchar* entry, RASCREDENTIALS* credentials)
{
#ifdef _UNICODE
    const char _name[] = "RasGetCredentialsW";

    static ModuleProc3<ulong, tchar*, tchar*, RASCREDENTIALS*> RasGetCredentials(GetRASModule(), _name);
#else
    const char _name[] = "RasGetCredentialsA";

    static ModuleProc3<ulong, tchar*, tchar*, RASCREDENTIALS*> RasGetCredentials(GetRASModule(), _name);
#endif
    return RasGetCredentials(phonebook, entry, credentials);
}

ulong RASModule::RasSetCredentials(tchar* phonebook, tchar* entry, RASCREDENTIALS* credentials, bool clear)
{
#ifdef _UNICODE
    const char _name[] = "RasSetCredentialsW";

    static ModuleProc4<ulong, tchar*, tchar*, RASCREDENTIALS*, bool> RasSetCredentials(GetRASModule(), _name);
#else
    const char _name[] = "RasSetCredentialsA";

    static ModuleProc4<ulong, tchar*, tchar*, RASCREDENTIALS*, bool> RasSetCredentials(GetRASModule(), _name);
#endif
    return RasSetCredentials(phonebook, entry, credentials, clear ? TRUE : FALSE);
}

ulong RASModule::RasConnectionNotification(HRASCONN handle, HANDLE hevent, ulong flags)
{
#ifdef _UNICODE
    const char _name[] = "RasConnectionNotificationW";

    static ModuleProc3<ulong, HRASCONN, HANDLE, ulong> RasConnectionNotification(GetRASModule(), _name);
#else
    const char _name[] = "RasConnectionNotificationA";

    static ModuleProc3<ulong, HRASCONN, HANDLE, ulong> RasConnectionNotification(GetRASModule(), _name);
#endif
    return RasConnectionNotification(handle, hevent, flags);
}

ulong RASModule::RasGetSubEntryProperties(tchar* phonebook, tchar* entry, ulong subentry, RASSUBENTRY* ras_subentry, ulong* size, byte* tapi_config, ulong device_config_count)
{
#ifdef _UNICODE
    const char _name[] = "RasGetSubEntryPropertiesW";

    static ModuleProc7<ulong, tchar*, tchar*, ulong, RASSUBENTRY*, ulong*, byte*, ulong> RasGetSubEntryProperties(GetRASModule(), _name);
#else
    const char _name[] = "RasGetSubEntryPropertiesA";

    static ModuleProc7<ulong, tchar*, tchar*, ulong, RASSUBENTRY*, ulong*, byte*, ulong> RasGetSubEntryProperties(GetRASModule(), _name);
#endif
    return RasGetSubEntryProperties(phonebook, entry, subentry, ras_subentry, size, tapi_config, device_config_count);
}

ulong RASModule::RasSetSubEntryProperties(tchar* phonebook, tchar* entry, ulong subentry, RASSUBENTRY* ras_subentry, ulong* size, byte* tapi_config, ulong device_config_count)
{
#ifdef _UNICODE
    const char _name[] = "RasSetSubEntryPropertiesW";
#else
    const char _name[] = "RasSetSubEntryPropertiesA";
#endif
    static ModuleProc7<ulong, tchar*, tchar*, ulong, RASSUBENTRY*, ulong*, byte*, ulong> RasSetSubEntryProperties(GetRASModule(), _name);
    return RasSetSubEntryProperties(phonebook, entry, subentry, ras_subentry, size, tapi_config, device_config_count);
}

ulong RASModule::RasGetAutodialAddress(tchar* address, ulong* reserved, RASAUTODIALENTRY* autodial, ulong* entries_size, ulong* entries_count)
{
#ifdef _UNICODE
    const char _name[] = "RasGetAutodialAddressW";

    static ModuleProc5<ulong, tchar*, ulong*, RASAUTODIALENTRY*, ulong*, ulong*> RasGetAutodialAddress(GetRASModule(), _name);
#else
    const char _name[] = "RasGetAutodialAddressA";

    static ModuleProc5<ulong, tchar*, ulong*, RASAUTODIALENTRY*, ulong*, ulong*> RasGetAutodialAddress(GetRASModule(), _name);
#endif
    return RasGetAutodialAddress(address, reserved, autodial, entries_size, entries_count);
}

ulong RASModule::RasSetAutodialAddress(tchar* address, ulong reserved, RASAUTODIALENTRY* autodial, ulong entries_size, ulong entries_count)
{
#ifdef _UNICODE
    const char _name[] = "RasSetAutodialAddressW";

    static ModuleProc5<ulong, tchar*, ulong, RASAUTODIALENTRY*, ulong, ulong> RasSetAutodialAddress(GetRASModule(), _name);
#else
    const char _name[] = "RasSetAutodialAddressA";

    static ModuleProc5<ulong, tchar*, ulong, RASAUTODIALENTRY*, ulong, ulong> RasSetAutodialAddress(GetRASModule(), _name);
#endif
    return RasSetAutodialAddress(address, reserved, autodial, entries_size, entries_count);
}

ulong RASModule::RasEnumAutodialAddresses(tchar** addresses, ulong* size, ulong* count)
{
#ifdef _UNICODE
    const char _name[] = "RasEnumAutodialAddressesW";

    static ModuleProc3<ulong, tchar**, ulong*, ulong*> RasEnumAutodialAddresses(GetRASModule(), _name);
#else
    const char _name[] = "RasEnumAutodialAddressesA";

    static ModuleProc3<ulong, tchar**, ulong*, ulong*> RasEnumAutodialAddresses(GetRASModule(), _name);
#endif
    return RasEnumAutodialAddresses(addresses, size, count);
}

ulong RASModule::RasGetAutodialEnable(ulong location, bool* enabled)
{
#ifdef _UNICODE
    const char _name[] = "RasGetAutodialEnableW";

    static ModuleProc2<ulong, ulong, BOOL*> RasGetAutodialEnable(GetRASModule(), _name);
#else
    const char _name[] = "RasGetAutodialEnableA";

    static ModuleProc2<ulong, ulong, BOOL*> RasGetAutodialEnable(GetRASModule(), _name);
#endif

    BOOL  tmp;

    ulong rc = RasGetAutodialEnable(location, &tmp);

    *enabled = tmp == TRUE ? true : false;

    return rc;
}

ulong RASModule::RasSetAutodialEnable(ulong location, bool enabled)
{
#ifdef _UNICODE
    const char _name[] = "RasSetAutodialEnableW";

    static ModuleProc2<ulong, ulong, bool> RasSetAutodialEnable(GetRASModule(), _name);
#else
    const char _name[] = "RasSetAutodialEnableA";

    static ModuleProc2<ulong, ulong, bool> RasSetAutodialEnable(GetRASModule(), _name);
#endif
    return RasSetAutodialEnable(location, enabled);
}

ulong RASModule::RasGetAutodialParam(ulong key, void* value, ulong* count)
{
#ifdef _UNICODE
    const char _name[] = "RasGetAutodialParamW";

    static ModuleProc3<ulong, ulong, void*, ulong*> RasGetAutodialParam(GetRASModule(), _name);
#else
    const char _name[] = "RasGetAutodialParamA";

    static ModuleProc3<ulong, ulong, void*, ulong*> RasGetAutodialParam(GetRASModule(), _name);
#endif
    return RasGetAutodialParam(key, value, count);
}

ulong RASModule::RasSetAutodialParam(ulong key, void* value, ulong count)
{
#ifdef _UNICODE
    const char _name[] = "RasSetAutodialParamW";

    static ModuleProc3<ulong, ulong, void*, ulong> RasSetAutodialParam(GetRASModule(), _name);
#else
    const char _name[] = "RasSetAutodialParamA";

    static ModuleProc3<ulong, ulong, void*, ulong> RasSetAutodialParam(GetRASModule(), _name);
#endif
    return RasSetAutodialParam(key, value, count);
}
#endif
////////////////////////////////////////////////////////////////////////////////////////
// class RasConnection
// ----- -------------
RasConnection::RasConnection()
{
    Init();
}

RasConnection::RasConnection(const RasConnection& other)
{
    operator = (other);
}

RasConnection::RasConnection(HRASCONN hconnection, const tchar* entry_name, const tchar* device_type, const tchar* device_name)
{
    Init();

    hrasconn = hconnection;

    StrCopy(szEntryName, entry_name);

#if (WINVER >= 0x400)
    StrCopy(szDeviceType, device_type);
    StrCopy(szDeviceName, device_name);
#endif
}

RasConnection::~RasConnection()
{
}

const RasConnection& RasConnection::operator = (const RasConnection& other)
{
    if(this != &other)
    {
        dwSize   = sizeof(RASCONN);
        hrasconn = other.hrasconn;

        StrCopy(szEntryName, other.szEntryName);

#if (WINVER >= 0x400)
        StrCopy(szDeviceType, other.szDeviceType);
        StrCopy(szDeviceName, other.szDeviceName);
#endif
    }

    return *this;
}

void RasConnection::Init()
{
    dwSize   = sizeof(RASCONN);
    hrasconn = null;

    InitMemory(&szEntryName, sizeof(szEntryName));

#if (WINVER >= 0x400)
    InitMemory(&szDeviceType, sizeof(szDeviceType));
    InitMemory(&szDeviceName, sizeof(szDeviceName));
#endif
}
////////////////////////////////////////////////////////////////////////////////////////
// class RasConnections
// ----- --------------
static _ConnectionKeyExtractor __ConnectionKeyExtractor__;
static _ConnectionComparator   __ConnectionComparator__;
//
RasConnections::RasConnections() : List<RasConnection, pctchar, _ConnectionKeyExtractor, _ConnectionComparator>(__ConnectionKeyExtractor__, __ConnectionComparator__)
{
    SetState(StateObject::eNoDelete);
}

RasConnections::~RasConnections()
{
    SetState(StateObject::eDelete);
}

void RasConnections::GetConnections()
{
    // reset content
    Destroy();

    RASCONN* connection = null;

    // enumerate connections
    int   rc;
    ulong count = sizeof(RASCONN);
    ulong connection_count = 0;

    connection = (RASCONN*)new byte[count];

    connection->dwSize = sizeof(RASCONN);
    
    rc = RASModule::RasEnumConnections(connection, &count, &connection_count);

    if(rc != 0)
    {
        if(rc == ERROR_BUFFER_TOO_SMALL)
        {
            delete connection;

            connection         = (RASCONN*)new byte[count];
            connection->dwSize = sizeof(RASCONN);
            connection_count   = 0;

            rc = RASModule::RasEnumConnections(connection, &count, &connection_count);

            if(rc == ERROR_NOT_ENOUGH_MEMORY)
            {
                delete [] connection;
                throw XRasConnections(rc, X::OutOfMemory);
            }
            else if(rc != 0)// other error
            {
                delete [] connection;
                throw XRasConnections(rc, X::Failure);
            }
        }
    }

    for(ulong i = 0; i < connection_count; i++)
    {
#if (WINVER >= 0x400)
        LinkTail(new RasConnection(connection[i].hrasconn, connection[i].szEntryName, connection[i].szDeviceType, connection[i].szDeviceName));
#else
        LinkTail(new RasConnection(connection[i].hrasconn, connection[i].szEntryName));
#endif
    }

    delete [] connection;
}

RasConnections::XRasConnections::XRasConnections(ulong _rc, uint _error) : X(_error)
{
    ReturnCode = _rc;
}
////////////////////////////////////////////////////////////////////////////////////////
// class RasEntryName
// ----- ------------
RasEntryName::RasEntryName()
{
    Init();
}

RasEntryName::RasEntryName(const RasEntryName& other)
{
    operator = (other);
}

RasEntryName::RasEntryName(const tchar* name)
{
    Init();

    StrCopy(szEntryName, name);
}

RasEntryName::~RasEntryName()
{
}

const RasEntryName& RasEntryName::operator = (const RasEntryName& other)
{
    if(this != &other)
    {
        dwSize = sizeof(RASENTRYNAME);

        StrCopy(szEntryName, other.szEntryName);
    }

    return *this;
}

void RasEntryName::Init()
{
    dwSize = sizeof(RASENTRYNAME);

    InitMemory(szEntryName, sizeof(szEntryName));
}
////////////////////////////////////////////////////////////////////////////////////////
// class RasEntryNames
// ----- -------------
static _EntryNameKeyExtractor __EntryNameKeyExtractor__;
static _EntryNameComparator   __EntryNameComparator__;
//
RasEntryNames::RasEntryNames() : List<RasEntryName, pctchar, _EntryNameKeyExtractor, _EntryNameComparator>(__EntryNameKeyExtractor__, __EntryNameComparator__)
{
    SetState(StateObject::eNoDelete);
}

RasEntryNames::~RasEntryNames()
{
    SetState(StateObject::eDelete);
}

void RasEntryNames::InitEntries()
{
    // reset content
    Destroy();

    RASENTRYNAME* entry = null;

    // enumerate connections
    int   rc;
    ulong count = sizeof(RASENTRYNAME);
    ulong entry_count = 0;

    entry = (RASENTRYNAME*)new byte[count];

    entry->dwSize = sizeof(RASENTRYNAME);
    
    rc = RASModule::RasEnumEntries(null, null, entry, &count, &entry_count);

    if(rc != 0)
    {
        if(rc == ERROR_BUFFER_TOO_SMALL)
        {
            delete entry;

            entry         = (RASENTRYNAME*)new byte[count];
            entry->dwSize = sizeof(RASENTRYNAME);
            entry_count   = 0;

            rc = RASModule::RasEnumEntries(null, null, entry, &count, &entry_count);

            if(rc == ERROR_NOT_ENOUGH_MEMORY)
            {
                delete [] entry;
                throw XRasEntriesName(rc, X::OutOfMemory);
            }
            else if(rc != 0)// other error
            {
                delete [] entry;
                throw XRasEntriesName(rc, X::Failure);
            }
        }
    }

    for(ulong i = 0; i < entry_count; i++)
    {
        LinkTail(new RasEntryName(entry[i].szEntryName));
    }

    delete [] entry;
}

RasEntryNames::XRasEntriesName::XRasEntriesName(ulong _rc, uint _error) : X(_error)
{
    ReturnCode = _rc;
}
////////////////////////////////////////////////////////////////////////////////////////
// class RasDialParams
// ----- -------------
RasDialParams::RasDialParams()
{
    Init();
}

RasDialParams::RasDialParams(const RASDIALPARAMS& params)
{
    Init();

    StrCopy(szEntryName, params.szEntryName);
    StrCopy(szPhoneNumber, params.szPhoneNumber);
    StrCopy(szCallbackNumber, params.szCallbackNumber);
    StrCopy(szUserName, params.szUserName);
    StrCopy(szPassword, params.szPassword);
    StrCopy(szDomain, params.szDomain);
#if (WINVER >= 0x401)
    dwSubEntry   = params.dwSubEntry;
    dwCallbackId = params.dwCallbackId;
#endif
}

RasDialParams::~RasDialParams()
{
}

const RasDialParams& RasDialParams::operator = (const RasDialParams& other)
{
    if(this != &other)
    {
        Init();

        StrCopy(szEntryName, other.szEntryName);
        StrCopy(szPhoneNumber, other.szPhoneNumber);
        StrCopy(szCallbackNumber, other.szCallbackNumber);
        StrCopy(szUserName, other.szUserName);
        StrCopy(szPassword, other.szPassword);
        StrCopy(szDomain, other.szDomain);
#if (WINVER >= 0x401)
        dwSubEntry   = other.dwSubEntry;
        dwCallbackId = other.dwCallbackId;
#endif
    }

    return *this;
}

void RasDialParams::Init()
{
    dwSize = sizeof(RASDIALPARAMS);

    InitMemory(&szEntryName, sizeof(szEntryName));
    InitMemory(szPhoneNumber, sizeof(szPhoneNumber));
    InitMemory(szCallbackNumber, sizeof(szCallbackNumber));
    InitMemory(szUserName, sizeof(szUserName));
    InitMemory(szPassword, sizeof(szPassword));
    InitMemory(szDomain, sizeof(szDomain));

#if (WINVER >= 0x401)
    dwSubEntry   = 0;
    dwCallbackId = 0;
#endif
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__
