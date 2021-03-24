////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __DDE_INL__
#define __DDE_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class DDEString
// ----- ---------
__INLINE__ HSZ DDEString::GetHandle() const
{
    return Text;
}

__INLINE__ bool DDEString::IsShouldFree() const
{
    return ShouldFree;
}

__INLINE__ void DDEString::SetShouldFree(bool flag)
{
    ShouldFree = flag;
}

__INLINE__ void DDEString::Assert()
{
    if(Text == null)
    {
        throw XDDEString();
    }
}

__INLINE__ DDEString::operator HSZ ()
{
    return Text;
}

__INLINE__ bool DDEString::operator == (const DDEString& _other)
{
    return DDEModule::CmpStringHandles(Text, _other.Text) == 0;
}

__INLINE__ bool DDEString::operator < (const DDEString& _other)
{
    return DDEModule::CmpStringHandles(Text, _other.Text) < 0;
}

__INLINE__ bool DDEString::operator > (const DDEString& _other)
{
    return DDEModule::CmpStringHandles(Text, _other.Text) > 0;
}

__INLINE__ void DDEString::CreateString(const String<>& str, int code_page)
{
    if(Text == null)
    {
        ShouldFree = true;
        Text = DDEModule::CreateStringHandle(str, code_page);
        Assert();
    }
}

__INLINE__ void DDEString::GetString(tchar* buffer, uint count, int code_page)
{
    Assert();
    DDEModule::QueryString(Text, buffer, count, code_page);
}

__INLINE__ String<> DDEString::GetString(int code_page)
{
    String<> str(_t(' '), STRING_SIZE);
    //
    Assert();
    DDEModule::QueryString(Text, str, str.GetCount(), code_page);

    return str;
}

__INLINE__ void DDEString::SetString(HSZ hsz)
{
    ShouldFree = false;
    Text = hsz;
    Assert();
}

__INLINE__ bool DDEString::KeepStringHandle()
{
    Assert();
    return DDEModule::KeepStringHandle(Text);
}
////////////////////////////////////////////////////////////////////////////////////////
// class DDEData
// ----- -------
__INLINE__ HDDEDATA DDEData::GetHandle() const
{
    return Data;
}

__INLINE__ bool DDEData::IsShouldFree() const
{
    return ShouldFree;
}

__INLINE__ void DDEData::SetShouldFree(bool flag)
{
    ShouldFree = flag;
}

__INLINE__ void DDEData::Assert()
{
    if(Data == null)
    {
        throw XDDEData();
    }
}

__INLINE__ DDEData::operator HDDEDATA ()
{
    return Data;
}

__INLINE__ bool DDEData::operator == (const DDEData& _other)
{
    return Data == _other.Data;
}

__INLINE__ void DDEData::CreateData(byte* data, uint count, uint countoff, HSZ hsz, uint clipb_fmt, uint flags)
{
    if(Data == null)
    {
        ShouldFree = true;
        Data       = DDEModule::CreateDataHandle(data, count, countoff, hsz, clipb_fmt, flags);

        Assert();
    }
}

__INLINE__ void DDEData::AddData(byte* data, uint count, uint countoff)
{
    Assert();
    Data = DDEModule::AddData(Data, data, count, countoff);
    Assert();
}

__INLINE__ uint DDEData::GetData(byte* buffer, uint count, uint countoff)
{
    Assert();
    return DDEModule::GetData(Data, buffer, count, countoff);
}

__INLINE__ byte* DDEData::AccessData(uint* count)
{
    Assert();
    return DDEModule::AccessData(Data, count);
}

__INLINE__ bool DDEData::UnaccessData()
{
    Assert();
    return DDEModule::UnaccessData(Data);
}

__INLINE__ void DDEData::SetData(HDDEDATA data)
{
    ShouldFree = false;
    Data       = data;

    Assert();
}
////////////////////////////////////////////////////////////////////////////////////////
// class DDEConversation
// ----- ---------------
__INLINE__ const HCONV& DDEConversation::GetConversation() const
{
    return Conversation;
}

__INLINE__ const HSZ& DDEConversation::GetTopic() const
{
    return Topic;
}

__INLINE__ bool DDEConversation::IsAsynchronous() const
{
    return Asynchronous;
}

__INLINE__ void DDEConversation::SetAsynchronous(bool flag)
{
    Asynchronous = flag;
}

__INLINE__ void DDEConversation::Assert()
{
    if(Conversation == null)
    {
        throw XDDEConversation();
    }
}

__INLINE__ DDEConversation::operator HCONV ()
{
    return Conversation;
}
////////////////////////////////////////////////////////////////////////////////////////
// struct _KeyExtractor
// ------ -------------
__INLINE__ const HCONV& DDEServer::_KeyExtractor::operator() (const DDEConversation& _v) const
{
    return _v.GetConversation();
}
////////////////////////////////////////////////////////////////////////////////////////
// struct _Comparator
// ------ -----------
__INLINE__ int DDEServer::_Comparator::operator() (const HCONV& _key1, const HCONV& _key2) const
{
    return ail::Compare<HCONV>(_key1, _key2);
}
////////////////////////////////////////////////////////////////////////////////////////
// class DDEServer
// ----- ---------
__INLINE__ DDEString& DDEServer::GetService() const
{
    return const_cast<DDEString&>(Service);
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __DDE_INL__
