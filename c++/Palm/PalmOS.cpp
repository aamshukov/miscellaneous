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

#ifndef __PALM_OS_INC__
#   include <PalmOS.inc>
#endif

#ifdef __PALM_OS__

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class PalmOS
// ----- ------
const uint32 PalmOS::CreatorID    = 'AA67';
byte         PalmOS::RomID[]      = { 0 };
uint8        PalmOS::RomCheckSum  = 0;
const char*  PalmOS::StringStub   = " ";
const char*  PalmOS::MSEntryPoint = "/palm";
//

const byte* PalmOS::GetRomID(uint8& _checksum)
{
    // from "Palm OS Programmer's Companion"
    if(RomID[0] == 0)
    {
        uint16 count;
        byte* p = null;

        Err err = ::SysGetROMToken(PalmOS::GetCardNumber(), sysROMTokenSnum, &p, &count);

        if(err == errNone && PalmOS::RomID[0] != 0 && PalmOS::RomID[0] != 0xFF)
        {
            PalmOS::MemMove(static_cast<void*>(&PalmOS::RomID), p, Min(static_cast<uint16>(sizeof(PalmOS::RomID)), count));

            // calculate checksum
            PalmOS::RomCheckSum = 0;

            for(uint16 i = 0; i < count; i++)
            {
                PalmOS::RomCheckSum += PalmOS::RomID[i];
                PalmOS::RomCheckSum  = static_cast<uint8>((PalmOS::RomCheckSum << 1) | ((PalmOS::RomCheckSum & 0x80) >> 7));
            }
            PalmOS::RomCheckSum = static_cast<uint8>(((PalmOS::RomCheckSum >> 4) & 0x0F)+(PalmOS::RomCheckSum & 0x0F)+2);
        }
    }
   _checksum = PalmOS::RomCheckSum;
    return const_cast<const byte*>(RomID);
}

Err PalmOS::RomVersionCompatible(uint32 _required_version, uint16 _launch_flags)
{
    uint32 romversion;

    // see if we're on in minimum required version of the rom or later.
  ::FtrGet(sysFtrCreator, sysFtrNumROMVersion, &romversion);

    if(romversion < _required_version)
    {
        if((_launch_flags & (sysAppLaunchFlagNewGlobals | sysAppLaunchFlagUIApp)) == (sysAppLaunchFlagNewGlobals | sysAppLaunchFlagUIApp))
        {
            // Pilot 1.0 will continuously relaunch this app unless we switch to another safe one
            if(romversion < 0x02000000)
            {
                AppLaunchWithCommand(sysFileCDefaultApp, sysAppLaunchCmdNormalLaunch, null);
            }
        }
        return sysErrRomIncompatible;
    }
    return errNone;
}

uint32 PalmOS::ElfHash(const char* _buffer)
{
    // the published hash algorithm used in the UNIX ELF format for object files ...
    if(_buffer != null)
    {
        uint32 g;
        uint32 hash_value = 0;

        while(*_buffer !=  0)
        {
            hash_value = (hash_value << 4)+(*_buffer++);

            if((g = hash_value & 0xF0000000) != 0)
            {
                hash_value ^= g >> 24;
            }
            hash_value &= ~g;
        }

        return hash_value;
    }
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__
