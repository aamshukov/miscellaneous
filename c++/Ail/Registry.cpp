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

#ifndef __REGISTRY_INC__
#   include <Registry.inc>
#endif

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class RegKey
// ----- ------
RegKey::RegKey()
{
    ShouldClose = false;
    Name        = null;
    SubkeyCount = 0;
    ValueCount  = 0;
    Key         = null;
}

RegKey::RegKey(HKEY _base_key, const tchar* _key_name, REGSAM _sam_desired)
{
    uint disposition = 0;

    Name = StrClone(_key_name);

    if(::RegCreateKeyEx(_base_key, Name, 0, _t(""), REG_OPTION_NON_VOLATILE, _sam_desired, 0, &Key, reinterpret_cast<ulong*>(&disposition)) != ERROR_SUCCESS)
    {
        throw RegKey::XRegKey();
    }

    QueryInfo(0, 0, &SubkeyCount, 0, 0, &ValueCount, 0, 0, 0, 0);
    ShouldClose = true;
}

RegKey::RegKey(const RegKeyIterator& _iter, REGSAM _sam_desired)
{
    Key  = null;
    Name = new tchar[STRING_SIZE];

   _iter.GetBaseKey().EnumKey(_iter.GetCurrent(), Name, STRING_SIZE);

    if(::RegOpenKeyEx(HKEY(const_cast<RegKey*>(&_iter.GetBaseKey())), Name, 0, _sam_desired, &Key) != ERROR_SUCCESS)
    {
        throw RegKey::XRegKey();
    }

    ShouldClose = true;
    QueryInfo(0, 0, &SubkeyCount, 0, 0, &ValueCount, 0, 0, 0, 0);
}

RegKey::RegKey(HKEY _alias_key, bool _should_close, const tchar* _key_name)
{
    Key         = _alias_key;
    Name        = StrClone(_key_name);
    ShouldClose = _should_close;
    //
    QueryInfo(0, 0, &SubkeyCount, 0, 0, &ValueCount, 0, 0, 0, 0);
}

RegKey::~RegKey()
{
    if(Key && ShouldClose)
    {
        ::RegCloseKey(Key);
    }
    delete [] Name, Name = null;
}

bool RegKey::EnumKey(uint _index, tchar* _subkey_name, uint _subkey_size) const
{
    uint ret =::RegEnumKey(Key, _index, _subkey_name, _subkey_size);

    if(ret == ERROR_SUCCESS)
    {
        return true;
    }
    else if(ret == ERROR_NO_MORE_ITEMS)
    {
        return false;
    }
    else
    {
        throw RegKey::XRegKey();
    }
}

void RegKey::DeleteKey(const tchar* _subkey_name)
{
    if(::RegDeleteKey(Key, _subkey_name) != ERROR_SUCCESS)
    {
        throw RegKey::XRegKey();
    }
}

void RegKey::Flush() const
{
    if(::RegFlushKey(Key) != ERROR_SUCCESS)
    {
        throw RegKey::XRegKey();
    }
}

void RegKey::GetSecurity(SECURITY_INFORMATION _sec_inf, SECURITY_DESCRIPTOR* _sec_desc, uint* _sec_desc_size)
{ 
    if(::RegGetKeySecurity(Key, _sec_inf, _sec_desc, reinterpret_cast<DWORD*>(_sec_desc_size)) != ERROR_SUCCESS)
    {
        throw RegKey::XRegKey();
    }
}

void RegKey::SetSecurity(SECURITY_INFORMATION _sec_inf, SECURITY_DESCRIPTOR* _sec_desc)
{ 
    if(::RegSetKeySecurity(Key, _sec_inf, _sec_desc) != ERROR_SUCCESS)
    {
        throw RegKey::XRegKey();
    }
}

void RegKey::Save(const tchar* _file_name)
{
    if(::RegSaveKey(Key, _file_name, 0) != ERROR_SUCCESS)
    {
        throw RegKey::XRegKey();
    }
}

void RegKey::LoadKey(const tchar* _subkey_name, const tchar* _file_name)
{
    if(::RegLoadKey(Key, _subkey_name, _file_name) != ERROR_SUCCESS)
    {
        throw RegKey::XRegKey();
    }
}

