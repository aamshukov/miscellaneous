////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __COM_MODULE_H__
#define __COM_MODULE_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class ComModule
// ----- ---------
class __DECLSPEC__ ComModule
{
    private:
     refcnt         LockCount;
     HMODULE        HModule;
    public:
     // ctor/dtor
                    ComModule();
     virtual       ~ComModule();

     // access
     refcnt         GetLockCount()          const;

     refcnt         Lock();
     refcnt         Unlock();

     HMODULE        GetHModule()            const;
     void           SetHModule(HMODULE);

                    operator HMODULE ();
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __COM_MODULE_H__
