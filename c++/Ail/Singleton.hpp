////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __SINGLETON_H__
#define __SINGLETON_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class SingletonBase
// ----- -------------
class __DECLSPEC__ SingletonBase
{
    public:
     virtual   ~SingletonBase();
};
////////////////////////////////////////////////////////////////////////////////////////
// class Singleton
// ----- ---------
template <typename _Instance, typename _Mutex = Synchronization::ThreadMutex<>, typename _Allocator = StandardAllocator> class Singleton : public SingletonBase, public StateObject
{
    private:
                        Singleton(const Singleton&);
     const Singleton&   operator = (const Singleton&);
    protected:
     static _Instance*  Instance_;
     static _Mutex      Mutex;
    protected:
     static _Instance*  ConstructInstance();
     static void        DestroyInstance(void*);
    public:
     // ctor/dtor
                        Singleton(StateObject::EState = StateObject::eNoDelete, const tchar* = null);
     virtual           ~Singleton();
     
     // access
     static _Instance*  GetInstance();
     static _Instance&  Instance();

     // methods
     static void        Destroy();
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __SINGLETON_H__
