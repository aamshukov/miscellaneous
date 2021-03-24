////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __EMAIL_INL__
#define __EMAIL_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class Recipient
// ----- ---------
__INLINE__ const TCharStr& Recipient::GetAddress() const
{
    return Address;
}

__INLINE__ void Recipient::SetAddress(const TCharStr& _address)
{
    Address = _address;
}

__INLINE__ const TCharStr& Recipient::GetName() const
{
    return Name;
}

__INLINE__ void Recipient::SetName(const TCharStr& _name)
{
    Name = _name;
}
////////////////////////////////////////////////////////////////////////////////////////
// class Attachment
// ----- ----------
__INLINE__ uint Attachment::GetPosition() const
{
    return Position;
}

__INLINE__ void Attachment::SetPosition(uint _pos)
{
    Position = _pos;
}

__INLINE__ const TCharStr& Attachment::GetPath() const
{
    return Path;
}

__INLINE__ void Attachment::SetPath(const TCharStr& _path)
{
    Path = _path;
}

__INLINE__ const TCharStr& Attachment::GetFile() const
{
    return File;
}

__INLINE__ void Attachment::SetFile(const TCharStr& _file)
{
    File = _file;
}

__INLINE__ bool Attachment::operator < (const Attachment&)
{
    return false;
}

__INLINE__ bool Attachment::operator == (const Attachment&)
{
    return false;
}
////////////////////////////////////////////////////////////////////////////////////////
// struct _RecKeyExtractor
// ----- -----------------
__INLINE__ const TCharStr& MailMessage::_RecKeyExtractor::operator() (const Recipient& _v) const
{
    return _v.GetName();
}
////////////////////////////////////////////////////////////////////////////////////////
// struct _RecComparator
// ----- ---------------
__INLINE__ int MailMessage::_RecComparator::operator() (const TCharStr& _key1, const TCharStr& _key2) const
{
    return  _key1.Compare(_key2);
}
////////////////////////////////////////////////////////////////////////////////////////
// struct _AttKeyExtractor
// ----- -----------------
__INLINE__ const TCharStr& MailMessage::_AttKeyExtractor::operator() (const Attachment& _v) const
{
    return _v.GetFile();
}
////////////////////////////////////////////////////////////////////////////////////////
// struct _AttComparator
// ----- ---------------
__INLINE__ int MailMessage::_AttComparator::operator() (const TCharStr& _key1, const TCharStr& _key2) const
{
    return  _key1.Compare(_key2);
}
////////////////////////////////////////////////////////////////////////////////////////
// class MailMessage
// ----- -----------
__INLINE__ TCharStr MailMessage::GetObject() const
{
    return Object;
}

__INLINE__ void MailMessage::SetObject(const TCharStr& _object)
{
    Object = _object;
}

__INLINE__ TCharStr MailMessage::GetSubject() const
{
    return Subject;
}

__INLINE__ void MailMessage::SetSubject(const TCharStr& _subject)
{
    Subject = _subject;
}

__INLINE__ TCharStr MailMessage::GetHeader() const
{
    return Header;
}

__INLINE__ void MailMessage::SetHeader(const TCharStr& _header)
{
    Header = _header;
}

__INLINE__ TCharStr MailMessage::GetMessage() const
{
    return Message;
}

__INLINE__ void MailMessage::SetMessage(const TCharStr& _message)
{
    Message = _message;
}

__INLINE__ Time MailMessage::GetTime() const
{
    return TimeStamp;
}

__INLINE__ void MailMessage::SetTime(const Time& _time)
{
    TimeStamp = _time;
}

__INLINE__ List<Attachment, TCharStr, MailMessage::_AttKeyExtractor, MailMessage::_AttComparator>& MailMessage::GetAttachments() const
{
    return const_cast<List<Attachment, TCharStr, MailMessage::_AttKeyExtractor, MailMessage::_AttComparator>&>(Attachments);
}

__INLINE__ void MailMessage::AddAttachment(const TCharStr& _path, const TCharStr& _file, uint _pos)
{
    Attachments.LinkTail(new Attachment(_path, _file, _pos));
}

__INLINE__ void MailMessage::RemoveAttachment(const Attachment* _attachment)
{
    if(_attachment != null)
    {
        Attachments.Unlink(const_cast<Attachment*>(_attachment));
    }
}

__INLINE__ List<Recipient, TCharStr, MailMessage::_RecKeyExtractor, MailMessage::_RecComparator>& MailMessage::GetRecipientsTO() const
{
    return const_cast<List<Recipient, TCharStr, MailMessage::_RecKeyExtractor, MailMessage::_RecComparator>&>(RecipientsTO);
}

__INLINE__ List<Recipient, TCharStr, MailMessage::_RecKeyExtractor, MailMessage::_RecComparator>& MailMessage::GetRecipientsCC() const
{
    return const_cast<List<Recipient, TCharStr, MailMessage::_RecKeyExtractor, MailMessage::_RecComparator>&>(RecipientsCC);
}

__INLINE__ List<Recipient, TCharStr, MailMessage::_RecKeyExtractor, MailMessage::_RecComparator>& MailMessage::GetRecipientsBCC() const
{
    return const_cast<List<Recipient, TCharStr, MailMessage::_RecKeyExtractor, MailMessage::_RecComparator>&>(RecipientsBCC);
}

__INLINE__ void MailMessage::AddRecipientTO(const TCharStr& _address, const TCharStr& _name)
{
    RecipientsTO.LinkTail(new Recipient(_address, _name));
}

__INLINE__ void MailMessage::RemoveRecipientTO(const Recipient* _recipient)
{
    if(_recipient != null)
    {
        RecipientsTO.Unlink(const_cast<Recipient*>(_recipient));
    }
}

__INLINE__ void MailMessage::AddRecipientCC(const TCharStr& _address, const TCharStr& _name)
{
    RecipientsCC.LinkTail(new Recipient(_address, _name));
}

__INLINE__ void MailMessage::RemoveRecipientCC(const Recipient* _recipient)
{
    if(_recipient != null)
    {
        RecipientsCC.Unlink(const_cast<Recipient*>(_recipient));
    }
}

__INLINE__ void MailMessage::AddRecipientBCC(const TCharStr& _address, const TCharStr& _name)
{
    RecipientsBCC.LinkTail(new Recipient(_address, _name));
}

__INLINE__ void MailMessage::RemoveRecipientBCC(const Recipient* _recipient)
{
    if(_recipient != null)
    {
        RecipientsBCC.Unlink(const_cast<Recipient*>(_recipient));
    }
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __EMAIL_INL__
