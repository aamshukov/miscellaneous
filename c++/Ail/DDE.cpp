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

#ifndef __DDE_INC__
#   include <DDE.inc>
#endif

__BEGIN_NAMESPACE__

static const ushort DDE_TIMEOUT  = 5000;

////////////////////////////////////////////////////////////////////////////////////////
// class DDEModule
// ----- ---------
////////////////////////////////////////////////////////////////////////////////////////
uint DDEModule::Instance = 0;

DDEModule::DDEModule() : Module(_t("USER32.DLL"))
{
}

uint DDEModule::GetInstance()
{
    return Instance;
}

Module& DDEModule::GetDDEModule()
{
    static DDEModule TheModule;
    return TheModule;
}

uint DDEModule::Initialize(PFNCALLBACK func, uint flags)
{
#ifdef _UNICODE
    const char _name[] = "DdeInitializeW";

    static ModuleProc4<uint, uint*, PFNCALLBACK, uint, uint> DdeInitialize(GetDDEModule(), _name);
#else
    const char _name[] = "DdeInitializeA";

    static ModuleProc4<uint, uint*, PFNCALLBACK, uint, uint> DdeInitialize(GetDDEModule(), _name);
#endif
    return DdeInitialize(&Instance, func, flags, 0);
}

bool DDEModule::Uninitialize()
{
    const char _name[] = "DdeUninitialize";

    static ModuleProc1<bool, uint> DdeUninitialize(GetDDEModule(), _name);
    
    bool rc = DdeUninitialize(Instance) != 0;

    Instance = 0;

    return rc;
}

HSZ DDEModule::CreateStringHandle(const tchar* str, int code_page)
{
#ifdef _UNICODE
    const char _name[] = "DdeCreateStringHandleW";

    static ModuleProc3<HSZ, uint, const tchar*, int> DdeCreateStringHandle(GetDDEModule(), _name);
#else
    const char _name[] = "DdeCreateStringHandleA";

    static ModuleProc3<HSZ, uint, const tchar*, int> DdeCreateStringHandle(GetDDEModule(), _name);
#endif
    return DdeCreateStringHandle(Instance, str, code_page);
}

bool DDEModule::FreeStringHandle(HSZ hsz)
{
    const char _name[] = "DdeFreeStringHandle";

    static ModuleProc2<bool, uint, HSZ> DdeFreeStringHandle(GetDDEModule(), _name);
    return DdeFreeStringHandle(Instance, hsz) != 0;
}

bool DDEModule::KeepStringHandle(HSZ hsz)
{
    const char _name[] = "DdeKeepStringHandle";

    static ModuleProc2<bool, uint, HSZ> DdeKeepStringHandle(GetDDEModule(), _name);
    return DdeKeepStringHandle(Instance, hsz) != 0;
}

uint DDEModule::QueryString(HSZ hsz, tchar* buffer, uint count, int code_page)
{
#ifdef _UNICODE
    const char _name[] = "DdeQueryStringW";

    static ModuleProc5<uint, uint, HSZ, tchar*, uint, int> DdeQueryString(GetDDEModule(), _name);
#else
    const char _name[] = "DdeQueryStringA";

    static ModuleProc5<uint, uint, HSZ, tchar*, uint, int> DdeQueryString(GetDDEModule(), _name);
#endif
    return DdeQueryString(Instance, hsz, buffer, count, code_page);
}

short DDEModule::CmpStringHandles(HSZ hsz1, HSZ hsz2)
{
    const char _name[] = "DdeCmpStringHandles";

    static ModuleProc2<short, HSZ, HSZ> DdeCmpStringHandles(GetDDEModule(), _name);
    return short(DdeCmpStringHandles(hsz1, hsz2));
}

HDDEDATA DDEModule::CreateDataHandle(byte* data, uint count, uint countoff, HSZ hsz, uint clipb_fmt, uint flags)
{
    const char _name[] = "DdeCreateDataHandle";

    static ModuleProc7<HDDEDATA, uint, byte*, uint, uint, HSZ, uint, uint> DdeCreateDataHandle(GetDDEModule(), _name);
    return DdeCreateDataHandle(Instance, data, count, countoff, hsz, clipb_fmt, flags);
}

