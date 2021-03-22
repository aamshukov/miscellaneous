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

#ifndef __SEMAPHORE_INC__
#   include <Semaphore.inc>
#endif

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class Semaphore
// ----- ---------
Semaphore::Semaphore(int _count, int _maxcount, const tchar* _name, SECURITY_ATTRIBUTES* _sa)
{
    Handle = ::CreateSemaphore(_sa, _count, _maxcount, _name);
    
    Assert();
}

Semaphore::Semaphore(const tchar* _name, bool _inherit, uint _access)
{
    Handle = ::OpenSemaphore(_access, _inherit, _name);
    
    Assert();
}

Semaphore::Semaphore(HANDLE _handle)
{
    ::DuplicateHandle(::GetCurrentProcess(), _handle, ::GetCurrentProcess(), &Handle, 0, false, DUPLICATE_SAME_ACCESS);
    Assert();
}

void Semaphore::Release()
{
    Assert();
  ::ReleaseSemaphore(*this, 1, 0);
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__
