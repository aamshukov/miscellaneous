////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __RAS_H__
#define __RAS_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class RASModule
// ----- ---------
class __DECLSPEC__ RASModule : public Module
{
    public:
                        RASModule();

     static Module&     GetRASModule();

     static ulong       RasDial(RASDIALEXTENSIONS*, tchar*, RASDIALPARAMS*, ulong, void*, HRASCONN*);
     static ulong       RasEnumConnections(RASCONN*, ulong*, ulong*);
     static ulong       RasEnumEntries(tchar*, tchar*, RASENTRYNAME*, ulong*, ulong*);
     static ulong       RasGetConnectStatus(HRASCONN, RASCONNSTATUS*);
     static ulong       RasGetErrorString(ulong, tchar*, ulong);
     static ulong       RasHangUp(HRASCONN);
     static ulong       RasGetProjectionInfo(HRASCONN, RASPROJECTION, void*, ulong*);
     static ulong       RasCreatePhonebookEntry(HWND, tchar*);
     static ulong       RasEditPhonebookEntry(HWND, tchar*, tchar*);
     static ulong       RasSetEntryDialParams(tchar*, RASDIALPARAMS*, bool);
     static ulong       RasGetEntryDialParams(tchar*, RASDIALPARAMS*, bool*);
     static ulong       RasEnumDevices(RASDEVINFO*, ulong*, ulong*);
     static ulong       RasGetCountryInfo(RASCTRYINFO*, ulong*);
     static ulong       RasGetEntryProperties(tchar*, tchar*, RASENTRY*, ulong*, byte*, ulong*);
     static ulong       RasSetEntryProperties(tchar*, tchar*, RASENTRY*, ulong, byte*, ulong);
     static ulong       RasRenameEntry(tchar*, tchar*, tchar*);
     static ulong       RasDeleteEntry(tchar*, tchar*);
     static ulong       RasValidateEntryName(tchar*, tchar*);
#if (WINVER >= 0x401)
     static ulong       RasGetSubEntryHandle(HRASCONN, ulong, HRASCONN*);
     static ulong       RasGetCredentials(tchar*, tchar*, RASCREDENTIALS*);
     static ulong       RasSetCredentials(tchar*, tchar*, RASCREDENTIALS*, bool);
     static ulong       RasConnectionNotification(HRASCONN, HANDLE, ulong);
     static ulong       RasGetSubEntryProperties(tchar*, tchar*, ulong, RASSUBENTRY*, ulong*, byte*, ulong);
     static ulong       RasSetSubEntryProperties(tchar*, tchar*, ulong, RASSUBENTRY*, ulong*, byte*, ulong);
     static ulong       RasGetAutodialAddress(tchar*, ulong*, RASAUTODIALENTRY*, ulong*, ulong*);
     static ulong       RasSetAutodialAddress(tchar*, ulong, RASAUTODIALENTRY*, ulong, ulong);
     static ulong       RasEnumAutodialAddresses(tchar**, ulong*, ulong*);
     static ulong       RasGetAutodialEnable(ulong, bool*);
     static ulong       RasSetAutodialEnable(ulong, bool);
     static ulong       RasGetAutodialParam(ulong, void*, ulong*);
     static ulong       RasSetAutodialParam(ulong, void*, ulong);
#endif
};
////////////////////////////////////////////////////////////////////////////////////////
// class RasConnection
// ----- -------------
#ifdef _UNICODE
class RasConnection : public tagRASCONNW, public ListNodeBase<RasConnection, pctchar>
#else
class RasConnection : public tagRASCONNA, public ListNodeBase<RasConnection, pctchar>
#endif
{
    private:
     void                       Init();
    public:
                                RasConnection();
                                RasConnection(const RasConnection&);
                                RasConnection(HRASCONN, const tchar*, const tchar* = null, const tchar* = null);
     virtual                   ~RasConnection();

     const RasConnection&       operator = (const RasConnection&);

                                operator RASCONN* ();
                                operator const RASCONN* ();

     HRASCONN                   GetHRasConnection()         const;
     const tchar*               GetEntryName()              const;
#if (WINVER >= 0x400)
     const tchar*               GetDeviceType()             const;
     const tchar*               GetDeviceName()             const;
#endif
};
////////////////////////////////////////////////////////////////////////////////////////
// struct _ConnectionKeyExtractor
// ------ -----------------------
struct _ConnectionKeyExtractor
{
    const pctchar& operator() (const RasConnection&) const;
};
////////////////////////////////////////////////////////////////////////////////////////
// struct _ConnectionComparator
// ------ ---------------------
struct _ConnectionComparator
{
    int operator() (const pctchar&, const pctchar&) const;
};
////////////////////////////////////////////////////////////////////////////////////////
// class RasConnections
// ----- --------------
class RasConnections : public List<RasConnection, pctchar, _ConnectionKeyExtractor, _ConnectionComparator>
{
    public:
                RasConnections();
     virtual   ~RasConnections();

