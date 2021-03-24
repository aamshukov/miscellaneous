////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __REGISTRY_H__
#define __REGISTRY_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
class RegKeyIterator;
class RegValueIterator;
////////////////////////////////////////////////////////////////////////////////////////
// class RegKey
// ----- ------
class __DECLSPEC__ RegKey
{
    private:
     bool           ShouldClose;
     tchar*         Name;
     uint           SubkeyCount;
     uint           ValueCount;
     HKEY           Key;
    private:
                    RegKey(const RegKey&);
     const RegKey&  operator = (const RegKey&);
    public:
                    RegKey();
                    RegKey(HKEY, const tchar*, REGSAM = KEY_ALL_ACCESS);
                    RegKey(const RegKeyIterator&, REGSAM = KEY_ALL_ACCESS);
                    RegKey(HKEY, bool = false, const tchar* = null);
     virtual       ~RegKey(); 

     bool           IsKeyValid()                                                          const;
     bool           IsShouldClose()                                                       const;
     tchar*         GetName()                                                             const;
     uint           GetSubkeyCount()                                                      const;
     uint           GetValueCount()                                                       const;
     HKEY           GetKey()                                                              const;

                    operator HKEY();

     bool           EnumKey(uint, tchar*, uint)                                           const;
     bool           EnumValue(uint, tchar*, uint&, uint* = 0, byte* = 0, uint* = 0)       const;
     void           DeleteKey(const tchar*);
     void           SetValue(const tchar*, uint, const byte*, uint)                       const;
     void           SetValue(const tchar*, uint)                                          const;
     void           QueryValue(const tchar*, uint*, byte*, uint*)                         const;
     void           DeleteValue(const tchar*)                                             const;
     void           Flush()                                                               const;
     void           GetSecurity(SECURITY_INFORMATION, SECURITY_DESCRIPTOR*, uint*);
     void           SetSecurity(SECURITY_INFORMATION, SECURITY_DESCRIPTOR*);
     void           Save(const tchar*);
     void           LoadKey(const tchar*, const tchar*);
     void           ReplaceKey(const tchar*, const tchar*, const tchar*);
     void           Restore(const tchar*, uint = 0);
     void           UnLoadKey(const tchar*);
     void           QueryInfo(tchar*, uint*, uint*, uint*, uint*, uint*, uint*, uint*, uint*, FILETIME*);
    public:
     static RegKey& GetClassRootKey();
     static RegKey& GetClassRootCLSIDKey();
     static RegKey& GetCurrentUserKey();
     static RegKey& GetLocalMachineKey();
     static RegKey& GetUsersKey();
     static RegKey& GetCurrentConfigKey();
     static RegKey& GetDynDataKey();
     static RegKey& GetPerformanceDataKey();

     static uint    DeleteRegistryTree(HKEY, const TCharStr&);
    public:

    class __DECLSPEC__ XRegKey : public X
    {
        public:
            XRegKey(uint = X::Failure);
    };

    friend class XRegKey;
};
////////////////////////////////////////////////////////////////////////////////////////
// class RegValue
// ----- --------
class __DECLSPEC__ RegValue
{
    private:
     tchar*             AliasName;
     const tchar*       Name;
     byte*              Data;
     uint               DataSize;
     uint               DataType;
     const RegKey&      Key;
    private:
                        RegValue(const RegValue&);
     const RegValue&    operator = (const RegValue&);
    public:
                        RegValue(const RegKey&, const tchar*);
                        RegValue(const RegValueIterator&);
     virtual           ~RegValue();

     void               operator = (uint);
     void               operator = (const tchar*);

     const tchar*       GetName()                     const;
     const uint         GetDataType()                 const;
     const uint         GetDataSize()                 const;
     const byte*        GetData()                     const;

                        operator uint()               const;
                        operator const tchar*()       const;

     void               Set(uint, byte*, uint);
     void               Set(uint);
     void               Set(const tchar* data);

     void               Delete();

     void               RetrieveOnDemand()            const;
    public:

    class __DECLSPEC__ XRegValue : public X
    {
        public:
            XRegValue(uint = X::Failure);
    };

    friend class XRegValue;
};
////////////////////////////////////////////////////////////////////////////////////////
// class RegKeyIterator
// ----- --------------
class __DECLSPEC__ RegKeyIterator
{
    private:
     const RegKey&  Key;
     uint           Index;
    public:
                    RegKeyIterator(const RegKey&);

     operator       bool();

     uint           operator ++ ();
     uint           operator ++ (int);
     uint           operator -- ();
     uint           operator -- (int);

     uint           operator [] (uint);
                     
     uint           GetCurrent() const;
     const RegKey&  GetBaseKey() const;

     void           Reset();
};                   
////////////////////////////////////////////////////////////////////////////////////////
// class RegValueIterator
// ----- ----------------
class __DECLSPEC__ RegValueIterator
{
    private:
     const RegKey&  Key;
     uint           Index;
    public:
                    RegValueIterator(const RegKey&);

     operator       bool();

     uint           operator ++ ();
     uint           operator ++ (int);
     uint           operator -- ();
     uint           operator -- (int);

     uint           operator [] (uint);

     uint           GetCurrent() const;
     const RegKey&  GetBaseKey() const;

     void           Reset();
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __REGISTRY_H__

