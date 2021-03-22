////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __MUTEX_H__
#define __MUTEX_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class Mutex
// ----- -----
class __DECLSPEC__ Mutex : public SyncObjectBase
{
    private:
                    Mutex(const Mutex&);
     const Mutex&   operator = (const Mutex&);
    public:
                    Mutex(const tchar* = null, SECURITY_ATTRIBUTES* = null);
                    Mutex(const tchar*, bool, uint = MUTEX_ALL_ACCESS);
                    Mutex(HANDLE);

     virtual void   Release();
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __MUTEX_H__
