////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __REGISTRY_INL__
#define __REGISTRY_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class RegKey
// ----- ------
__INLINE__ bool RegKey::IsKeyValid() const
{
    return Key != null;
}

__INLINE__ bool RegKey::IsShouldClose() const
{ 
    return ShouldClose;
}

__INLINE__ tchar* RegKey::GetName() const
{ 
    return Name;
}

__INLINE__ uint RegKey::GetSubkeyCount() const
{ 
    return SubkeyCount;
}

__INLINE__ uint RegKey::GetValueCount() const
{ 
    return ValueCount;
}

__INLINE__ HKEY RegKey::GetKey() const
{ 
    return Key;
}

__INLINE__ RegKey::operator HKEY()
{ 
    return Key;
}
////////////////////////////////////////////////////////////////////////////////////////
// class RegValue
// ----- --------
__INLINE__ void RegValue::operator = (uint _v)
{
    Set(DataType, reinterpret_cast<byte*>(&_v), DataSize);
}

__INLINE__ void RegValue::operator = (const tchar* _v)
{
    Set(DataType, reinterpret_cast<byte*>(const_cast<tchar*>(_v)), StrLen(_v)+1);
}

__INLINE__ const byte* RegValue::GetData() const 
{
    RetrieveOnDemand();
    return Data;
}

__INLINE__ RegValue::operator uint() const
{
    return *reinterpret_cast<uint*>(const_cast<byte*>(GetData())); // Assumes DataType == REG_DWORD
}

__INLINE__ RegValue::operator const tchar*() const
{
    return reinterpret_cast<const tchar*>(GetData()); // Assumes DataType == REG_SZ or sim.
}

__INLINE__ void RegValue::Set(uint _data)
{
    Set(REG_DWORD, reinterpret_cast<byte*>(&_data), sizeof _data);
}

__INLINE__ void RegValue::Set(const tchar* _data)
{
    Set(REG_SZ, reinterpret_cast<byte*>(const_cast<tchar*>(_data)), StrLen(_data));
}

__INLINE__ void RegValue::Delete()
{
    Key.DeleteValue(Name);
}
////////////////////////////////////////////////////////////////////////////////////////
// class RegKeyIterator
// ----- --------------
__INLINE__ RegKeyIterator::operator bool()
{
    return Index >= 0 && Index < static_cast<uint>(Key.GetSubkeyCount());
}

__INLINE__ uint RegKeyIterator::operator ++ ()
{
    return ++Index;
}

__INLINE__ uint RegKeyIterator::operator ++ (int)
{
    return Index++;
}

__INLINE__ uint RegKeyIterator::operator -- ()
{
    return --Index;
}

__INLINE__ uint RegKeyIterator::operator -- (int)
{
    return Index--;
}

__INLINE__ uint RegKeyIterator::operator [] (uint _index)
{
    return Index = _index;
}

__INLINE__ uint RegKeyIterator::GetCurrent() const
{
    return Index;
}
 
__INLINE__ const RegKey& RegKeyIterator::GetBaseKey() const
{
    return Key;
}

__INLINE__ void RegKeyIterator::Reset()
{
    Index = 0;
}
////////////////////////////////////////////////////////////////////////////////////////
// class RegValueIterator
// ----- ----------------
__INLINE__ RegValueIterator::operator bool()
{
    return Index >= 0 && Index < static_cast<int>(Key.GetValueCount());
}

__INLINE__ uint RegValueIterator::operator ++ ()
{
    return ++Index;
}

__INLINE__ uint RegValueIterator::operator ++ (int)
{
    return Index++;
}

__INLINE__ uint RegValueIterator::operator -- ()
{
    return --Index;
}

__INLINE__ uint RegValueIterator::operator -- (int)
{
    return Index--;
}

__INLINE__ uint RegValueIterator::operator [] (uint _index)
{
    return Index = _index;
}

__INLINE__ uint RegValueIterator::GetCurrent() const
{
    return Index;
}

__INLINE__ const RegKey& RegValueIterator::GetBaseKey() const
{
    return Key;
}

__INLINE__ void RegValueIterator::Reset()
{
    Index = 0;
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __REGISTRY_INL__
