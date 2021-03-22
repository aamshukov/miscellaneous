////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __MEDIA_INL__
#define __MEDIA_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class Media
// ----- -----
template <typename _T, typename _Mutex> Media<_T, _Mutex>::Media(const tchar* _name, const tchar* _mutex_name, uint _timeout) : Mutex(_mutex_name, _timeout)
{
    if(_name != null)
    {
        Name = StrClone(_name);
    }
}

template <typename _T, typename _Mutex> Media<_T, _Mutex>::~Media()
{
}

template <typename _T, typename _Mutex> __INLINE_TEMPLATE__ bool Media<_T, _Mutex>::IsValid() const
{
    return Handle != 0 && Handle != INVALID_HANDLE_VALUE;
}

template <typename _T, typename _Mutex> __INLINE_TEMPLATE__ const Handle<_T>* Media<_T, _Mutex>::GetHandle() const
{
    return reinterpret_cast<const Handle<_T>*>(&Handle);
}

template <typename _T, typename _Mutex> __INLINE_TEMPLATE__ const _Mutex* Media<_T, _Mutex>::GetMutex() const
{
    return reinterpret_cast<const _Mutex*>(&Mutex);
}

template <typename _T, typename _Mutex> __INLINE_TEMPLATE__ const tchar* Media<_T, _Mutex>::GetName() const
{
    return reinterpret_cast<const tchar*>(Name);
}
////////////////////////////////////////////////////////////////////////////////////////
// class MediaLock
// ----- ---------
template <typename _Media> MediaLock<_Media>::MediaLock(_Media& _media, fpos_t_ _pos, fsize_t_ _count) : Media(_media)
{
    Position = _pos   != fpos_t_(-1)  ? _pos   : 0;
    Count    = _count != fsize_t_(-1) ? _count : 0;

    if(Count == 0)
    {
        Media.GetSize(Count);
    }
    
    Media.LockRange(Position, Count);
}

template <typename _Media> MediaLock<_Media>::~MediaLock()
{
    Media.UnlockRange(Position, Count);
}
////////////////////////////////////////////////////////////////////////////////////////
// class MediaPos
// ----- --------
template <typename _Media> MediaPos<_Media>::MediaPos(_Media& _media, fpos_t_ _pos) : Media(_media)
{
    Media.GetPosition(Position);
    
    if(_pos != -1)
    {
        Media.SetPosition(_pos);
    }
}

template <typename _Media> MediaPos<_Media>::~MediaPos()
{
    Media.SetPosition(Position);
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __MEDIA_INL__