     void       GetConnections();
    public:

    class XRasConnections : public X
    {
        private:
         ulong  ReturnCode;
        public:
                XRasConnections(ulong, uint = X::Failure);

         ulong  GetError()  const;
    };

    friend class XRasConnections;
};
////////////////////////////////////////////////////////////////////////////////////////
// class RasEntryName
// ----- ------------
#ifdef _UNICODE
class RasEntryName : public tagRASENTRYNAMEW, public ListNodeBase<RasEntryName, pctchar>
#else
class RasEntryName : public tagRASENTRYNAMEA, public ListNodeBase<RasEntryName, pctchar>
#endif
{
    private:
     void                       Init();
    public:
                                RasEntryName();
                                RasEntryName(const RasEntryName&);
                                RasEntryName(const tchar*);
     virtual                   ~RasEntryName();

     const RasEntryName&        operator = (const RasEntryName&);

                                operator RASENTRYNAME* ();
                                operator const RASENTRYNAME* ();

     const tchar*               GetEntryName()  const;
};
////////////////////////////////////////////////////////////////////////////////////////
// struct _EntryNameKeyExtractor
// ------ ----------------------
struct _EntryNameKeyExtractor
{
    const pctchar& operator() (const RasEntryName&) const;
};
////////////////////////////////////////////////////////////////////////////////////////
// struct _EntryNameComparator
// ------ --------------------
struct _EntryNameComparator
{
    int operator() (const pctchar&, const pctchar&) const;
};
////////////////////////////////////////////////////////////////////////////////////////
// class RasEntryNames
// ----- -------------
class RasEntryNames : public List<RasEntryName, pctchar, _EntryNameKeyExtractor, _EntryNameComparator>
{
    public:
                    RasEntryNames();
     virtual       ~RasEntryNames();

     void           InitEntries();
    public:

    class XRasEntriesName : public X
    {
        private:
         ulong  ReturnCode;
        public:
                XRasEntriesName(ulong, uint = X::Failure);

        ulong   GetError()  const;
    };

    friend class XRasEntriesName;
};
////////////////////////////////////////////////////////////////////////////////////////
// class RasDialParams
// ----- -------------
#ifdef _UNICODE
class RasDialParams : public tagRASDIALPARAMSW
#else
class RasDialParams : public tagRASDIALPARAMSA
#endif
{
    private:
     void                   Init();
    public:
                            RasDialParams();
                            RasDialParams(const RASDIALPARAMS&);
     virtual               ~RasDialParams();

     const RasDialParams&   operator = (const RasDialParams&);

                            operator RASDIALPARAMS* ();
                            operator const RASDIALPARAMS* ();

     tchar*                 GetEntryName()                          const;
     void                   SetEntryName(const tchar*);

     tchar*                 GetPhoneNumber()                        const;
     void                   SetPhoneNumber(const tchar*);

     tchar*                 GetCallbackPhoneNumber()                const;
     void                   SetCallbackPhoneNumber(const tchar*);

     tchar*                 GetUserName()                           const;
     void                   SetUserName(const tchar*);

     tchar*                 GetPassword()                           const;
     void                   SetPassword(const tchar*);

     tchar*                 GetDomain()                             const;
     void                   SetDomain(const tchar*);
#if (WINVER >= 0x400)
     ulong                  GetSubEntry()                           const;
     void                   SetSubEntry(ulong);

     ulong                  GetCallbackID()                         const;
     void                   SetCallbackID(ulong);
#endif
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __RAS_H__
