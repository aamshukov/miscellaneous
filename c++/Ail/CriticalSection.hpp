////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __CRITICALSECTION_H__
#define __CRITICALSECTION_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class CriticalSection
// ----- ---------------
class __DECLSPEC__ CriticalSection
{
    private:
     bool                       Valid;

     CRITICAL_SECTION           CS;
    private:
                                CriticalSection(const CriticalSection&);
     const CriticalSection&     operator = (const CriticalSection&);
    public:
                                CriticalSection();
     virtual                   ~CriticalSection();

     bool                       IsValid()                       const;

     const CRITICAL_SECTION&    GetCriticalSection()            const;

                                operator CRITICAL_SECTION ()    const;
                                operator CRITICAL_SECTION* ()   const;
    public:

    class __DECLSPEC__ Lock
    {
        private:
         const CriticalSection& CSWrap;
        public:
                                Lock(const CriticalSection&);
                               ~Lock();
    };

    friend class Lock;
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __CRITICALSECTION_H__