void RegKey::ReplaceKey(const tchar* _subkey_name, const tchar* _new_file_name, const tchar* _old_file_name)
{
    if(::RegReplaceKey(Key, _subkey_name, _new_file_name, _old_file_name) != ERROR_SUCCESS)
    {
        throw RegKey::XRegKey();
    }
}

void RegKey::Restore(const tchar* _file_name, uint _options)
{
    if(::RegRestoreKey(Key, _file_name, _options) != ERROR_SUCCESS)
    {
        throw RegKey::XRegKey();
    }
}

void RegKey::UnLoadKey(const tchar* _subkey_name)
{
    if(::RegUnLoadKey(Key, _subkey_name) != ERROR_SUCCESS)
    {
        throw RegKey::XRegKey();
    }
}

void RegKey::SetValue(const tchar* _val_name, uint _type, const byte* _data, uint _data_size) const
{
    if(::RegSetValueEx(Key, _val_name, 0, _type, _data, _data_size) != ERROR_SUCCESS)
    {
        throw RegKey::XRegKey();
    }
}

void RegKey::SetValue(const tchar* _val_name, uint _data) const
{
    SetValue(_val_name, REG_DWORD, reinterpret_cast<byte*>(const_cast<uint*>(&_data)), sizeof(_data));
}

void RegKey::DeleteValue(const tchar* _val_name) const
{
    if(::RegDeleteValue(Key, _val_name) != ERROR_SUCCESS)
    {
        throw RegKey::XRegKey();
    }
}

void RegKey::QueryValue(const tchar* _val_name, uint* _type, byte* _data, uint* _data_size) const
{
    if(::RegQueryValueEx(Key, _val_name, 0, reinterpret_cast<ulong*>(_type), _data, reinterpret_cast<ulong*>(_data_size)) != ERROR_SUCCESS)
    {
        throw RegKey::XRegKey();
    }
}

bool RegKey::EnumValue(uint _index, tchar* _value_name, uint& _value_size, uint* _type, byte* _data, uint* _data_size) const
{
    uint ret = ::RegEnumValue(Key, _index, _value_name, reinterpret_cast<ulong*>(&_value_size), 0, reinterpret_cast<ulong*>(_type), _data, reinterpret_cast<ulong*>(_data_size));

    if(ret == ERROR_SUCCESS)
    {
        return true;
    }
    else if(ret == ERROR_NO_MORE_ITEMS)
    {
        return false;
    }
    else
    {
        throw RegKey::XRegKey();
    }
}

RegKey& RegKey::GetClassRootKey()
{
    static RegKey ClassesRoot(HKEY_CLASSES_ROOT, true, _t("HKEY_CLASSES_ROOT"));
    return ClassesRoot;
}

RegKey& RegKey::GetClassRootCLSIDKey()
{
    static RegKey ClassesRootCLSID(RegKey::GetClassRootKey(), _t("CLSID"), KEY_ALL_ACCESS);
    return ClassesRootCLSID;
}

RegKey& RegKey::GetCurrentUserKey()
{
    static RegKey CurrentUser(HKEY_CURRENT_USER, true, _t("HKEY_CURRENT_USER"));
    return CurrentUser;
}

RegKey& RegKey::GetLocalMachineKey()
{
    static RegKey LocalMachine(HKEY_LOCAL_MACHINE, true, _t("HKEY_LOCAL_MACHINE"));
    return LocalMachine;
}

RegKey& RegKey::GetUsersKey()
{
    static RegKey Users(HKEY_USERS, true, _t("HKEY_USERS"));
    return Users;
}

RegKey& RegKey::GetCurrentConfigKey()
{
    static RegKey CurrentConfig(HKEY_CURRENT_CONFIG, true, _t("HKEY_CURRENT_CONFIG"));
    return CurrentConfig;
}

RegKey& RegKey::GetDynDataKey()
{
    static RegKey DynData(HKEY_DYN_DATA, true, _t("HKEY_DYN_DATA"));
    return DynData;
}

RegKey& RegKey::GetPerformanceDataKey()
{
    static RegKey PerformanceData(HKEY_PERFORMANCE_DATA, true, _t("HKEY_PERFORMANCE_DATA"));
    return PerformanceData;
}

