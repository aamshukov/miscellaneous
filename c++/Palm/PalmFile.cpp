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

#ifndef __PALM_FILE_INC__
#   include <PalmFile.inc>
#endif

#ifdef __PALM_OS__

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class PalmFile
// ----- --------
PalmFile::PalmFile()
        : Handle(0),
          Error(errNone)
{
}

PalmFile::~PalmFile()
{
    Close();
}

Err PalmFile::Open(uint16 _card_no, const char* _filename, uint32 _type, uint32 _creator, uint32 _open_mode)
{
    palmxassert(Handle != 0, Error::eUninitialized, PalmFile::XPalmFile);
    palmxassert(_filename != 0, Error::eInvalidArg, PalmFile::XPalmFile);

#if (__PALM_OS__ >= 0x0400)
    Handle = ::FileOpen(_card_no, _filename, _type, _creator, _open_mode, &Error);
#else
    Handle = ::FileOpen(_card_no, const_cast<char*>(_filename), _type, _creator, _open_mode, &Error);
#endif
    return Error;
}

////////////////////////////////////////////////////////////////////////////////////////
// class XPalmFile
// ----- ---------
void PalmFile::XPalmFile::LoadErrorDescriptions()
{
    // base class
    PalmError::LoadErrorDescriptions();

    // file errors
    GetDescriptions()[fileErrCorruptFile]         = "The file is corrupted/invalid/not a stream file";
    GetDescriptions()[fileErrNotFound]            = "Couldn't find the file";
    GetDescriptions()[fileErrTypeCreatorMismatch] = "File's type and creator didn't match those expected";
    GetDescriptions()[fileErrReplaceError]        = "Couldn't replace an existing file";
    GetDescriptions()[fileErrCreateError]         = "Couldn't create a new file";
    GetDescriptions()[fileErrOpenError]           = "Generic open error";
    GetDescriptions()[fileErrInUse]               = "File couldn't be opened or deleted because it is in use";
    GetDescriptions()[fileErrReadOnly]            = "Couldn't open in write mode because db is read-only";
    GetDescriptions()[fileErrInvalidDescriptor]   = "Invalid file descriptor (FileHandle)";
    GetDescriptions()[fileErrCloseError]          = "Error closing the database";
    GetDescriptions()[fileErrOutOfBounds]         = "Attempted operation went out of bounds of the file";
    GetDescriptions()[fileErrPermissionDenied]    = "Couldn't write to a file open for read-only access";
    GetDescriptions()[fileErrIOError]             = "General I/O error";
    GetDescriptions()[fileErrEOF]                 = "End-of-file error";
    GetDescriptions()[fileErrNotStream]           = "Attempted to open a file that is not a stream";
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__

