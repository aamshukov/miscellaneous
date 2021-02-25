////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  Copyright © 1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PALM_OS_INL__
#define __PALM_OS_INL__

#ifdef __PALM_OS__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class PalmOS
// ----- ------
__INLINE__ uint32 PalmOS::GetCreatorID()
{
    return CreatorID;
}

__INLINE__ Err PalmOS::MemMove(void* _dst, const void* _src, int32 _count)
{
    if(_dst == null || _src == null || _count <= 0)
    {
        return 0;
    }
    return ::MemMove(_dst, _src, _count);
}

__INLINE__ Err PalmOS::MemCopy(void* _dst, const void* _src, int32 _count)
{
    if(_dst == null || _src == null || _count <= 0)
    {
        return 0;
    }
    return ::MemMove(_dst, _src, _count);
}

__INLINE__ Err PalmOS::MemSet(void* _dst, int32 _count, byte _pattern)
{
    if(_dst == null || _count <= 0)
    {
        return 0;
    }
    return ::MemSet(_dst, _count, _pattern);
}

__INLINE__ int16 PalmOS::MemCompare(const void* _s1, const void* _s2, int32 _count)
{
    if(_s1 == null || _s2 == null || _count <= 0)
    {
        return 0;
    }
    return ::MemCmp(_s1, _s2, _count);
}

__INLINE__ uint16 PalmOS::GetCardNumber()
{
    return 0;
}

__INLINE__ void PalmOS::GetDatabaseName(char* _name)
{
  ::StrNCat(_name, reinterpret_cast<char*>(CreatorID), sizeof(CreatorID));
}

__INLINE__ int32 PalmOS::SecondsToTicks(uint16 _secs)
{
    return static_cast<int32>(_secs*sysTicksPerSecond+(_secs/(1000000L/sysTicksPerSecond)));
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__
#endif // __PALM_OS_INL__
