////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __MEDIA_H__
#define __MEDIA_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class Media
// ----- -----
template <typename _T, typename _Mutex = Synchronization::ThreadMutex<> > class Media
{
    typedef Handle<_T>          _Handle;
    typedef Media<_Mutex>       _Media;
    typedef AutoPtrArray<tchar> _Name;

    public:

    enum EPosition
    {
        Begin   = 0x01,
        Current = 0x02,
        End     = 0x04
    };

    private:
//                      Media(const Media&);
//     const Media&     operator = (const Media&);
    protected:
     // data members
    _Handle           Handle;
    _Mutex            Mutex;
    _Name             Name;
    protected:      
     // protocol
     virtual void     Create(const tchar*, uint)                    = 0;
     virtual void     Open(const tchar*, uint)                      = 0;
     virtual void     Close()                                       = 0;
     virtual void     Destroy()                                     = 0;
                    
     virtual void     GetPosition(fpos_t_&)                         = 0;
     virtual void     SetPosition(fpos_t_, uint = _Media::Begin)    = 0;
                    
     virtual void     GetSize(fsize_t_&)                            = 0;
     virtual void     SetSize(fsize_t_)                             = 0;
                    
     virtual void     LockRange(fpos_t_, fsize_t_)                  = 0;
     virtual void     UnlockRange(fpos_t_, fsize_t_)                = 0;
                    
     virtual ulong    Read(void*, ulong, fpos_t_)                   = 0;
     virtual ulong    Write(const void*, ulong, fpos_t_)            = 0;
    public:         
     // ctor/dtor   
                      Media(const tchar* = null, const tchar* = null, uint = Synchronization::TimeoutNoLimit);
     virtual         ~Media();
                    
     // access      
     bool             IsValid()     const;
     const _Handle*   GetHandle()   const;
     const _Mutex*    GetMutex()    const;
     const tchar*     GetName()     const;
};
////////////////////////////////////////////////////////////////////////////////////////
// class MediaLock
// ----- ---------
template <typename _Media = File<> > class MediaLock
{
    private:
    _Media&   Media;
     fpos_t_  Position;
     fsize_t_ Count;
    public:
              MediaLock(_Media&, fpos_t_ = -1, fsize_t_ = -1);
             ~MediaLock();
};
////////////////////////////////////////////////////////////////////////////////////////
// class MediaPos
// ----- --------
template <typename _Media = File<> > class MediaPos
{
    private:
    _Media&   Media;
     fpos_t_  Position;
    public:
              MediaPos(_Media&, fpos_t_ = -1);
             ~MediaPos();
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __MEDIA_H__
