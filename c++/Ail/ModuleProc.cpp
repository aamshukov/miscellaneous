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

#ifndef __MODULEPROC_INC__
#   include <ModuleProc.inc>
#endif

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class ModuleProc
// ----- ----------
ModuleProc::ModuleProc(const Module& _module, const char* _proc)
{
    Procedure = _module.GetProcAddress(_proc);

#ifdef __MS_WINDOWS__
    if(Procedure == null)
    {
        throw ModuleProc::XModuleProc();
    }
#endif
}

ModuleProc::~ModuleProc()
{
}

#ifdef __MS_WINDOWS__
ModuleProc::XModuleProc::XModuleProc(uint _error) : X(_error)
{
}
#endif
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__
