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

#ifndef __EVENT_INC__
#   include <Event.inc>
#endif

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class Event
// ----- -----
Event::Event(bool _manual_reset, bool _initial_state, const tchar* _name, SECURITY_ATTRIBUTES* _sa)
{
    Handle = ::CreateEvent(_sa, _manual_reset, _initial_state, _name);
    
    Assert();
}

Event::Event(const tchar* _name, bool _inherit, uint _access)
{
    Handle = ::OpenEvent(_access, _inherit, _name);

    Assert();
} 

Event::Event(HANDLE _handle)
{
    ::DuplicateHandle(::GetCurrentProcess(), _handle, ::GetCurrentProcess(), &Handle, 0, false, DUPLICATE_SAME_ACCESS);
    Assert();
}

void Event::Release()
{
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__
