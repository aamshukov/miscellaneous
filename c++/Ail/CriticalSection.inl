////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __CRITICALSECTION_INL__
#define __CRITICALSECTION_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class CriticalSection
// ----- ---------------
__INLINE__ bool CriticalSection::IsValid() const
{
    return Valid;
}

__INLINE__ const CRITICAL_SECTION& CriticalSection::GetCriticalSection() const
{
    return const_cast<const CRITICAL_SECTION&>(CS);
}

__INLINE__ CriticalSection::operator CRITICAL_SECTION() const
{
    return CS;
}

__INLINE__ CriticalSection::operator CRITICAL_SECTION* () const
{
    return const_cast<CRITICAL_SECTION*>(&CS);
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __CRITICALSECTION_INL__
