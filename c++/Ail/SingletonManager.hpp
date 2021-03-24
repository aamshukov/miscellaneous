////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __SINGLETON_MANAGER_H__
#define __SINGLETON_MANAGER_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class SingletonManager
// ----- ----------------
class __DECLSPEC__ SingletonManager
{
    typedef Synchronization::NullThreadMutex<>  _NullMutex;
    typedef Synchronization::ThreadMutex<>      _Mutex;
    typedef Array<void*, _NullMutex>            _Array;

    private:
    _Array                      Handles;
    _Mutex                      Mutex;
    private:
                                SingletonManager(const SingletonManager&);
     const SingletonManager&    operator = (const SingletonManager&);
    public:
     // ctor/dtor
                                SingletonManager(ushort = 8);
                               ~SingletonManager();
     // protocol
     void                       Register(void*);
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __SINGLETON_MANAGER_H__
