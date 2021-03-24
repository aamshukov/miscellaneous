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

#ifndef __PALM_MATHLIB_INC__
#   include <PalmMathlib.inc>
#endif

#ifdef __PALM_OS__

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class PalmMathlib
// ----- -----------
PalmMathlib::PalmMathlib(bool _unload)
           : PalmModule(MathLibName, MathLibCreator, LibType, _unload)
{
}

PalmMathlib::~PalmMathlib()
{
    Close();
}

Err PalmMathlib::Open()
{
    Err err = ::MathLibOpen(Handle, MathLibVersion);
    return err;
}

Err PalmMathlib::Close()
{
    Err err = ::MathLibClose(Handle, &Count);
    return err;
}

PalmModule& PalmMathlib::GetMathlibModule()
{
    static PalmMathlib _the_module_;
    //
    if(!_the_module_.IsValid())
    {
        _the_module_.LoadModule();
    }
    return _the_module_;
}
////////////////////////////////////////////////////////////////////////////////////////
// class XPalmMathlib
// ----- ------------
void PalmMathlib::XPalmMathlib::LoadErrorDescriptions()
{
    // base class
    PalmModule::XPalmModule::LoadErrorDescriptions();
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__
