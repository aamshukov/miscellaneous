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

#ifndef __SYNCHRONIZATION_INC__
#   include <Synchronization.inc>
#endif

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
namespace Synchronization
{
////////////////////////////////////////////////////////////////////////////////////////
// class ETrigger
// ----- --------
ETrigger::ETrigger()
{
}

ETrigger::~ETrigger()
{
}

bool ETrigger::WaitEvent(uint _timeout)
{
    return ::WaitForSingleObject(E, _timeout) == WAIT_OBJECT_0;
}

void ETrigger::Trigger()
{
    E.Set();
}
////////////////////////////////////////////////////////////////////////////////////////
} // namespace Synchronization
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__
