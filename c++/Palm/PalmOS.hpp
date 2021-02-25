////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  Copyright © 1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PALM_OS_H__
#define __PALM_OS_H__

#ifdef __PALM_OS__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
template <typename T> __INLINE_TEMPLATE__ const T& Min(const T& _t1, const T& _t2)
{
    return _t1 < _t2 ? _t1 : _t2;
}

template <typename T> __INLINE_TEMPLATE__ const T& Max(const T& _t1, const T& _t2)
{
    return _t1 > _t2 ? _t1 : _t2;
}
////////////////////////////////////////////////////////////////////////////////////////
/** 
 * @class PalmOS
 * @brief An utility class which wraps some useful functions for Palm OS API.
 */

////////////////////////////////////////////////////////////////////////////////////////
// class PalmOS
// ----- ------
class __DECLSPEC__ PalmOS
{
    public:

    enum EConst
    {
        eBufferSize    = 256,
        eUnknownCtrlID = 0
    };

    private:
     static const uint32    CreatorID;
     static byte            RomID[16]; // 12 digits
     static uint8           RomCheckSum;
    public:
     static const char*     StringStub;
     static const char*     MSEntryPoint;
    public:
    /** 
     *  Returns the creator id, which MUST be registered through Palm Company
     */
     static uint32          GetCreatorID();

    /** 
     *  Returns the unique ROM id
     */
     static const byte*     GetRomID(uint8&);

    /** 
     *  Returns a card number for an external memory card
     */
     static uint16          GetCardNumber();

    /** 
     *  Returns a database name
     */
     static void            GetDatabaseName(char*);

    /** 
     *  Checks version compatibility
     */
     static Err             RomVersionCompatible(uint32, uint16);

    /** 
     * @brief Memory functions
     *  Moves a memory block from one address to another
     */
     static Err             MemMove(void*, const void*, int32);

    /** 
     *  Copies a memory block from one address to another
     */
     static Err             MemCopy(void*, const void*, int32);

    /** 
     *  Fills out a memory block of a given size with a pattern
     */
     static Err             MemSet(void*, int32, byte = 0);

    /** 
     *  Compares two memory blocks and returns -1
     *  if the first block is less then the second one,
     *  or 0 if they are equal and 1 in other cases
     */
     static int16           MemCompare(const void*, const void*, int32);

    /** 
     *  Published hash algorithm used in UNIX ELF format for object files
     */
     static uint32          ElfHash(const char*);

    /** 
     *  Converts seconds to Palm OS dependent ticks
     */
     static int32           SecondsToTicks(uint16);
};
////////////////////////////////////////////////////////////////////////////////////////
// macros
// ------
#define DECLARE_BUFFER                                  \
    char buffer[PalmOS::eBufferSize];                   \
    buffer[0] = 0;                                      \

#define BUFFER_SIZE                                     \
    sizeof(buffer)/sizeof(buffer[0])                    \
////////////////////////////////////////////////////////////////////////////////////////
typedef std::string _string;
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__
#endif // __PALM_OS_H__
