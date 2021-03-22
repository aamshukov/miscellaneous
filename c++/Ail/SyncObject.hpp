////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __SYNCOBJECT_H__
#define __SYNCOBJECT_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class SyncObject
// ----- ----------
class __DECLSPEC__ SyncObject
{
    private:
     CriticalSection    CS;
    protected:
                        SyncObject();
                        SyncObject(const SyncObject&);

     const SyncObject&  operator = (const SyncObject&);
    protected:

    class __DECLSPEC__ Lock : private CriticalSection::Lock
    {
        private:
         static const CriticalSection&  GetCriticalSection(const SyncObject*);
        public:
                                        Lock(const SyncObject*);
    };
     
    friend class Lock;

    public:

    class __DECLSPEC__ XSyncObject : public X
    {
        public:
            XSyncObject(uint = X::Failure);
    };
     
    friend class XSyncObject;
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __SYNCOBJECT_H__
