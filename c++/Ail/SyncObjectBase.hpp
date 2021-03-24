////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __SYNCOBJECTBASE_H__
#define __SYNCOBJECTBASE_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class SyncObjectBase
// ----- --------------
class __DECLSPEC__ SyncObjectBase
{
    public:
     enum EState
     {
        NoWait  = 0,
        NoLimit = INFINITE
     };
    protected:
     HANDLE         Handle; 
    protected:
     virtual void   Release() = 0;
     virtual void   Assert();
    public:
                    SyncObjectBase();
                   ~SyncObjectBase();

                    operator HANDLE()   const;

     HANDLE         GetHandle()         const;
    public:

    class __DECLSPEC__ Lock 
    {
        private:
         const SyncObjectBase*  SO;
        public:
                                Lock(const SyncObjectBase&, uint = SyncObjectBase::NoLimit, bool = false);
                               ~Lock();

         bool                   WasAquired()    const;
         void                   Release(bool = false);
    };

    friend class Lock;

    class __DECLSPEC__ XSyncObjectBase : public X
    {
        public:
            XSyncObjectBase(uint = X::Failure);
    };

    friend class XSyncObjectBase;
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __SYNCOBJECTBASE_H__
