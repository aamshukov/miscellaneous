////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PALM_MODULE_INL__
#define __PALM_MODULE_INL__

#ifdef __PALM_OS__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class PalmModule
// ----- ----------
__INLINE__ bool PalmModule::IsValid() const
{
    return Handle > 0;
}

__INLINE__ bool PalmModule::ShouldFree() const
{
    return Free;
}

__INLINE__ HMODULE PalmModule::GetModule() const
{
    return Handle;
}

__INLINE__ uint32 PalmModule::GetType() const
{
    return Type;
}

__INLINE__ uint32 PalmModule::GetCreator() const
{
    return Creator;
}

__INLINE__ _string PalmModule::GetName() const
{
    return Name;
}

__INLINE__ PalmModule::operator HMODULE () const
{
    return Handle;
}

__INLINE__ bool PalmModule::operator == (const PalmModule& _other) const
{
    return GetModule() == _other.GetModule();
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif //__PALM_OS__
#endif // __PALM_MODULE_INL__
