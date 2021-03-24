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

#ifndef __EMAIL_INC__
#   include <eMail.inc>
#endif

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class Recipient
// ----- ---------
Recipient::Recipient()
{
}

Recipient::Recipient(const Recipient& _other)
{
    operator = (_other);
}

Recipient::Recipient(const TCharStr& _address, const TCharStr& _name)
{
    Address = _address;
    Name    = _name;
}

Recipient::~Recipient()
{
}

const Recipient& Recipient::operator = (const Recipient& _other)
{
    if(this != &_other)
    {
        Address = _other.Address;
        Name    = _other.Name;
    }
    return *this;
}

bool Recipient::operator < (const Recipient&)
{
    return false;
}

bool Recipient::operator == (const Recipient&)
{
    return false;
}
////////////////////////////////////////////////////////////////////////////////////////
// class Attachment
// ----- ----------
Attachment::Attachment()
{
    Position = ConstError32;
}

Attachment::Attachment(const Attachment& _other)
{
    operator = (_other);
}

Attachment::Attachment(const TCharStr& _path, const TCharStr& _file, uint _pos)
{
    Position = _pos;
    Path     = _path;
    File     = _file;
}

Attachment::~Attachment()
{
}

const Attachment& Attachment::operator = (const Attachment& _other)
{
    if(this != &_other)
    {
        Position = _other.Position;
        Path     = _other.Path;
        File     = _other.File;
    }
    return *this;
}
////////////////////////////////////////////////////////////////////////////////////////
// class MailMessage
// ----- -----------
MailMessage::MailMessage()
           : RecipientsTO(RecKeyExtractor, RecComparator),
             RecipientsCC(RecKeyExtractor, RecComparator),
             RecipientsBCC(RecKeyExtractor,RecComparator),
             Attachments(AttKeyExtractor,  AttComparator)
{
}

MailMessage::MailMessage(const TCharStr& _object, const TCharStr& _subject, const TCharStr& _header, const TCharStr& _message, const Time& _time)
           : RecipientsTO(RecKeyExtractor, RecComparator),
             RecipientsCC(RecKeyExtractor, RecComparator),
             RecipientsBCC(RecKeyExtractor,RecComparator),
             Attachments(AttKeyExtractor,  AttComparator),
             Object(_object), Subject(_subject), Header(_header), Message(_message), TimeStamp(_time)
{
}

MailMessage::~MailMessage()
{
}

Recipient* MailMessage::GetRecipientTO(const TCharStr& _address, const TCharStr& _name) const
{
    ListIterator<Recipient, TCharStr> i(RecipientsTO.GetHead());

    for(; i; i++)
    {
        if(i.Current().GetAddress() == _address && i.Current().GetName() == _name)
        {
            return &i.Current();
        }
    }

    return null;
}

Recipient* MailMessage::GetRecipientCC(const TCharStr& _address, const TCharStr& _name) const
{
    ListIterator<Recipient, TCharStr> i(RecipientsCC.GetHead());

    for(; i; i++)
    {
        if(i.Current().GetAddress() == _address && i.Current().GetName() == _name)
        {
            return &i.Current();
        }
    }

    return null;
}

Recipient* MailMessage::GetRecipientBCC(const TCharStr& _address, const TCharStr& _name) const
{
    ListIterator<Recipient, TCharStr> i(RecipientsBCC.GetHead());

    for(; i; i++)
    {
        if(i.Current().GetAddress() == _address && i.Current().GetName() == _name)
        {
            return &i.Current();
        }
    }

    return null;
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__
