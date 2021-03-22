////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PALM_VFS_INL__
#define __PALM_VFS_INL__

#if (__PALM_OS__ >= 0x0400)

#ifdef __PALM_OS__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class File VFS
// ----- ---- ---
__INLINE__ FileRef PalmVFS::File::GetRef() const
{
    return Ref;
}

__INLINE__ PalmVFS::File::operator FileRef ()
{
    return Ref;
}

__INLINE__ Err PalmVFS::File::Create(const char* _filename)
{
    palmxassert(_filename != null, Error::eInvalidArg, PalmVFS::XPalmVFS);
    return ::VFSFileCreate(PalmVFS::Volume::GetRefNumber(), _filename);
}

__INLINE__ Err PalmVFS::File::Delete(const char* _filename)
{
    palmxassert(_filename != null, Error::eInvalidArg, PalmVFS::XPalmVFS);
    return ::VFSFileDelete(PalmVFS::Volume::GetRefNumber(), _filename);
}

__INLINE__ Err PalmVFS::File::Rename(const char* _filename, const char* _new_filename)
{
    palmxassert(_filename != null, Error::eInvalidArg, PalmVFS::XPalmVFS);
    palmxassert(_new_filename != null, Error::eInvalidArg, PalmVFS::XPalmVFS);
    return ::VFSFileRename(PalmVFS::Volume::GetRefNumber(), _filename, _new_filename);
}

__INLINE__ Err PalmVFS::File::Open(const char* _filename, uint16 _open_mode)
{
    palmxassert(_filename != null, Error::eInvalidArg, PalmVFS::XPalmVFS);
    return ::VFSFileOpen(PalmVFS::Volume::GetRefNumber(), _filename, _open_mode, &Ref);
}

__INLINE__ Err PalmVFS::File::Close()
{
    if(Ref != 0)
    {
        Err err = ::VFSFileClose(Ref), Ref = 0;
        return err;
    }
    return errNone;
}

__INLINE__ Err PalmVFS::File::ReadData(uint32 _count, void* _buffer, uint32 _offset, uint32& _read_count)
{
    palmxassert(Ref != null, Error::eUninitialized, PalmVFS::XPalmVFS);
    palmxassert(_buffer != null, Error::eInvalidArg, PalmVFS::XPalmVFS);
    return ::VFSFileReadData(Ref, _count, _buffer, _offset, &_read_count);
}

__INLINE__ Err PalmVFS::File::Read(uint32 _count, void* _buffer, uint32& _read_count)
{
    palmxassert(Ref != null, Error::eUninitialized, PalmVFS::XPalmVFS);
    palmxassert(_buffer != null, Error::eInvalidArg, PalmVFS::XPalmVFS);
    return ::VFSFileRead(Ref, _count, _buffer, &_read_count);
}

__INLINE__ Err PalmVFS::File::Write(uint32 _count, const void* _buffer, uint32& _written_count)
{
    palmxassert(Ref != null, Error::eUninitialized, PalmVFS::XPalmVFS);
    palmxassert(_buffer != null, Error::eInvalidArg, PalmVFS::XPalmVFS);
    return ::VFSFileWrite(Ref, _count, _buffer, &_written_count);
}

__INLINE__ Err PalmVFS::File::Seek(FileOrigin _dir, int32 _offset)
{
    palmxassert(Ref != null, Error::eUninitialized, PalmVFS::XPalmVFS);
    return ::VFSFileSeek(Ref, _dir, _offset);
}

__INLINE__ Err PalmVFS::File::IsEOF()
{
    palmxassert(Ref != null, Error::eUninitialized, PalmVFS::XPalmVFS);
    return ::VFSFileEOF(Ref);
}

__INLINE__ Err PalmVFS::File::Tell(uint32& _pos)
{
    palmxassert(Ref != null, Error::eUninitialized, PalmVFS::XPalmVFS);
    return ::VFSFileTell(Ref, &_pos);
}

