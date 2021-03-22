////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __RAS_INL__
#define __RAS_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class RasConnection
// ----- -------------
__INLINE__ RasConnection::operator RASCONN* ()
{
    return reinterpret_cast<RASCONN*>(this);
}

__INLINE__ RasConnection::operator const RASCONN* ()
{
    return reinterpret_cast<const RASCONN*>(this);
}

__INLINE__ HRASCONN RasConnection::GetHRasConnection() const
{
    return hrasconn;
}

__INLINE__ const tchar* RasConnection::GetEntryName() const
{
    return reinterpret_cast<const tchar*>(szEntryName);
}

#if (WINVER >= 0x400)
__INLINE__ const tchar* RasConnection::GetDeviceType() const
{
    return reinterpret_cast<const tchar*>(szDeviceType);
}

__INLINE__ const tchar* RasConnection::GetDeviceName() const
{
    return reinterpret_cast<const tchar*>(szDeviceName);
}
#endif
////////////////////////////////////////////////////////////////////////////////////////
// struct _ConnectionKeyExtractor
// ------ -----------------------
__INLINE__ const pctchar& _ConnectionKeyExtractor::operator() (const RasConnection& _v) const
{
    return reinterpret_cast<const pctchar&>(*_v.GetEntryName());
}
////////////////////////////////////////////////////////////////////////////////////////
// struct _ConnectionComparator
// ------ ---------------------
__INLINE__ int _ConnectionComparator::operator() (const pctchar& _key1, const pctchar& _key2) const
{
    return _tcscmp(_key1, _key2);
}
////////////////////////////////////////////////////////////////////////////////////////
// class RasConnections
// ----- --------------
__INLINE__ ulong RasConnections::XRasConnections::GetError() const
{
    return ReturnCode;
}
////////////////////////////////////////////////////////////////////////////////////////
// class RasEntryName
// ----- ------------
__INLINE__ RasEntryName::operator RASENTRYNAME* ()
{
    return reinterpret_cast<RASENTRYNAME*>(this);
}

__INLINE__ RasEntryName::operator const RASENTRYNAME* ()
{
    return reinterpret_cast<const RASENTRYNAME*>(this);
}

__INLINE__ const tchar* RasEntryName::GetEntryName() const
{
    return reinterpret_cast<const tchar*>(szEntryName);
}
////////////////////////////////////////////////////////////////////////////////////////
// struct _EntryNameKeyExtractor
// ------ ----------------------
__INLINE__ const pctchar& _EntryNameKeyExtractor::operator() (const RasEntryName& _v) const
{
    return reinterpret_cast<const pctchar&>(*_v.GetEntryName());
}
////////////////////////////////////////////////////////////////////////////////////////
// struct _EntryNameComparator
// ------ --------------------
__INLINE__ int _EntryNameComparator::operator() (const pctchar& _key1, const pctchar& _key2) const
{
    return _tcscmp(_key1, _key2);
}
////////////////////////////////////////////////////////////////////////////////////////
// class RasEntryNames
// ----- -------------
__INLINE__ ulong RasEntryNames::XRasEntriesName::GetError() const
{
    return ReturnCode;
}
////////////////////////////////////////////////////////////////////////////////////////
// class RasDialParams
// ----- -------------
__INLINE__ RasDialParams::operator RASDIALPARAMS* ()
{
    return reinterpret_cast<RASDIALPARAMS*>(this);
}

__INLINE__ RasDialParams::operator const RASDIALPARAMS* ()
{
    return reinterpret_cast<const RASDIALPARAMS*>(this);
}

__INLINE__ tchar* RasDialParams::GetEntryName() const
{
    return (tchar*)&szEntryName;
}

__INLINE__ void RasDialParams::SetEntryName(const tchar* name)
{
    StrCopy(szEntryName, name);
}

__INLINE__ tchar* RasDialParams::GetPhoneNumber() const
{
    return (tchar*)&szPhoneNumber;
}

__INLINE__ void RasDialParams::SetPhoneNumber(const tchar* number)
{
    StrCopy(szPhoneNumber, number);
}

__INLINE__ tchar* RasDialParams::GetCallbackPhoneNumber() const
{
    return (tchar*)(&szCallbackNumber);
}

__INLINE__ void RasDialParams::SetCallbackPhoneNumber(const tchar* number)
{
    StrCopy(szCallbackNumber, number);
}

__INLINE__ tchar* RasDialParams::GetUserName() const
{
    return (tchar*)(&szUserName);
}

__INLINE__ void RasDialParams::SetUserName(const tchar* username)
{
    StrCopy(szUserName, username);
}

__INLINE__ tchar* RasDialParams::GetPassword() const
{
    return (tchar*)(&szPassword);
}

__INLINE__ void RasDialParams::SetPassword(const tchar* password)
{
    StrCopy(szPassword, password);
}

__INLINE__ tchar* RasDialParams::GetDomain() const
{
    return (tchar*)(&szDomain);
}

__INLINE__ void RasDialParams::SetDomain(const tchar* domain)
{
    StrCopy(szDomain, domain);
}

#if (WINVER >= 0x401)
__INLINE__ ulong RasDialParams::GetSubEntry() const
{
    return dwSubEntry;
}

__INLINE__ void RasDialParams::SetSubEntry(ulong subentry)
{
#if (WINVER >= 0x401)
//    szSubEntry = subentry;
#endif
}

__INLINE__ ulong RasDialParams::GetCallbackID() const
{
    return dwCallbackId;
}

__INLINE__ void RasDialParams::SetCallbackID(ulong id)
{
    dwCallbackId = id;
}
#endif
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __RAS_INL__