HDDEDATA DDEModule::AddData(HDDEDATA hdata, byte* data, uint count, uint countoff)
{
    const char _name[] = "DdeAddData";

    static ModuleProc5<HDDEDATA, uint, HDDEDATA, byte*, uint, uint> DdeAddData(GetDDEModule(), _name);
    return DdeAddData(Instance, hdata, data, count, countoff);
}

uint DDEModule::GetData(HDDEDATA hdata, byte* data, uint count, uint countoff)
{
    const char _name[] = "DdeGetData";

    static ModuleProc5<uint, uint, HDDEDATA, byte*, uint, uint> DdeGetData(GetDDEModule(), _name);
    return DdeGetData(Instance, hdata, data, count, countoff);
}

byte* DDEModule::AccessData(HDDEDATA hdata, uint* count)
{
    const char _name[] = "DdeAccessData";

    static ModuleProc2<byte*, HDDEDATA, uint*> DdeAccessData(GetDDEModule(), _name);
    return DdeAccessData(hdata, count);
}

bool DDEModule::UnaccessData(HDDEDATA hdata)
{
    const char _name[] = "DdeUnaccessData";

    static ModuleProc1<bool, HDDEDATA> DdeUnaccessData(GetDDEModule(), _name);
    return DdeUnaccessData(hdata) != 0;
}

bool DDEModule::FreeDataHandle(HDDEDATA hdata)
{
    const char _name[] = "DdeFreeDataHandle";

    static ModuleProc1<bool, HDDEDATA> DdeFreeDataHandle(GetDDEModule(), _name);
    return DdeFreeDataHandle(hdata) != 0;
}

HCONV DDEModule::Connect(HSZ service, HSZ topic, CONVCONTEXT* context)
{
    const char _name[] = "DdeConnect";

    static ModuleProc4<HCONV, uint, HSZ, HSZ, CONVCONTEXT*> DdeConnect(GetDDEModule(), _name);
    return DdeConnect(Instance, service, topic, context);
}

HCONVLIST DDEModule::ConnectList(HSZ service, HSZ topic, HCONVLIST list, CONVCONTEXT* context)
{
    const char _name[] = "DdeConnectList";

    static ModuleProc5<HCONVLIST, uint, HSZ, HSZ, HCONVLIST, CONVCONTEXT*> DdeConnectList(GetDDEModule(), _name);
    return DdeConnectList(Instance, service, topic, list, context);
}

bool DDEModule::Disconnect(HCONV conv)
{
    const char _name[] = "DdeDisconnect";

    static ModuleProc1<bool, HCONV> DdeDisconnect(GetDDEModule(), _name);
    return DdeDisconnect(conv) != 0;
}

bool DDEModule::DisconnectList(HCONVLIST list)
{
    const char _name[] = "DdeDisconnectList";

    static ModuleProc1<bool, HCONVLIST> DdeDisconnect(GetDDEModule(), _name);
    return DdeDisconnectList(list) != 0;
}

HCONV DDEModule::Reconnect(HCONV conv)
{
    const char _name[] = "DdeReconnect";

    static ModuleProc1<HCONV, HCONV> DdeReconnect(GetDDEModule(), _name);
    return DdeReconnect(conv);
}

uint DDEModule::GetLastError()
{
    const char _name[] = "DdeGetLastError";

    static ModuleProc1<uint, uint> DdeGetLastError(GetDDEModule(), _name);
    return DdeGetLastError(Instance);
}

bool DDEModule::EnableCallback(HCONV conv, uint flags)
{
    const char _name[] = "DdeEnableCallback";

    static ModuleProc3<bool, uint, HCONV, uint> DdeEnableCallback(GetDDEModule(), _name);
    return DdeEnableCallback(Instance, conv, flags) != 0;
}

HDDEDATA DDEModule::NameService(HSZ service, uint flags)
{
    const char _name[] = "DdeNameService";

    static ModuleProc4<HDDEDATA, uint, HSZ, HSZ, uint> DdeNameService(GetDDEModule(), _name);
    return DdeNameService(Instance, service, 0, flags);
}

