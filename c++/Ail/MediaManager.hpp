////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __MEDIA_MANAGER_H__
#define __MEDIA_MANAGER_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
#pragma pack(push, before, 2)
////////////////////////////////////////////////////////////////////////////////////////
// class MediaManager
// ----- ------------
template <typename _Media = File<>, typename _Mutex = Synchronization::ThreadMutex<> > class MediaManager
{
    private:

    class _Header
    {
        friend class MediaManager<_Media, _Mutex>;

        private:
         // id
         uint16                 MagicNumber;            // magic number
         byte                   Signature[16*2];        // unicode string

         // info
         uint16                 Version;                // 01.25

         uint16                 OS;                     // original OS
         byte                   DescOS[160];            // original OS desc

         uint16                 ByteOrder;              // big/little endian

         byte                   UUID[16];               // CORBA/COM compliant feature

         uint32                 CRC32;                  // check integrity with CRC32 algo
         byte                   MD5[16];                // check integrity with MD5 algo

         uint32                 LanguageId;             // original LCID

         byte                   Desc[64];               // description of media
         byte                   UserInfo[64];           // user info

         byte                   SearchCriteria[128];    // search criteria (index, filter and so on)

         // WHO WHAT WHEN WHERE WHY
         byte                   CreateId[64];           // WHO created media
         byte                   AccessId[64];           // WHO had last access to media

         byte                   Category[64];           // WHAT category media is belonged

        _time                   CreationTime;           // WHEN media was created
        _time                   LastAccessTime;         // WHEN media was written to, read from
        _time                   LastWriteTime;          // WHEN media was written to
        _time                   LifeTime;               // WHEN (life time - 0 unlimited) will be deleted
                                                        //      even if LinkCount != 0

         byte                   CreateLocation[64];     // WHERE media was created
         byte                   AccessLocation[64];     // WHERE media file was opened last time

         byte                   CreateReason[64];       // WHY media was created
         byte                   AccessReason[64];       // WHY media was opened last time

         // system
         uint32                 OffsetToData;           // offset to actual data
         uint32                 LinkCount;              // how many hard links media has
                                                        // if == 0 will be deleted by monitor

         uint32                 Flags;                  // system flags

         byte                   Reserved[36];           // for future (1024)
        public:
                               _Header()
                                {
                                    InitMemory(this, sizeof(*this));
                                };

                              ~_Header()
                                {
                                }
    };

    public:

    enum EFlag
    {
        None = 0x00000000
    };

    enum EOS
    {
        Unknown   = 0,
        WindowsNT = 1,
        Windows95 = 2,
        Windows98 = 3
     // Custom    = 100+
    };

    enum EByteOrder
    {
        LittleEndian = 1234,  // wintel
        BigEndian    = 4321   // IBM, net
    };

    private:
     uint           Flags;
    _Header         Header;
    _Media          Media;
    _Mutex          Mutex;
     //
     static ushort  ConstMagicNumber;
     static ushort  ConstVersion;
     static const tchar*
                    ConstSignature;
    private:
     void           AdjustPointer(fpos_t_);
     void           xxassert(int, uint = X::InvalidArg);
    protected:
     void           InitHeader();
     void           ReadHeader();
     void           WriteHeader();
    public:
     // ctor/dtor
                    MediaManager(uint32 = MediaManager::None, const tchar* = null, uint = Synchronization::TimeoutNoLimit);
     virtual       ~MediaManager();

     // media
     const _Media&  GetMedia()                                  const;

     // header
     const _Header& GetHeader()                                 const;

     uint16         GetMagicNumber()                            const;
     void           GetSignature(byte*)                         const;

     uint16         GetVersion()                                const;

     uint16         GetOS()                                     const;

     void           GetDescOS(byte*)                            const;
     void           SetDescOS(const byte*);

     uint16         GetByteOrder()                              const;
     void           SetByteOrder(uint16);

     void           GetUUID(byte*)                              const;
     void           SetUUID(const byte*);

     uint32         GetCRC32()                                  const;
     void           GetMD5(byte*)                               const;

     uint32         GetLanguageId()                             const;
     void           SetLanguageId(uint32);

     void           GetDesc(byte*)                              const;
     void           SetDesc(const byte*);

     void           GetUserInfo(byte*)                          const;
     void           SetUserInfo(const byte*);

     void           GetSearchCriteria(byte*)                    const;
     void           SetSearchCriteria(const byte*);

     void           GetCreateId(byte*)                          const;
     void           SetCreateId(const byte*);

     void           GetAccessId(byte*)                          const;
     void           SetAccessId(const byte*);

     void           GetCategory(byte*)                          const;
     void           SetCategory(const byte*);

     void           GetCreationTime(_time&)                     const;

     void           GetLifeTime(_time&)                         const;
     void           SetLifeTime(const _time&);

     void           GetCreateLocation(byte*)                    const;
     void           SetCreateLocation(const byte*);

     void           GetAccessLocation(byte*)                    const;
     void           SetAccessLocation(const byte*);

     void           GetCreateReason(byte*)                      const;
     void           SetCreateReason(const byte*);

     void           GetAccessReason(byte*)                      const;
     void           SetAccessReason(const byte*);

     uint32         GetOffsetToData()                           const;
     void           SetOffsetToData(uint32);

     uint32         GetLinkCount()                              const;
     void           SetLinkCount(uint32);
     uint32         IncreaseLinkCount();
     uint32         DecreaseLinkCount();

     uint32         GetMediaFlags()                             const;
     void           SetMediaFlags(uint32);

     // access
     uint           GetFlags()                                  const;
     void           SetFlags(uint);

     // protocol
     void           Create(const tchar*, uint = _Media::CreateNew|_Media::AccessReadWrite|_Media::ShareExclusive);
     void           Open(const tchar*, uint = _Media::AccessReadWrite|_Media::ShareExclusive);
     void           Close();

     void           LockRange(fpos_t_, fsize_t_);
     void           UnlockRange(fpos_t_, fsize_t_);

     ulong          Read(void*, ulong, fpos_t_ = -1);
     ulong          Write(const void*, ulong, fpos_t_ = -1);

     void           Flush();

     // integrity
     void           CalculateCRC32();
     void           CalculateMD5();
};
////////////////////////////////////////////////////////////////////////////////////////
// class XMediaManager
// ----- -------------
class __DECLSPEC__ XMediaManager : public X
{
    public:

    enum EError
    {
        InvalidHeader    = 0x00000010,
        InvalidCRC32     = 0x00000020,
        InvalidMD5       = 0x00000040,
        InvalidLinkCount = 0x00000080
    };

    public:
        XMediaManager(uint = X::Failure);
       ~XMediaManager();
};
////////////////////////////////////////////////////////////////////////////////////////
#pragma pack(pop, before)
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __MEDIA_MANAGER_H__
