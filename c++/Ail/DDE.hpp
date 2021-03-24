////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __DDE_H__
#define __DDE_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class DDEModule
// ----- ---------
class __DECLSPEC__ DDEModule : public Module
{
    friend class DDEString;

    private:
     static uint        Instance;
    public:
                        DDEModule();

     static uint        GetInstance();
     static Module&     GetDDEModule();

     static uint        Initialize(PFNCALLBACK, uint);
     static bool        Uninitialize();

     static HSZ         CreateStringHandle(const tchar*, int);
     static bool        FreeStringHandle(HSZ);
     static bool        KeepStringHandle(HSZ);
     static uint        QueryString(HSZ, tchar*, uint, int);
     static short       CmpStringHandles(HSZ, HSZ);

     static HDDEDATA    CreateDataHandle(byte*, uint, uint, HSZ, uint, uint);
     static HDDEDATA    AddData(HDDEDATA, byte*, uint, uint);
     static uint        GetData(HDDEDATA, byte*, uint, uint);
     static byte*       AccessData(HDDEDATA, uint*);
     static bool        UnaccessData(HDDEDATA);
     static bool        FreeDataHandle(HDDEDATA);

     static HCONV       Connect(HSZ, HSZ, CONVCONTEXT*);
     static HCONVLIST   ConnectList(HSZ, HSZ, HCONVLIST, CONVCONTEXT*);
     static bool        Disconnect(HCONV);
     static bool        DisconnectList(HCONVLIST);
     static HCONV       Reconnect(HCONV);

     static uint        GetLastError();

     static bool        EnableCallback(HCONV, uint);

     static HDDEDATA    NameService(HSZ, uint);

     static bool        ImpersonateClient(HCONV);
     static uint        QueryConvInfo(HCONV, uint, CONVINFO*);
     static HCONV       QueryNextServer(HCONVLIST, HCONV);
     static bool        SetUserHandle(HCONV, uint, uint);
     static HDDEDATA    ClientTransaction(byte*, uint, HCONV, HSZ, uint, uint, uint, uint*);
     static bool        AbandonTransaction(HCONV, uint);
     static bool        PostAdvise(HSZ, HSZ);
};
////////////////////////////////////////////////////////////////////////////////////////
// class DDEString
// ----- ---------
class __DECLSPEC__ DDEString
{
    private:
     bool               ShouldFree;
     HSZ                Text;
    protected:
     void               Assert();
    public:
                        DDEString();
                        DDEString(HSZ, bool = false);
                        DDEString(const DDEString&);
#ifdef _UNICODE
                        DDEString(const tchar*, int = CP_WINUNICODE);
                        DDEString(const String<>&, int = CP_WINUNICODE);
#else
                        DDEString(const tchar*, int = CP_WINANSI);
                        DDEString(const String<>&, int = CP_WINANSI);
#endif
     virtual           ~DDEString();

     HSZ                GetHandle()                     const;
     bool               IsShouldFree()                  const;
     void               SetShouldFree(bool = true);

     const DDEString&   operator = (const DDEString&);

                        operator HSZ ();

     bool               operator == (const DDEString&);
     bool               operator <  (const DDEString&);
     bool               operator >  (const DDEString&);

#ifdef _UNICODE
     void               CreateString(const String<>&, int = CP_WINUNICODE);
     void               GetString(tchar*, uint, int = CP_WINUNICODE);
     String<>           GetString(int = CP_WINUNICODE);
#else
     void               CreateString(const String<>&, int = CP_WINANSI);
     void               GetString(tchar*, uint, int = CP_WINANSI);
     String<>           GetString(int = CP_WINANSI);
#endif
     void               SetString(HSZ);

     bool               KeepStringHandle();

    public:

    class __DECLSPEC__ XDDEString : public X
    {
        public:
            XDDEString(uint = X::Failure);
    };

    friend class XDDEString;
};
////////////////////////////////////////////////////////////////////////////////////////
// class DDEData
// ----- -------
class __DECLSPEC__ DDEData
{
    private:
     bool           ShouldFree;
     HDDEDATA       Data;
    private:
     const DDEData& operator = (const DDEData&);
                    DDEData(const DDEData&);
    protected:
     void           Assert();
    public:
                    DDEData();
                    DDEData(HDDEDATA, bool = false);
                    DDEData(byte*, uint, uint, HSZ, uint, uint);
     virtual       ~DDEData();

     HDDEDATA       GetHandle()                     const;

     bool           IsShouldFree()                  const;
     void           SetShouldFree(bool = true);

                    operator HDDEDATA ();
     bool           operator == (const DDEData&);

     void           CreateData(byte*, uint, uint, HSZ, uint, uint);
     void           AddData(byte*, uint, uint);
     uint           GetData(byte*, uint, uint);
     void           SetData(HDDEDATA);
     byte*          AccessData(uint*);
     bool           UnaccessData();
    public:
    class __DECLSPEC__ XDDEData : public X
    {
        public:
            XDDEData(uint = X::Failure);
    };

