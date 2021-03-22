////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __MEMORY_FILE_H__
#define __MEMORY_FILE_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class MemoryFile
// ----- ----------
template <typename _T = HANDLE, typename _Mutex = Synchronization::ThreadMutex<> > class MemoryFile : public Media<_T, _Mutex>
{
    typedef Media<_T, _Mutex> _Media;

    private:
                        MemoryFile(const MemoryFile&);
     const MemoryFile&  operator = (const MemoryFile&);
    private:
     // data members
     fsize_t_           Size;
    public:
     // ctor/dtor
                        MemoryFile(const tchar* = null, const tchar* = null, uint = Synchronization::TimeoutNoLimit);
     virtual           ~MemoryFile();

     // access
     const byte*        GetPointer()    const;

     // protocol
     void               Create(const tchar* = null, uint = 0);
     void               Open(const tchar* = null, uint = 0);
     void               Close();
     void               Destroy();

     void               GetPosition(fpos_t_&);
     void               SetPosition(fpos_t_, uint = _Media::Begin);

     void               GetSize(fsize_t_&);
     void               SetSize(fsize_t_);

     void               LockRange(fpos_t_, fsize_t_);
     void               UnlockRange(fpos_t_, fsize_t_);

     ulong              Read(void*, ulong, fpos_t_);
     ulong              Write(const void*, ulong, fpos_t_);
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __MEMORY_FILE_H__
