////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __MODULE_INL__
#define __MODULE_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class Module
// ----- ------
__INLINE__ bool Module::IsValid() const
{
    return Handle > 0;
}

__INLINE__ bool Module::ShouldFree() const
{
    return Free;
}

__INLINE__ HMODULE Module::GetModule() const
{
    return Handle;
}

__INLINE__ void Module::SetModule(HMODULE _handle)
{
    if(!ShouldFree())
    {
        Handle = _handle;
    }
}

__INLINE__ String<tchar> Module::GetName() const
{
    return Name;
}

__INLINE__ void Module::SetName()
{
    if(IsValid())
    {
        Name = GetModuleFileName();
    }
}

__INLINE__ void Module::SetName(const _string& _name)
{
    Name = _name;
}

__INLINE__ Module::operator HMODULE () const
{
    return Handle;
}

__INLINE__ bool Module::operator == (const Module& _other) const
{
    return GetModule() == _other.GetModule();
}

__INLINE__ FARPROC Module::GetProcAddress(const char* _proc) const
{
    if(IsValid())
    {
        return ::GetProcAddress(Handle, _proc);
    }
    return null;
}

__INLINE__ HRSRC Module::FindResource(uint _id, const tchar* _type) const
{
    if(IsValid())
    {
        return ::FindResource(Handle, MAKEINTRESOURCE(_id), _type);
    }
    return null;
}

__INLINE__ HGLOBAL Module::LoadResource(HRSRC _resource) const
{
    if(IsValid())
    {
        return ::LoadResource(Handle, _resource);
    }
    return null;
}

__INLINE__ uint Module::SizeOfResource(HRSRC _resource) const
{
    if(IsValid())
    {
        return ::SizeofResource(Handle, _resource);
    }
    return 0;
}

__INLINE__ bool Module::GetClassInfo(const tchar* _name, WNDCLASS& _ci) const
{
    if(IsValid())
    {
        return ::GetClassInfo(Handle, _name, &_ci) > 0;
    }
    return false;
}

__INLINE__ bool Module::LoadString(uint _id, tchar* _buffer, uint _count) const
{
    if(IsValid())
    {
        return StringFromResource(_buffer, _count, _id, Handle);
    }
    return false;
}

__INLINE__ HBITMAP Module::LoadBitmap(uint _id) const
{
    if(IsValid())
    {
        return ::LoadBitmap(Handle, MAKEINTRESOURCE(_id));
    }
    return null;
}

__INLINE__ HACCEL Module::LoadAccelerators(uint _id) const
{
    if(IsValid())
    {
        return ::LoadAccelerators(Handle, MAKEINTRESOURCE(_id));
    }
    return null;
}

__INLINE__ HMENU Module::LoadMenu(uint _id) const
{
    if(IsValid())
    {
        return ::LoadMenu(Handle, MAKEINTRESOURCE(_id));
    }
    return null;
}

__INLINE__ HCURSOR Module::LoadCursor(uint _id) const
{
    if(IsValid())
    {
        return ::LoadCursor(Handle, MAKEINTRESOURCE(_id));
    }
    return null;
}

__INLINE__ HICON Module::LoadIcon(const tchar* _name) const
{
    if(IsValid())
    {
        return ::LoadCursor(Handle, _name);
    }
    return null;
}

__INLINE__ HANDLE Module::LoadImage(const tchar* _name, uint _type, int _cx, int _cy, uint _flags) const
{
    if(IsValid())
    {
        return ::LoadImage(Handle, _name, _type, _cx, _cy, _flags);
    }
    return null;
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __MODULE_INL__
