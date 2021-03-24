////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __EMAIL_H__
#define __EMAIL_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class Recipient
// ----- ---------
class __DECLSPEC__ Recipient : public ListNodeBase<Recipient, TCharStr>
{
    private:
     TCharStr         Address;
     TCharStr         Name;
    protected:
     virtual bool     operator < (const Recipient&);
     virtual bool     operator == (const Recipient&);
    public:
                      Recipient();
                      Recipient(const Recipient&);
                      Recipient(const TCharStr&, const TCharStr&);
     virtual         ~Recipient();

     const Recipient& operator = (const Recipient&);

     const TCharStr&  GetAddress()                    const;
     void             SetAddress(const TCharStr&);

     const TCharStr&  GetName()                       const;
     void             SetName(const TCharStr&);
};
////////////////////////////////////////////////////////////////////////////////////////
// class Attachment
// ----- ----------
class __DECLSPEC__ Attachment : public ListNodeBase<Attachment, TCharStr>
{
    private:
     uint                   Position;
     TCharStr               Path;
     TCharStr               File;
    private:
     virtual bool           operator < (const Attachment&);
     virtual bool           operator == (const Attachment&);
    public:
                            Attachment();
                            Attachment(const Attachment&);
                            Attachment(const TCharStr&, const TCharStr&, uint = -1);
     virtual               ~Attachment();

     const Attachment&      operator = (const Attachment&);

     uint                   GetPosition()                       const;
     void                   SetPosition(uint = ConstError32);

     const TCharStr&        GetPath()                           const;
     void                   SetPath(const TCharStr&);

     const TCharStr&        GetFile()                           const;
     void                   SetFile(const TCharStr&);
};
////////////////////////////////////////////////////////////////////////////////////////
// class MailMessage
// ----- -----------
class __DECLSPEC__ MailMessage
{
    private:

    struct _RecKeyExtractor
    {
        const TCharStr& operator() (const Recipient&) const;
    };

    struct _RecComparator
    {
        int operator() (const TCharStr&, const TCharStr&) const;
    };

    struct _AttKeyExtractor
    {
        const TCharStr& operator() (const Attachment&) const;
    };

    struct _AttComparator
    {
        int operator() (const TCharStr&, const TCharStr&) const;
    };

    private:
    _RecKeyExtractor            RecKeyExtractor;
    _RecComparator              RecComparator;
    _AttKeyExtractor            AttKeyExtractor;
    _AttComparator              AttComparator;

     TCharStr                   Object;
     TCharStr                   Subject;
     TCharStr                   Header;
     TCharStr                   Message;

     Time                       TimeStamp;

     List<Recipient,
          TCharStr,
         _RecKeyExtractor,
         _RecComparator>        RecipientsTO;
     List<Recipient,
          TCharStr,
         _RecKeyExtractor,
         _RecComparator>        RecipientsCC;
     List<Recipient,
          TCharStr,
         _RecKeyExtractor,
         _RecComparator>        RecipientsBCC;

     List<Attachment,
          TCharStr,
         _AttKeyExtractor,
         _AttComparator>        Attachments;
    private:
                                MailMessage(const MailMessage&);
     const MailMessage&         operator = (const MailMessage&);
    public:
                                MailMessage();
                                MailMessage(const TCharStr&, const TCharStr&, const TCharStr&, const TCharStr&, const Time&);
     virtual                   ~MailMessage();

     TCharStr                   GetObject()                                         const;
     void                       SetObject(const TCharStr&);
     TCharStr                   GetSubject()                                        const;
     void                       SetSubject(const TCharStr&);
     TCharStr                   GetHeader()                                         const;
     void                       SetHeader(const TCharStr&);
     TCharStr                   GetMessage()                                        const;
     void                       SetMessage(const TCharStr&);
     Time                       GetTime()                                           const;
     void                       SetTime(const Time&);

     List<Attachment,
          TCharStr,
         _AttKeyExtractor,
         _AttComparator>&       GetAttachments()                                    const;

     void                       AddAttachment(const TCharStr&, const TCharStr&, uint = ConstError32);
     void                       RemoveAttachment(const Attachment*);

     List<Recipient,
          TCharStr,
         _RecKeyExtractor,
         _RecComparator>&       GetRecipientsTO()                                   const;
     List<Recipient,
          TCharStr,
         _RecKeyExtractor,
         _RecComparator>&       GetRecipientsCC()                                   const;
     List<Recipient,
          TCharStr,
         _RecKeyExtractor,
         _RecComparator>&       GetRecipientsBCC()                                  const;

     Recipient*                 GetRecipientTO(const TCharStr&, const TCharStr&)    const;
     void                       AddRecipientTO(const TCharStr&, const TCharStr&);
     void                       RemoveRecipientTO(const Recipient*);

     Recipient*                 GetRecipientCC(const TCharStr&, const TCharStr&)    const;
     void                       AddRecipientCC(const TCharStr&, const TCharStr&);
     void                       RemoveRecipientCC(const Recipient*);

     Recipient*                 GetRecipientBCC(const TCharStr&, const TCharStr&)   const;
     void                       AddRecipientBCC(const TCharStr&, const TCharStr&);
     void                       RemoveRecipientBCC(const Recipient*);
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __EMAIL_H__
