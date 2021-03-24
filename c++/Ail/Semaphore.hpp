////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __SEMAPHORE_H__
#define __SEMAPHORE_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class Semaphore
// ----- ---------
class __DECLSPEC__ Semaphore : public SyncObjectBase
{
    private:
                        Semaphore(const Semaphore&);
     const Semaphore&   operator = (const Semaphore&);
    public:
                        Semaphore(int = 0, int = 0, const tchar* = null, SECURITY_ATTRIBUTES* = null);
                        Semaphore(const tchar*, bool, uint = SEMAPHORE_ALL_ACCESS);
                        Semaphore(HANDLE);

     virtual void       Release();
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __SEMAPHORE_H__