__INLINE__ Err PalmVFS::File::Size(uint32& _size)
{
    palmxassert(Ref != null, Error::eUninitialized, PalmVFS::XPalmVFS);
    return ::VFSFileSize(Ref, &_size);
}

__INLINE__ Err PalmVFS::File::Resize(uint32 _new_size)
{
    palmxassert(Ref != null, Error::eUninitialized, PalmVFS::XPalmVFS);
    return ::VFSFileResize(Ref, _new_size);
}

__INLINE__ Err PalmVFS::File::GetAttributes(uint32& _attributes)
{
    palmxassert(Ref != null, Error::eUninitialized, PalmVFS::XPalmVFS);
    return ::VFSFileGetAttributes(Ref, &_attributes);
}

__INLINE__ Err PalmVFS::File::SetAttributes(uint32 _attributes)
{
    palmxassert(Ref != null, Error::eUninitialized, PalmVFS::XPalmVFS);
    return ::VFSFileSetAttributes(Ref, _attributes);
}

__INLINE__ Err PalmVFS::File::GetDate(uint16 _type, uint32& _date)
{
    palmxassert(Ref != null, Error::eUninitialized, PalmVFS::XPalmVFS);
    return ::VFSFileGetDate(Ref, _type, &_date);
}

__INLINE__ Err PalmVFS::File::SetDate(uint16 _type, uint32 _date)
{
    palmxassert(Ref != null, Error::eUninitialized, PalmVFS::XPalmVFS);
    return ::VFSFileSetDate(Ref, _type, _date);
}

__INLINE__ Err PalmVFS::File::DirEntryEnumerate(uint32& _it, FileInfoType& _info)
{
    palmxassert(Ref != null, Error::eUninitialized, PalmVFS::XPalmVFS);
    return ::VFSDirEntryEnumerate(Ref, &_it, &_info);
}

__INLINE__ Err PalmVFS::File::DirCreate(const char* _dir_name)
{
    palmxassert(_dir_name != null, Error::eInvalidArg, PalmVFS::XPalmVFS);
    return ::VFSDirCreate(PalmVFS::Volume::GetRefNumber(), _dir_name);
}

__INLINE__ Err PalmVFS::File::GetDefaultDirectory(const char* _type, char* _buffer, uint16& _count)
{
    palmxassert(_type != null, Error::eInvalidArg, PalmVFS::XPalmVFS);
    palmxassert(_buffer != null, Error::eInvalidArg, PalmVFS::XPalmVFS);
    return ::VFSGetDefaultDirectory(PalmVFS::Volume::GetRefNumber(), _type, _buffer, &_count);
}

__INLINE__ Err PalmVFS::File::RegisterDefaultDirectory(const char* _type, uint32 _media_type, const char* _dir_name)
{
    palmxassert(_type != null, Error::eInvalidArg, PalmVFS::XPalmVFS);
    palmxassert(_dir_name != null, Error::eInvalidArg, PalmVFS::XPalmVFS);
    return ::VFSRegisterDefaultDirectory(_type, _media_type, _dir_name);
}

__INLINE__ Err PalmVFS::File::UnregisterDefaultDirectory(const char* _type, uint32 _media_type)
{
    palmxassert(_type != null, Error::eInvalidArg, PalmVFS::XPalmVFS);
    return ::VFSUnregisterDefaultDirectory(_type, _media_type);
}

__INLINE__ Err PalmVFS::File::DBGetResource(DmResType _res_type, DmResID _res_id, MemHandle& _hres)
{
    palmxassert(Ref != null, Error::eUninitialized, PalmVFS::XPalmVFS);
    return ::VFSFileDBGetResource(Ref, _res_type, _res_id, &_hres);
}

