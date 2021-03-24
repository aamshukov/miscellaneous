////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PROFILE_H__
#define __PROFILE_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class Profile
// ----- -------
class __DECLSPEC__ Profile
{
    protected:
     String<tchar>  Section;
     String<tchar>  FileName;
    public:
     // ctor/dtor
                    Profile(const tchar*, const tchar*);
                    Profile(const String<tchar>&, const String<tchar>&);
     virtual       ~Profile();

     // protocol
     int            GetInt(const tchar*, int = 0);
     bool           WriteInt(const tchar*, int);

     bool           GetString(const tchar*, tchar*, uint, const tchar* = _t(""));
     bool           WriteString(const tchar*, const tchar*);

     bool           GetSection(tchar*, uint);
     bool           WriteSection(const tchar*);

     void           Flush();
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PROFILE_H__
