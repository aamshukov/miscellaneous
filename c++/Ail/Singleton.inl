////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __SINGLETON_INL__
#define __SINGLETON_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class SingletonBase
// ----- -------------
__INLINE__ SingletonBase::~SingletonBase()
{
}
////////////////////////////////////////////////////////////////////////////////////////
// class Singleton
// ----- ---------
template <typename _Instance, typename _Mutex, typename _Allocator> _Instance* Singleton<_Instance, _Mutex, _Allocator>::Instance_ = null;
template <typename _Instance, typename _Mutex, typename _Allocator> _Mutex Singleton<_Instance, _Mutex, _Allocator>::Mutex;
//
template <typename _Instance, typename _Mutex, typename _Allocator>
Singleton<_Instance, _Mutex, _Allocator>::Singleton(StateObject::EState _state, const tchar* _name) : StateObject(_state)
{
}

template <typename _Instance, typename _Mutex, typename _Allocator>
Singleton<_Instance, _Mutex, _Allocator>::~Singleton()
{
    if(ShouldDelete())
    {
        Destroy();
    }
}

template <typename _Instance, typename _Mutex, typename _Allocator>
_Instance* Singleton<_Instance, _Mutex, _Allocator>::ConstructInstance()
{
    void* p = _Allocator::Allocate(sizeof(_Instance));
   _Instance* inst = new (p) _Instance;
    return inst;
}

template <typename _Instance, typename _Mutex, typename _Allocator>
void Singleton<_Instance, _Mutex, _Allocator>::DestroyInstance(void* _p)
{
    if(_p != null)
    {
        reinterpret_cast<_Instance*>(_p)->~_Instance(); // virtual dtor OK
       _Allocator::Deallocate(_p);                      // casting
    }
}

template <typename _Instance, typename _Mutex, typename _Allocator>
_Instance* Singleton<_Instance, _Mutex, _Allocator>::GetInstance()
{
    if(Instance_ == null)
    {
        // double-check pattern
        Synchronization::Guard<_Mutex> guard(Mutex);

        if(Instance_ == null)
        {
            Instance_ = ConstructInstance();
        }
    }
    return Instance_;
}

template <typename _Instance, typename _Mutex, typename _Allocator>
_Instance& Singleton<_Instance, _Mutex, _Allocator>::Instance()
{
    __x_assert__(Singleton<_Instance, _Mutex, _Allocator>::GetInstance() != null);
    return *Singleton<_Instance, _Mutex, _Allocator>::GetInstance();
}

template <typename _Instance, typename _Mutex, typename _Allocator>
void Singleton<_Instance>::Destroy()
{
    if(Instance != null)
    {
        // double-check pattern
        Synchronization::Guard<_Mutex> guard(Mutex);

        if(Instance_ != null)
        {
            DestroyInstance(Instance_), Instance_ = null;
        }
    }
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __SINGLETON_INL__