    friend class XDDEData;
};
////////////////////////////////////////////////////////////////////////////////////////
// class DDEConversation
// ----- ---------------
class __DECLSPEC__ DDEConversation : private ListNodeBase<DDEConversation, HCONV>, private ObjectRef<>, private SyncObject
{
    friend class DDEServer;

    private:
     bool                    Asynchronous;
     HCONV                   Conversation;
     HSZ                     Topic;
    private:
                             DDEConversation(const DDEConversation&);
     const DDEConversation&  operator = (const DDEConversation&);

     virtual bool            operator < (const DDEConversation&);
     virtual bool            operator == (const DDEConversation&);

     virtual uint            AddReference();
     virtual uint            ReleaseReference();
    protected:
     void                    Assert();
    public:
                             DDEConversation();
                             DDEConversation(HCONV, HSZ);
     virtual                ~DDEConversation();

     const HCONV&            GetConversation()                  const;
     const HSZ&              GetTopic()                         const;
     bool                    IsAsynchronous()                   const;
     void                    SetAsynchronous(bool = true);

                             operator HCONV ();

     void                    Connect(DDEString&, DDEString&);
     void                    Disconnect();

     HDDEDATA                AdviseStart(DDEString&);
     HDDEDATA                AdviseStop(DDEString&);
     HDDEDATA                Execute(const tchar*);
     HDDEDATA                Send(uint, DDEString&, void*, uint);
     HDDEDATA                Request(DDEString&, void**, uint*);
    public:

    class __DECLSPEC__ XDDEConversation : public X
    {
        public:
            XDDEConversation(uint = X::Failure);
    };

    friend class XDDEConversation;
};
////////////////////////////////////////////////////////////////////////////////////////
// class DDETransaction
// ----- --------------
class __DECLSPEC__ DDETransaction
{
    public:
     WORD       Type;
     UINT       ClipboardFormat;
     HCONV      Conversation;
     HSZ        Topic;
     HSZ        Item;
     HDDEDATA   Data;
     DWORD      Data1;
     DWORD      Data2;
    public:
                DDETransaction();
                DDETransaction(WORD, WORD, HCONV, HSZ, HSZ, HDDEDATA, DWORD, DWORD);
};
////////////////////////////////////////////////////////////////////////////////////////
// class DDEServer
// ----- ---------
class __DECLSPEC__ DDEServer
{
    private:

    struct _KeyExtractor
    {
        const HCONV& operator() (const DDEConversation&) const;
    };

    struct _Comparator
    {
        int operator() (const HCONV&, const HCONV&) const;
    };

    private:
    _KeyExtractor               KeyExtractor;
    _Comparator                 Comparator;

     DDEString                  Service;

     List<DDEConversation, 
          HCONV, 
         _KeyExtractor, 
         _Comparator>           ConversationList;

     static DDEServer*          TheServer;
    private:
                                DDEServer(const DDEServer&);
     const DDEServer&           operator = (const DDEServer&);

     bool                       CheckConversationTopic(HCONV, HSZ);
     void                       AddConversation(HCONV, HSZ);
     void                       RemoveConversation(HCONV);

     static HDDEDATA CALLBACK   DDECallback(WORD, WORD, HCONV, HSZ, HSZ, HDDEDATA, DWORD, DWORD);
    protected:
     virtual void               SetupServer();

     virtual HDDEDATA           OnXTypeAdviseData(const DDETransaction&);
     virtual HDDEDATA           OnXTypeAdviseRequest(const DDETransaction&);
     virtual HDDEDATA           OnXTypeAdviseStart(const DDETransaction&);
     virtual HDDEDATA           OnXTypeAdviseStop(const DDETransaction&);
     virtual HDDEDATA           OnXTypeConnect(const DDETransaction&);
     virtual HDDEDATA           OnXTypeConnectConfirm(const DDETransaction&);
     virtual HDDEDATA           OnXTypeDisconnect(const DDETransaction&);
     virtual HDDEDATA           OnXTypeError(const DDETransaction&);
     virtual HDDEDATA           OnXTypeExecute(const DDETransaction&);
     virtual HDDEDATA           OnXTypeMonitor(const DDETransaction&);
     virtual HDDEDATA           OnXTypePoke(const DDETransaction&);
     virtual HDDEDATA           OnXTypeRegister(const DDETransaction&);
     virtual HDDEDATA           OnXTypeRequest(const DDETransaction&);
     virtual HDDEDATA           OnXTypeUnregister(const DDETransaction&);
     virtual HDDEDATA           OnXTypeWildConnect(const DDETransaction&);
     virtual HDDEDATA           OnXTypeXActComplete(const DDETransaction&);

     virtual HDDEDATA           CustomCallback(WORD, WORD, HCONV, HSZ, HSZ, HDDEDATA, DWORD, DWORD);
    public:
                                DDEServer();
     virtual                   ~DDEServer();
    
     DDEString&                 GetService()                    const;

     void                       Create(const tchar*, uint = 0);
     void                       Create(const String<>&, uint = 0);
    public:

    class __DECLSPEC__ XDDEServer : public X
    {
        public:
            XDDEServer(uint = X::Failure);
    };

    friend class XDDEServer;
};          
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __DDE_H__
