////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __MODULE_H__
#define __MODULE_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class Module
// ----- ------
class __DECLSPEC__ Module : private SyncObject
{
    typedef String<tchar> _string;

    private:
     bool           Free;
     HMODULE        Handle;
    _string         Name;
    private:
                    Module(const Module&);
     const Module&  operator = (const Module&);
    public:
     // ctor/dtor
                    Module(const _string&, bool = true);
                    Module(HMODULE);
     virtual       ~Module();

     // access
     bool           IsValid()                               const;
     bool           ShouldFree()                            const;

     HMODULE        GetModule()                             const;
     void           SetModule(HMODULE);

    _string         GetName()                               const;
     void           SetName();
     void           SetName(const _string&);

     // operators
                    operator HMODULE ()                     const;
     bool           operator == (const Module&)             const;

     // api
     void           LoadModule(const _string&);
     void           UnloadModule();

     FARPROC        GetProcAddress(const char*)             const;
    _string         GetModuleFileName()                     const;

     HRSRC          FindResource(uint, const tchar*)        const;
     HGLOBAL        LoadResource(HRSRC)                     const;
     uint           SizeOfResource(HRSRC)                   const;

     bool           GetClassInfo(const tchar*, WNDCLASS&)   const;

     bool           LoadString(uint, tchar*, uint)          const;
     HBITMAP        LoadBitmap(uint)                        const;
     HACCEL         LoadAccelerators(uint)                  const;
     HMENU          LoadMenu(uint)                          const;
     HCURSOR        LoadCursor(uint)                        const;
     HICON          LoadIcon(const tchar*)                  const;

     HANDLE         LoadImage(const tchar*, uint, int = 0, int = 0, uint = LR_DEFAULTCOLOR|LR_DEFAULTSIZE) const;
    public:

    class __DECLSPEC__ XModule : public X
    {
        public:
            XModule(uint = X::Failure);
    };
    
    friend class XModule;
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __MODULE_H__