bool DDEModule::ImpersonateClient(HCONV conv)
{
    const char _name[] = "DdeImpersonateClient";

    static ModuleProc1<bool, HCONV> DdeImpersonateClient(GetDDEModule(), _name);
    return DdeImpersonateClient(conv) != 0;
}

uint DDEModule::QueryConvInfo(HCONV conv, uint id, CONVINFO* info)
{
    const char _name[] = "DdeQueryConvInfo";

    static ModuleProc3<uint, HCONV, uint, CONVINFO*> DdeQueryConvInfo(GetDDEModule(), _name);
    return DdeQueryConvInfo(conv, id, info);
}

HCONV DDEModule::QueryNextServer(HCONVLIST list, HCONV prev)
{
    const char _name[] = "DdeQueryNextServer";

    static ModuleProc2<HCONV, HCONVLIST, HCONV> DdeQueryNextServer(GetDDEModule(), _name);
    return DdeQueryNextServer(list, prev);
}

bool DDEModule::SetUserHandle(HCONV conv, uint id, uint user)
{
    const char _name[] = "DdeSetUserHandle";

    static ModuleProc3<bool, HCONV, uint, uint> DdeSetUserHandle(GetDDEModule(), _name);
    return DdeSetUserHandle(conv, id, user) != 0;
}

HDDEDATA DDEModule::ClientTransaction(byte* data, uint count, HCONV conv, HSZ hsz, uint clipb_fmt, uint type, uint timeout, uint* result)
{
    const char _name[] = "DdeClientTransaction";

    static ModuleProc8<HDDEDATA, byte*, uint, HCONV, HSZ, uint, uint, uint, uint*> DdeClientTransaction(GetDDEModule(), _name);
    return DdeClientTransaction(data, count, conv, hsz, clipb_fmt, type, timeout, result);
}

bool DDEModule::AbandonTransaction(HCONV conv, uint id)
{
    const char _name[] = "DdeAbandonTransaction";

    static ModuleProc3<bool, uint, HCONV, uint> DdeAbandonTransaction(GetDDEModule(), _name);
    return DdeAbandonTransaction(Instance, conv, id) != 0;
}

bool DDEModule::PostAdvise(HSZ topic, HSZ item)
{
    const char _name[] = "DdePostAdvise";

    static ModuleProc3<bool, uint, HSZ, HSZ> DdePostAdvise(GetDDEModule(), _name);
    return DdePostAdvise(Instance, topic, item) != 0;
}
////////////////////////////////////////////////////////////////////////////////////////
// class DDEString
// ----- ---------
DDEString::DDEString()
{
    ShouldFree = false;
    Text       = null;
}

DDEString::DDEString(HSZ hsz, bool free)
{
    ShouldFree = free;
    Text     = hsz;

    Assert();
}

DDEString::DDEString(const DDEString& other)
{
    operator = (other);
}

DDEString::DDEString(const tchar* str, int code_page)
{
    ShouldFree = true;
    Text       = DDEModule::CreateStringHandle(str, code_page);

    Assert();
}

DDEString::DDEString(const String<>& str, int code_page)
{
    ShouldFree = true;
    Text       = DDEModule::CreateStringHandle(str, code_page);

    Assert();
}

DDEString::~DDEString()
{
    if(ShouldFree)
    {
        Assert();
        DDEModule::FreeStringHandle(Text);
    }
    Text = null;
}

const DDEString& DDEString::operator = (const DDEString& _other)
{
    if(this != &_other)
    {
        Text = _other.Text;

        KeepStringHandle();
    }
    return *this;
}

DDEString::XDDEString::XDDEString(uint _error) : X(_error)
{
}
////////////////////////////////////////////////////////////////////////////////////////
// class DDEData
// ----- -------
DDEData::DDEData()
{
    ShouldFree = false;
    Data       = null;
}

DDEData::DDEData(HDDEDATA data, bool free)
{
    ShouldFree = free;
    Data       = data;

    Assert();
}