void RegKey::QueryInfo(tchar* _class, uint* _class_size, uint* _subkey_count, uint* _max_subkey_size, uint* _max_class_size, uint* _value_count, uint* _max_value_name, uint* _max_value_data, uint* _sec_desc_size, FILETIME* _last_write_time)
{
    tchar    db[STRING_SIZE];
    uint     d1 = sizeof(db);
    uint     d2 = 0;
    uint     d3 = 0;
    uint     d4 = 0;
    uint     d5 = 0;
    uint     d6 = 0;
    uint     d7 = 0;
    uint     d8 = 0;
    FILETIME ft;

    if(::RegQueryInfoKey(Key, 
                         _class                    ? _class           : db,
                         (DWORD*)(_class_size      ? _class_size      : &d1), 
                         0,
                         (DWORD*)(_subkey_count    ? _subkey_count    : &d2),
                         (DWORD*)(_max_subkey_size ? _max_subkey_size : &d3),
                         (DWORD*)(_max_class_size  ? _max_class_size  : &d4),
                         (DWORD*)(_value_count     ? _value_count     : &d5),
                         (DWORD*)(_max_value_name  ? _max_value_name  : &d6),
                         (DWORD*)(_max_value_data  ? _max_value_data  : &d7),
                         (DWORD*)(_sec_desc_size   ? _sec_desc_size   : &d8),
                         _last_write_time ? _last_write_time : &ft) != ERROR_SUCCESS)
    {
        throw RegKey::XRegKey();
    }
}

uint RegKey::DeleteRegistryTree(HKEY _parent_key, const TCharStr& _key_name)
{
    // for Windows NT ! ...
    // Under Win32, a reg key may not be deleted unless it is empty.
    // to delete a tree - recursively enumerate and delete all of the subkeys.
    tchar subkey_name[STRING_SIZE];
    uint  index = 0;
    uint  result;
    HKEY  current_key;

    if((result = ::RegOpenKey(_parent_key, _key_name, &current_key)) == ERROR_SUCCESS)
    {
        // Remove all subkeys of the key to delete
        while((result = ::RegEnumKey(current_key, 0, subkey_name, 255)) == ERROR_SUCCESS)
        {
            if((result = DeleteRegistryTree(current_key, subkey_name)) != ERROR_SUCCESS)
            {
                break;
            }
        }

        if((result == ERROR_NO_MORE_ITEMS) || (result == ERROR_BADKEY))
        {
            result = ::RegDeleteKey(_parent_key, _key_name);
        }
    }

    ::RegCloseKey(current_key);
        
    return result;
}

RegKey::XRegKey::XRegKey(uint _error) : X(_error)
{
}
////////////////////////////////////////////////////////////////////////////////////////
// class RegValue
// ----- --------
RegValue::RegValue(const RegKey& _key, const tchar* _name) : Key(_key), Name(_name)
{
    AliasName = null;
    Data      = null;
    DataSize  = 0;

    Key.QueryValue(Name, &DataType, 0, &DataSize);
}

RegValue::RegValue(const RegValueIterator& _iter) : Key(_iter.GetBaseKey())
{
    uint vs = STRING_SIZE;

    Data      = null;
    Name      = new tchar[STRING_SIZE];
    AliasName = new tchar[STRING_SIZE];
    DataSize  = 0;

    Key.EnumValue(_iter.GetCurrent(), AliasName, vs, &DataType, 0, &DataSize);
}

RegValue::~RegValue()
{
    delete [] AliasName, AliasName = null;
    delete [] Data, Data = null;
}

void RegValue::RetrieveOnDemand() const
{
    if(Data == null)
    {
        uint ds = DataSize;

        const_cast<RegValue*>(this)->Data = new byte[DataSize];

        Key.QueryValue(Name, 0, Data, &ds);
    }
}

void RegValue::Set(uint _type, byte* _data, uint _data_size)
{
    Key.SetValue(Name, _type, _data, _data_size);
    //
    DataType = _type;

    if(_data_size == DataSize) 
    {
        memcpy(Data, _data, DataSize);
    }
    else 
    {
        DataSize = _data_size;
        delete [] Data, Data = null;
    }
}

RegValue::XRegValue::XRegValue(uint _error) : X(_error)
{
}
////////////////////////////////////////////////////////////////////////////////////////
// class RegKeyIterator
// ----- --------------
RegKeyIterator::RegKeyIterator(const RegKey& _key) : Key(_key), Index(0)
{
}
////////////////////////////////////////////////////////////////////////////////////////
// class RegValueIterator
// ----- ----------------
RegValueIterator::RegValueIterator(const RegKey& _key) : Key(_key), Index(0)
{
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__
