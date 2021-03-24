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

#ifndef __MODULE_INC__
#   include <Module.inc>
#endif

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class Module
// ----- ------
Module::Module(const _string& _name, bool _load)
      : Handle(0)
{
    Lock lock(this);

    if(_load && !_name.IsEmpty())
    {
        uint e = ::SetErrorMode(SEM_NOOPENFILEERRORBOX|SEM_FAILCRITICALERRORS);

        Handle = ::LoadLibrary(_name);

        if(Handle == null)
        {
            throw Module::XModule();
        }

      ::SetErrorMode(e);
    }
    else
    {
        Handle = null;
    }

    Free = _load;
    //
    SetName(_name);
}

Module::Module(HMODULE _handle)
{
    Free   = false;
    Handle = _handle;
    //
    SetName();
}

Module::~Module()
{
    UnloadModule();
}

void Module::LoadModule(const _string& _name)
{
    Lock lock(this);

    if(!_name.IsEmpty())
    {
        uint e = ::SetErrorMode(SEM_NOOPENFILEERRORBOX|SEM_FAILCRITICALERRORS);

        Handle = ::LoadLibrary(_name);

        if(Handle == null)
        {
            throw Module::XModule();
        }

        ::SetErrorMode(e);

        Free = true;
    }
    else
    {
        Handle = null;
    }
    SetName(_name);
}

void Module::UnloadModule()
{
    Lock lock(this);

    if(ShouldFree() && IsValid())
    {
        Name.SetEmpty();
      ::FreeLibrary(Handle);
        Handle = null;
    }
}

String<tchar> Module::GetModuleFileName() const
{
   _string str;

    if(IsValid())
    {
        AutoPtrArray<tchar> buffer = new tchar[_MAX_PATH];

        ::GetModuleFileName(Handle, buffer, _MAX_PATH);

        str = buffer;
    }

    return str;
}

Module::XModule::XModule(uint _error) : X(_error)
{
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__