DDEData::DDEData(byte* data, uint count, uint countoff, HSZ hsz, uint clipb_fmt, uint flags)
{
    ShouldFree = true;
    Data       = DDEModule::CreateDataHandle(data, count, countoff, hsz, clipb_fmt, flags);

    Assert();
}

DDEData::~DDEData()
{
    if(ShouldFree)
    {
        Assert();
        DDEModule::FreeDataHandle(Data);
    }
    Data = null;
}

DDEData::XDDEData::XDDEData(uint _error) : X(_error)
{
}
////////////////////////////////////////////////////////////////////////////////////////
// class DDEConversation
// ----- ---------------
DDEConversation::DDEConversation()
{
    Asynchronous = false;
    Conversation = null;
    Topic        = null;
}

DDEConversation::DDEConversation(HCONV hconv, HSZ htopic)
{
    Asynchronous = false;
    Conversation = hconv;
    Topic        = htopic;

    Assert();
    AddReference();
}

DDEConversation::~DDEConversation()
{
    Disconnect();
}

void DDEConversation::Connect(DDEString& service, DDEString& topic)
{
    Lock lock();

    Conversation = DDEModule::Connect(HSZ(service), HSZ(topic), null);

    Assert();
    AddReference();
}

void DDEConversation::Disconnect()
{
    Lock lock();

    if(Conversation != null)
    {
        DDEModule::Disconnect(*this);
        Conversation = null;
    }
}

HDDEDATA DDEConversation::AdviseStart(DDEString& item)
{
    Lock lock();

    Assert();

    uint result = 0;

    return DDEModule::ClientTransaction(null, 0, Conversation, HSZ(item), CF_TEXT, XTYP_ADVSTART, Asynchronous ? TIMEOUT_ASYNC : DDE_TIMEOUT, &result);
}

HDDEDATA DDEConversation::AdviseStop(DDEString& item)
{
    Lock lock();

    Assert();

    uint result = 0;

    return DDEModule::ClientTransaction(null, 0, Conversation, HSZ(item), CF_TEXT, XTYP_ADVSTOP, Asynchronous ? TIMEOUT_ASYNC : DDE_TIMEOUT, &result);
}

HDDEDATA DDEConversation::Execute(const tchar* command)
{
    Lock lock();

    Assert();

    uint result = 0;

    return DDEModule::ClientTransaction((byte*)command, (StrLen(command)+1)*sizeof(tchar), Conversation, 0, CF_TEXT, XTYP_EXECUTE, Asynchronous ? TIMEOUT_ASYNC : DDE_TIMEOUT, &result);
}

HDDEDATA DDEConversation::Send(uint clib_fmt, DDEString& item, void* data, uint count)
{
    Lock lock();

    Assert();

    uint result = 0;

    return DDEModule::ClientTransaction((byte*)data, count, Conversation, HSZ(item), CF_TEXT, XTYP_POKE, Asynchronous ? TIMEOUT_ASYNC : DDE_TIMEOUT, &result);
}

HDDEDATA DDEConversation::Request(DDEString& item, void** buffer, uint* count)
{
    Lock lock();

    uint result = 0;

    *buffer = null;
    *count  = 0;

    Assert();

    HDDEDATA hdata = DDEModule::ClientTransaction(null, 0, Conversation, HSZ(item), CF_TEXT, XTYP_REQUEST, Asynchronous ? TIMEOUT_ASYNC : DDE_TIMEOUT, &result);

    if(!Asynchronous && DDEModule::GetLastError() == DMLERR_NO_ERROR)
    {    
        DDEData ddedata(hdata, true);

        byte* data = ddedata.AccessData(count);

        if(*count > 0)
        {
            *buffer = new byte[*count];
            memcpy(*buffer, data, *count);
        }

        ddedata.UnaccessData();
        return null;
    }

    return hdata;
}

bool DDEConversation::operator < (const DDEConversation&)
{
    return false;
}

bool DDEConversation::operator == (const DDEConversation&)
{
    return false;
}

uint DDEConversation::AddReference()
{
    Lock lock(this);
    return ++Reference;
}

uint DDEConversation::ReleaseReference()
{
    Lock lock(this);

    if(--Reference == 0)
    {
        delete this;
        return 0;
    }

    return Reference;
}

