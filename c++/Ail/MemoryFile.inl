////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __MEMORY_FILE_INL__
#define __MEMORY_FILE_INC__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class MemoryFile
// ----- ----------
template <typename _T, typename _Mutex> MemoryFile<_T, _Mutex>::MemoryFile(const tchar* _name, const tchar* _mutex_name, uint _timeout) : Media<_T, _Mutex>(null, _mutex_name, _timeout), Size(0)
{
}

template <typename _T, typename _Mutex> MemoryFile<_T, _Mutex>::~MemoryFile()
{
}

template <typename _T, typename _Mutex> __INLINE_TEMPLATE__ const byte* MemoryFile<_T, _Mutex>::GetPointer() const
{
    return Pointer;
}

template <typename _T, typename _Mutex> void MemoryFile<_T, _Mutex>::Create(const tchar*, uint)
{
}

template <typename _T, typename _Mutex> void MemoryFile<_T, _Mutex>::Open(const tchar*, uint)
{
}

template <typename _T, typename _Mutex> void MemoryFile<_T, _Mutex>::Close()
{
}

template <typename _T, typename _Mutex> void MemoryFile<_T, _Mutex>::Destroy()
{
}

template <typename _T, typename _Mutex> void MemoryFile<_T, _Mutex>::GetPosition(fpos_t_& _pos)
{
    _pos = 0;
}

template <typename _T, typename _Mutex> void MemoryFile<_T, _Mutex>::SetPosition(fpos_t_ _pos, uint _offset)
{
}

template <typename _T, typename _Mutex> void MemoryFile<_T, _Mutex>::GetSize(fsize_t_& _sz)
{
    _sz = Size;
}

template <typename _T, typename _Mutex> void MemoryFile<_T, _Mutex>::SetSize(fsize_t_ _sz)
{
    Size = _sz;
}

template <typename _T, typename _Mutex> void MemoryFile<_T, _Mutex>::LockRange(fpos_t_, fsize_t_)
{
}

template <typename _T, typename _Mutex> void MemoryFile<_T, _Mutex>::UnlockRange(fpos_t_, fsize_t_)
{
}

template <typename _T, typename _Mutex> ulong MemoryFile<_T, _Mutex>::Read(void*, ulong, fpos_t_)
{
    return 0;
}

template <typename _T, typename _Mutex> ulong MemoryFile<_T, _Mutex>::Write(const void*, ulong, fpos_t_)
{
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __MEMORY_FILE_INC__
