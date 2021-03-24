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

#ifndef __CRITICALSECTION_INC__
#   include <CriticalSection.inc>
#endif

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class CriticalSection
// ----- ---------------
CriticalSection::CriticalSection()
{
    ::InitializeCriticalSection(const_cast<CRITICAL_SECTION*>(&CS));
}

CriticalSection::~CriticalSection()
{
    ::DeleteCriticalSection(const_cast<CRITICAL_SECTION*>(&CS));
}

CriticalSection::Lock::Lock(const CriticalSection& _cs) : CSWrap(_cs)
{
    ::EnterCriticalSection(const_cast<CRITICAL_SECTION*>(&CSWrap.CS));
} 

CriticalSection::Lock::~Lock()
{
    ::LeaveCriticalSection(const_cast<CRITICAL_SECTION*>(&CSWrap.CS));
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__
