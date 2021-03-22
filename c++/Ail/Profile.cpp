////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __AIL_H__
#   include <ail.hpp>
#endif

#ifndef __PROFILE_INC__
#   include <Profile.inc>
#endif

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class Profile
// ----- -------
Profile::Profile(const tchar* _section, const tchar* _filename) : Section(_section), FileName(_filename)
{
}

Profile::Profile(const String<tchar>& _section, const String<tchar>& _filename) : Section(_section), FileName(_filename)
{
}

Profile::~Profile()
{
    Flush();
}

int Profile::GetInt(const tchar* _key, int _default_int)
{
    if(FileName.IsEmpty())
    {
        return ::GetProfileInt(LPCTSTR(Section), _key, _default_int);
    }
    else
    {
        return ::GetPrivateProfileInt(Section, _key, _default_int, FileName);
    }
}

bool Profile::WriteInt(const tchar* _key, int _value)
{
    AutoPtrArray<tchar> buffer = new tchar[TEXT_SIZE_SMALL];
    compose(buffer, _t("%d"), _value);
    return WriteString(_key, buffer);
}

bool Profile::GetString(const tchar* _key, tchar* _buffer, uint _count, const tchar* _default_str)
{
    if(_buffer != null)
    {
        _buffer[0] = 0;
    }

    if(FileName.IsEmpty())
    {
        return ::GetProfileString(Section, _key, _default_str, _buffer, _count) != 0;
    }
    else
    {
        return ::GetPrivateProfileString(Section, _key, _default_str, _buffer, _count, FileName) != 0;
    }
}

bool Profile::WriteString(const tchar* _key, const tchar* _str)
{
    if(FileName.IsEmpty())
    {
        return ::WriteProfileString(Section, _key, _str) != 0;
    }
    else
    {
        return ::WritePrivateProfileString(Section, _key, _str, FileName) != 0;
    }
}

bool Profile::GetSection(tchar* _section, uint _count)
{
    if(_section != null)
    {
        _section[0] = 0;
    }

    if(FileName.IsEmpty())
    {
        return ::GetProfileSection(Section, _section, _count) != 0;
    }
    else
    {
        return ::GetPrivateProfileSection(Section, _section, _count, FileName) != 0;
    }
}

bool Profile::WriteSection(const tchar* _section)
{
    if(FileName.IsEmpty())
    {
        return ::WriteProfileSection(Section, _section) != 0;
    }
    else
    {
        return ::WritePrivateProfileSection(Section, _section, FileName) != 0;
    }
}

void Profile::Flush()
{
    if(!FileName.IsEmpty())
    {
        ::WritePrivateProfileString(0, 0, 0, FileName);
    }
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

