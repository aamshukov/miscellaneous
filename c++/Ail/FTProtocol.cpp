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

#ifndef __FT_PROTOCOL_INC__
#   include <FTProtocol.inc>
#endif

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class FTProtocol
// ----- ----------
FTProtocol::FTProtocol()
{
}

FTProtocol::~FTProtocol()
{
}

ftpcode FTProtocol::GetResponseCode(const char* _line)
{
    xassert(_line != null, FTProtocol::Code0);
    //
    char* p_curr = const_cast<char*>(_line);
    p_curr = SkipSymbols(p_curr, Char::SPTAB);
    return static_cast<ftpcode>(StrToInteger(p_curr));
}

bool FTProtocol::IsMultiLineResponse(const char* _line)
{
    xassert(_line != null, false);

    const char* p_curr = _line;

    for(short i = 0; i < 3 && *p_curr != 0; i++, p_curr++)
    {
        if(!isdigit(*p_curr))
        {
            return false;
        }
    }

    if(*p_curr == Char::Minus)
    {
        return true;
    }
    return false;
}

String<> FTProtocol::GetMultiLineResponse(const char* _line)
{
    // syntax is as follows:
    //  response-code '-' first-line
    //  second line
    //  SP 123 third line
    //  response-code last line
    xassert(_line != null, String<>());

    char term[4];

    const char* p_buff = _line;
          char* p_term = term;
    const char* p_curr = p_buff;

    for(short i = 0; i < 3 && *p_curr != 0; i++)
    {
        *p_term++ = *p_curr++;
    }

    p_term = 0;

    if(*p_curr != Char::Minus || (p_curr = StrSubstr(p_curr, term)) == null)
    {
        return String<>();
    }

    String<> str;

    while(p_buff != p_curr)
    {
        str += *p_buff++;
    }

    while(*p_buff != Char::CR && *p_buff != Char::LF)
    {
        str += *p_buff++;
    }
    return str;
}

void FTProtocol::BuildPortRequest(uint _ip, ushort _port, char* _buffer)
{
    // syntax is as follows:
    //  h1,h2,h3,h4,p1,p2
    const ushort _port_mask_ = 0x00FF;
    const ushort _ip_mask_	 = 0x000000FF;
    //
    char buffer[32];
    ushort p = _port;

    uint x = 1;
    bool little_endian = (*(char*)&x) == 1;

    if(little_endian)
    {
        p = ((_port >> 8) & _port_mask_)|((_port & _port_mask_) << 8);
        sprintf(buffer, "%d,%d,%d,%d,%d,%d", (_ip >> 0)  & _ip_mask_, (_ip >> 8)  & _ip_mask_, (_ip >> 16) & _ip_mask_, (_ip >> 24) & _ip_mask_, (p >> 0) & _port_mask_, (p >> 8) & _port_mask_);
    }
    else
    {
        sprintf(buffer, "%d,%d,%d,%d,%d,%d", (_ip >> 24) & _ip_mask_, (_ip >> 16) & _ip_mask_, (_ip >> 8)  & _ip_mask_, (_ip >> 0)  & _ip_mask_, (p >> 8) & _port_mask_, (p >> 0) & _port_mask_);
    }
    StrCopy(_buffer, buffer);
}

void FTProtocol::ParseListLine(const char* _line)
{
    xassertv(_line != null);
    //
    const char* p_buff = _line;
    const char* p_curr = p_buff;

    if(isdigit(*p_curr))
    {
        // dos format
        // 03/08/2000  12:24p   <DIR>               Projects
        // 03/08/2000  12:24p           51,346,952  Projects
    }
    else
    {
        // unix format
        // ls does not show the year for dates in the last six months
        // netware uses 12 months period
        // drwx------  1    user    group           0 Jan 10 14:15 MyDir
        // -rwx------  1    user    group      117870 Feb 24 15:10 Banana.PNG
        // -rwx------  1    user    group      117870 Feb 24  1999 Banana.PNG
        bool isdir = *p_curr == 'd' || *p_curr == 'D';
    }
    
    // also NetWare:
    //  d [R----F--] supervisor            512       Jan 16 18:53    login
    //  - [R----F--] rhesus             214059       Oct 20 15:27    cx.exe
 
    // also NetPresenz for the Mac:
    //  -------r--         326  1391972  1392298 Nov 22  1995 MegaPhone.sit
    //  drwxrwxr-x               folder        2 May 10  1996 network

    // also MultiNet (some spaces removed from examples)
    //  00README.TXT;1      2 30-DEC-1996 17:44 [SYSTEM] (RWED,RWED,RE,RE)
    //  CORE.DIR;1          1  8-SEP-1996 16:09 [SYSTEM] (RWE,RWE,RE,RE)
    // and non-MutliNet VMS:
    //  CII-MANUAL.TEX;1  213/216  29-JAN-1996 03:33:12 [ANONYMOU,ANONYMOUS] (RWED,RWED,,)

    // some useless lines, safely ignored:
    //      "Total of 11 Files, 10966 Blocks." (VMS)
    //      "total 14786" (UNIX)
    //      "DISK$ANONFTP:[ANONYMOUS]" (VMS)
    //      "Directory DISK$PCSA:[ANONYM]" (VMS)
}

ftpcode FTProtocol::GetResourceSize(const char* _line, fsize_t_& _size)
{
    xassert(_line != null, FTProtocol::Code0);
    //
    ftpcode code = FTProtocol::GetResponseCode(_line);

    if(code == FTProtocol::Code213)
    {
        // syntax is as follows: rcode <SP> size
        char* p_curr = const_cast<char*>(_line);
        p_curr = SkipSymbols(p_curr, Char::SPTAB);
        p_curr = SkipTo(p_curr, Char::Space);
        p_curr = SkipSymbols(p_curr, Char::SPTAB);
       _size   = StrToInteger(p_curr);
    }
    return code;
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__
