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

#ifndef __PALM_DB_INC__
#   include <PalmDB.inc>
#endif

#ifdef __PALM_OS__

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class PalmDB
// ----- --------
PalmDB::PalmDB()
      : Handle(0)
//        Error(errNone)
{
}

PalmDB::~PalmDB()
{
//    Close();
}

/*
Err PalmDB::Open(uint16 _card_no, const char* _filename, uint32 _type, uint32 _creator, uint32 _open_mode)
{
    palmxassert(Handle != 0, Error::eUninitialized, PalmDB::XPalmDB);
    palmxassert(_filename != 0, Error::eInvalidArg, PalmDB::XPalmDB);

#if (__PALM_OS__ >= 0x0400)
    Handle = ::FileOpen(_card_no, _filename, _type, _creator, _open_mode, &Error);
#else
    Handle = ::FileOpen(_card_no, const_cast<char*>(_filename), _type, _creator, _open_mode, &Error);
#endif
    return Error;
}
*/
////////////////////////////////////////////////////////////////////////////////////////
// class XPalmDB
// ----- ---------
void PalmDB::XPalmDB::LoadErrorDescriptions()
{
    // base class
    PalmError::LoadErrorDescriptions();
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__

