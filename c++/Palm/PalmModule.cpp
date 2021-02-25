////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  Copyright © 1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __AIL_H__
#   include <ail.hpp>
#endif

#ifndef __PALM_MODULE_INC__
#   include <PalmModule.inc>
#endif

#ifdef __PALM_OS__

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class PalmModule
// ----- ----------
PalmModule::PalmModule(const char* _name, uint32 _creator, uint32 _type, bool _unload)
          : Handle(0),
            Free(_unload),
            Name(_name),
            Type(_type),
            Creator(_creator),
            Count(0)
{
}

PalmModule::~PalmModule()
{
    UnloadModule();
}

Err PalmModule::LoadModule()
{
    if(Name.empty())
    {
        return sysErrorClass+1;
    }

    Err err = ::SysLibFind(Name.c_str(), &Handle);

    if(err == sysErrLibNotFound)
    {
        err = ::SysLibLoad(Type, Creator, &Handle);

        if(err != errNone)
        {
            Handle = 0;
            return err;
        }
    }

    err = Open();
    return err;
}

Err PalmModule::UnloadModule()
{
    if(ShouldFree() && IsValid())
    {
        if(Count == 0)
        {
            Err err = ::SysLibRemove(Handle), Handle = null;
            return err;
        }
    }
    return errNone;
}
////////////////////////////////////////////////////////////////////////////////////////
// class XPalmModule
// ----- -----------
void PalmModule::XPalmModule::LoadErrorDescriptions()
{
    // base class
    PalmError::LoadErrorDescriptions();
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__
