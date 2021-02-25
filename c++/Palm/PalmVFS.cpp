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

#ifndef __PALM_VFS_INC__
#   include <PalmVFS.inc>
#endif

#if (__PALM_OS__ >= 0x0400)

#ifdef __PALM_OS__

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class PalmVFS
// ----- -------
PalmVFS::File::File()
       : Ref(0)
{
}

PalmVFS::File::~File()
{
    Close();
}
////////////////////////////////////////////////////////////////////////////////////////
// class Volume VFS
// ----- ------ ---
uint16 PalmVFS::Volume::GetRefNumber()
{
    static uint16 _refnum_ = 0;

    if(_refnum_ == 0)
    {
        uint32 it = expIteratorStart;

        while(it != expIteratorStop)
        {
            Err err = ::VFSVolumeEnumerate(&_refnum_, &it);

            if(err == errNone)
            {
                break;
            }
        }
    }
    return _refnum_;
}
////////////////////////////////////////////////////////////////////////////////////////
// class PalmVFS
// ----- -------
PalmVFS::PalmVFS()
{
}

PalmVFS::~PalmVFS()
{
}
////////////////////////////////////////////////////////////////////////////////////////
// class XPalmVFS
// ----- --------
void PalmVFS::XPalmVFS::LoadErrorDescriptions()
{
    // base class
    PalmError::LoadErrorDescriptions();
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__
#endif

