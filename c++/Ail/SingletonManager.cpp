////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __AIL_H__
#   include <ail.hpp>
#endif

#ifndef __SINGLETON_MANAGER_H__
#   include <SingletonManager.inc>
#endif

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class SingletonManager
// ----- ----------------
SingletonManager::SingletonManager(ushort _size)
                : Handles(_size, 2)
{
}

SingletonManager::~SingletonManager()
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    //
    for(int i = Handles.GetCount()-1; i >= 0; i--)
    {
        if(Handles[i] != null)
        {
//??
            reinterpret_cast<SingletonBase*>(Handles[i])->~SingletonBase(), Handles[i] = null;
        }
    }
}

void SingletonManager::Register(void* _singleton)
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    //
    for(uint i = 0; i < Handles.GetCount(); i++)
    {
        if(Handles[i] == null)
        {
            Handles[i] = _singleton;
            return;
        }
    }
    Handles.Resize(Handles.GetCount()+2);
    Handles[i] = _singleton;
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__