DDEConversation::XDDEConversation::XDDEConversation(uint _error) : X(_error)
{
}
////////////////////////////////////////////////////////////////////////////////////////
// class DDETransaction
// ----- --------------
DDETransaction::DDETransaction()
{
    Type            = null;
    ClipboardFormat = null;
    Conversation    = null;
    Topic           = null;
    Item            = null;
    Data            = null;
    Data1           = null;
    Data2           = null;
}

DDETransaction::DDETransaction(WORD type, WORD clipb_fmt, HCONV hconv, HSZ htopic, HSZ hitem, HDDEDATA data, DWORD data1, DWORD data2)
{
    Type            = type;
    ClipboardFormat = clipb_fmt;
    Conversation    = hconv;
    Topic           = htopic;
    Item            = hitem;
    Data            = data;
    Data1           = data1;
    Data2           = data2;
}
////////////////////////////////////////////////////////////////////////////////////////
// class DDEServer
// ----- ---------
DDEServer* DDEServer::TheServer = null;

DDEServer::DDEServer() : ConversationList(KeyExtractor, Comparator)
{
}

DDEServer::~DDEServer()
{
    ListIterator<DDEConversation, HCONV> i(ConversationList.GetHead());

    for(; i; i++)
    {
        i.Current().Disconnect();
    }

    DDEModule::NameService(Service, DNS_UNREGISTER);

    if(TheServer == this)
    {
        TheServer = null;
    }
}

void DDEServer::Create(const tchar* service_name, uint flags)
{
    flags &= ~(CBF_FAIL_CONNECTIONS | CBF_SKIP_CONNECT_CONFIRMS | CBF_SKIP_DISCONNECTS);

    if(DDEModule::Initialize((PFNCALLBACK)&DDECallback, flags) == DMLERR_NO_ERROR)
    {
        TheServer = this;

        Service.CreateString(service_name);
        DDEModule::NameService(Service, DNS_REGISTER);

        if(DDEModule::GetLastError() != DMLERR_NO_ERROR)
        {
            throw XDDEServer();
        }
    }
    else
    {
        throw XDDEServer();
    }

    SetupServer();
}

bool DDEServer::CheckConversationTopic(HCONV hconv, HSZ htopic)
{
    ListIterator<DDEConversation, HCONV> i(ConversationList.GetHead());

    for(; i; i++)
    {
        if(HCONV(i.Current()) == hconv && i.Current().GetTopic() == htopic)
        {
            return true;
        }
    }

    return false;
}

void DDEServer::AddConversation(HCONV hconv, HSZ htopic)
{
    DDEConversation* conversation = (DDEConversation*) new DDEConversation(hconv, htopic);
    ConversationList.LinkTail(conversation);
    conversation->AddReference();
}

void DDEServer::RemoveConversation(HCONV hconv)
{
    ListIterator<DDEConversation, HCONV> i(ConversationList.GetHead());

    for(; i; i++)
    {
        if(HCONV(i.Current()) == hconv)
        {
            ConversationList.Unlink((DDEConversation*)i.GetCurrentNode());
            i.Current().ReleaseReference();
            break;
        }
    }
}

void DDEServer::SetupServer()
{
}

HDDEDATA DDEServer::OnXTypeAdviseData(const DDETransaction& transaction)
{
    return null;
}

HDDEDATA DDEServer::OnXTypeAdviseRequest(const DDETransaction& transaction)
{
    return null;
}

HDDEDATA DDEServer::OnXTypeAdviseStart(const DDETransaction& transaction)
{
    return null;
}

HDDEDATA DDEServer::OnXTypeAdviseStop(const DDETransaction& transaction)
{
    return null;
}

HDDEDATA DDEServer::OnXTypeConnect(const DDETransaction& transaction)
{
    return null;
}

HDDEDATA DDEServer::OnXTypeConnectConfirm(const DDETransaction& transaction)
{
    TheServer->AddConversation(transaction.Conversation, transaction.Topic);
    return null;
}

HDDEDATA DDEServer::OnXTypeDisconnect(const DDETransaction& transaction)
{
    TheServer->RemoveConversation(transaction.Conversation);
    return null;
}