__INLINE__ Err PalmVFS::File::DBInfo(char* _name, uint16& _attributes, uint16& _version,
                                     uint32& _cr_date, uint32& _mod_date, uint32& _bck_date,
                                     uint32& _mod_no, MemHandle& _app_info, MemHandle& _sort_info,
                                     uint32& _type, uint32& _creator, uint16& _num_records)
{
    palmxassert(Ref != null, Error::eUninitialized, PalmVFS::XPalmVFS);
    palmxassert(_name != null, Error::eInvalidArg, PalmVFS::XPalmVFS);
    return ::VFSFileDBInfo(Ref, _name, &_attributes, &_version, &_cr_date, &_mod_date, &_bck_date, &_mod_no, &_app_info, &_sort_info, &_type, &_creator, &_num_records);
}

__INLINE__ Err PalmVFS::File::DBGetRecord(uint16 _index, MemHandle& _rec, uint8& _rec_attr, uint32& _unique_id)
{
    palmxassert(Ref != null, Error::eUninitialized, PalmVFS::XPalmVFS);
    return ::VFSFileDBGetRecord(Ref, _index, &_rec, &_rec_attr, &_unique_id);
}
////////////////////////////////////////////////////////////////////////////////////////
// class Volume VFS
// ----- ------ ---
__INLINE__ Err PalmVFS::Volume::Info(VolumeInfoType& _info)
{
    return ::VFSVolumeInfo(PalmVFS::Volume::GetRefNumber(), &_info);
}

__INLINE__ Err PalmVFS::Volume::Enumerate(uint16& _ref_num, uint32& _it)
{
    return ::VFSVolumeEnumerate(&_ref_num, &_it);
}

__INLINE__ Err PalmVFS::Volume::GetLabel(char* _label, uint16 _count)
{
    palmxassert(_label != null, Error::eInvalidArg, PalmVFS::XPalmVFS);
    return ::VFSVolumeGetLabel(PalmVFS::Volume::GetRefNumber(), _label, _count);
}

__INLINE__ Err PalmVFS::Volume::SetLabel(const char* _label)
{
    palmxassert(_label != null, Error::eInvalidArg, PalmVFS::XPalmVFS);
    return ::VFSVolumeSetLabel(PalmVFS::Volume::GetRefNumber(), _label);
}

__INLINE__ Err PalmVFS::Volume::Size(uint32& _used, uint32& _total)
{
    return ::VFSVolumeSize(PalmVFS::Volume::GetRefNumber(), &_used, &_total);
}

__INLINE__ Err PalmVFS::Volume::Format(uint8 _flags, uint16 _fs_ref, VFSAnyMountParamType& _mount_param)
{
    return ::VFSVolumeFormat(_flags, _fs_ref, &_mount_param);
}

__INLINE__ Err PalmVFS::Volume::Mount(uint8 _flags, uint16 _fs_ref, VFSAnyMountParamType& _mount_param)
{
    return ::VFSVolumeMount(_flags, _fs_ref, &_mount_param);
}

__INLINE__ Err PalmVFS::Volume::Unmount()
{
    return ::VFSVolumeUnmount(PalmVFS::Volume::GetRefNumber());
}
////////////////////////////////////////////////////////////////////////////////////////
// class PalmVFS
// ----- -------
__INLINE__ Err PalmVFS::Init()
{
    return ::VFSInit();
}

__INLINE__ Err PalmVFS::CustomControl(uint32 _fs_creator, uint32 _api_creator, uint16 _api_selector, void* _value, uint16& _count)
{
    return ::VFSCustomControl(_fs_creator, _api_creator, _api_selector, _value, &_count);
}

__INLINE__ Err PalmVFS::InstallFSLib(uint32 _creator, uint16& _fs_ref)
{
    return ::VFSInstallFSLib(_creator, &_fs_ref);
}

__INLINE__ Err PalmVFS::RemoveFSLib(uint16 _fs_ref)
{
    return ::VFSRemoveFSLib(_fs_ref);
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__
#endif
#endif // __PALM_VFS_INL__
