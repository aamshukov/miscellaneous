////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PALM_FILE_INL__
#define __PALM_FILE_INL__

#ifdef __PALM_OS__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class PalmFile
// ----- --------
__INLINE__ FileHand PalmFile::GetHandle() const
{
    return Handle;
}

__INLINE__ PalmFile::operator FileHand ()
{
    return Handle;
}

__INLINE__ Err PalmFile::Close()
{
    if(Handle != 0)
    {
        Error = ::FileClose(Handle), Handle = 0;
        return Error;
    }
    return errNone;
}

__INLINE__ Err PalmFile::Delete(uint16 _card_no, const char* _filename)
{
    palmxassert(_filename != null, Error::eUninitialized, PalmFile::XPalmFile);

#if (__PALM_OS__ >= 0x0400)
    return ::FileDelete(_card_no, _filename);
#else
    return ::FileDelete(_card_no, const_cast<char*>(_filename));
#endif
}

__INLINE__ int32 PalmFile::Read(char* _buffer, int32 _object_size, int32 _count)
{
    palmxassert(Handle != 0, Error::eUninitialized, PalmFile::XPalmFile);
    palmxassert(_buffer != null, Error::eInvalidArg, PalmFile::XPalmFile);
    return FileRead(Handle, _buffer, _object_size, _count, &Error);
}

__INLINE__ int32 PalmFile::DmRead(char* _buffer, int32 _dst_offset, int32 _object_size, int32 _count)
{
    palmxassert(Handle != 0, Error::eUninitialized, PalmFile::XPalmFile);
    return FileDmRead(Handle, _buffer, _dst_offset, _object_size, _count, &Error);
}

__INLINE__ int32 PalmFile::Write(const void* _buffer, int32 _object_size, int32 _count)
{
    palmxassert(Handle != 0, Error::eUninitialized, PalmFile::XPalmFile);
    palmxassert(_buffer != null, Error::eInvalidArg, PalmFile::XPalmFile);

#if (__PALM_OS__ >= 0x0400)
    return ::FileWrite(Handle, _buffer, _object_size, _count, &Error);
#else
    return ::FileWrite(Handle, const_cast<void*>(_buffer), _object_size, _count, &Error);
#endif
}

__INLINE__ Err PalmFile::Flush()
{
    palmxassert(Handle != 0, Error::eUninitialized, PalmFile::XPalmFile);
    return FileFlush(Handle);
}

__INLINE__ Err PalmFile::Truncate(int32 _new_size)
{
    palmxassert(Handle != 0, Error::eUninitialized, PalmFile::XPalmFile);
    return ::FileTruncate(Handle, _new_size);
}

__INLINE__ Err PalmFile::Rewind()
{
    palmxassert(Handle != 0, Error::eUninitialized, PalmFile::XPalmFile);
    return FileRewind(Handle);
}

__INLINE__ Err PalmFile::Seek(int32 _offset, FileOriginEnum _dir)
{
    palmxassert(Handle != 0, Error::eUninitialized, PalmFile::XPalmFile);
    return ::FileSeek(Handle, _offset, _dir);
}

__INLINE__ int32 PalmFile::Tell(int32& _size)
{
    palmxassert(Handle != 0, Error::eUninitialized, PalmFile::XPalmFile);
    return ::FileTell(Handle, &_size, &Error);
}

__INLINE__ Err PalmFile::Control(FileOpEnum _op, void* _value, int32& _value_size)
{
    palmxassert(Handle != 0, Error::eUninitialized, PalmFile::XPalmFile);
    return ::FileControl(_op, Handle, _value, &_value_size);
}

__INLINE__ Err PalmFile::IsEOF()
{
    palmxassert(Handle != 0, Error::eUninitialized, PalmFile::XPalmFile);
    return FileEOF(Handle);
}

__INLINE__ Err PalmFile::GetError()
{
    palmxassert(Handle != 0, Error::eUninitialized, PalmFile::XPalmFile);
    return FileError(Handle);
}

__INLINE__ Err PalmFile::GetLastError()
{
    palmxassert(Handle != 0, Error::eUninitialized, PalmFile::XPalmFile);
    return FileGetLastError(Handle);
}

__INLINE__ Err PalmFile::Clearerr()
{
    palmxassert(Handle != 0, Error::eUninitialized, PalmFile::XPalmFile);
    return FileClearerr(Handle);
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__
#endif // __PALM_FILE_INL__