HDDEDATA DDEServer::OnXTypeError(const DDETransaction& transaction)
{
    return null;
}

HDDEDATA DDEServer::OnXTypeExecute(const DDETransaction& transaction)
{
    return null;
}

HDDEDATA DDEServer::OnXTypeMonitor(const DDETransaction& transaction)
{
    return null;
}

HDDEDATA DDEServer::OnXTypePoke(const DDETransaction& transaction)
{
    return null;
}

HDDEDATA DDEServer::OnXTypeRegister(const DDETransaction& transaction)
{
    return null;
}

HDDEDATA DDEServer::OnXTypeRequest(const DDETransaction& transaction)
{
    return null;
}

HDDEDATA DDEServer::OnXTypeUnregister(const DDETransaction& transaction)
{
    return null;
}

HDDEDATA DDEServer::OnXTypeWildConnect(const DDETransaction& transaction)
{
    return null;
}

HDDEDATA DDEServer::OnXTypeXActComplete(const DDETransaction& transaction)
{
    return null;
}

HDDEDATA DDEServer::CustomCallback(WORD, WORD, HCONV, HSZ, HSZ, HDDEDATA, DWORD, DWORD)
{
    return null;
}

HDDEDATA CALLBACK DDEServer::DDECallback(WORD type, WORD clipb_fmt, HCONV hconv, HSZ htopic, HSZ hitem, HDDEDATA data, DWORD data1, DWORD data2)
{
    if(TheServer == null)
    {
        return null;
    }

    DDETransaction transaction(type, clipb_fmt, hconv, htopic, hitem, data, data1, data2);

    switch(type)
    {
        case XTYP_ADVDATA:
            if(TheServer->CheckConversationTopic(hconv, htopic))
            {
                return TheServer->OnXTypeAdviseData(transaction);
            }
            break;
        case XTYP_ADVREQ:
            if(TheServer->CheckConversationTopic(hconv, htopic))
            {
                return TheServer->OnXTypeAdviseRequest(transaction);
            }
            break;
        case XTYP_ADVSTART:
            if(TheServer->CheckConversationTopic(hconv, htopic))
            {
                return TheServer->OnXTypeAdviseStart(transaction);
            }
            break;
        case XTYP_ADVSTOP:
            return TheServer->OnXTypeAdviseStop(transaction);
        case XTYP_CONNECT:
            if(TheServer->CheckConversationTopic(hconv, htopic))
            {
                return TheServer->OnXTypeConnect(transaction);
            }
            break;
        case XTYP_CONNECT_CONFIRM:
            return TheServer->OnXTypeConnectConfirm(transaction);
        case XTYP_DISCONNECT:
            return TheServer->OnXTypeDisconnect(transaction);
        case XTYP_ERROR:
            return TheServer->OnXTypeError(transaction);
        case XTYP_EXECUTE:
            if(TheServer->CheckConversationTopic(hconv, htopic))
            {
                return TheServer->OnXTypeExecute(transaction);
            }
            break;
        case XTYP_MONITOR:
            return TheServer->OnXTypeMonitor(transaction);
        case XTYP_POKE:
            if(TheServer->CheckConversationTopic(hconv, htopic))
            {
                return TheServer->OnXTypePoke(transaction);
            }
            break;
        case XTYP_REGISTER:
            return TheServer->OnXTypeRegister(transaction);
        case XTYP_REQUEST:
            if(TheServer->CheckConversationTopic(hconv, htopic))
            {
                return TheServer->OnXTypeRequest(transaction);
            }
            break;
        case XTYP_UNREGISTER:
            return TheServer->OnXTypeUnregister(transaction);
        case XTYP_WILDCONNECT:
            return TheServer->OnXTypeWildConnect(transaction);
        case XTYP_XACT_COMPLETE:
            return TheServer->OnXTypeXActComplete(transaction);
        default:
            return TheServer->CustomCallback(type, clipb_fmt, hconv, htopic, hitem, data, data1, data2);
    }

    return null;
}                                                                            

DDEServer::XDDEServer::XDDEServer(uint _error) : X(_error)
{
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__
