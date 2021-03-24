////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __AIL_H__
#   include <ail.hpp>
#endif

#ifndef __MUTEX_INC__
#   include <Mutex.inc>
#endif

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class Mutex
// ----- -----
Mutex::Mutex(const tchar* _name, SECURITY_ATTRIBUTES* _sa)
{
    Handle = ::CreateMutex(_sa, false, _name);
    
    Assert();
}

Mutex::Mutex(const tchar* _name, bool _inherit, uint _access)
{
    Handle = ::OpenMutex(_access, _inherit, _name);

    Assert();
}

Mutex::Mutex(HANDLE _handle)
{
    ::DuplicateHandle(::GetCurrentProcess(), _handle, ::GetCurrentProcess(), &Handle, 0, false, DUPLICATE_SAME_ACCESS);
    Assert();
}

void Mutex::Release()
{
    Assert(); 
  ::ReleaseMutex(*this);
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__
