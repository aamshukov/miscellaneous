////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __AIL_H__
#   include <ail.hpp>
#endif

#ifndef __PALM_URL_INC__
#   include <PalmURL.inc>
#endif

#ifdef __PALM_OS__

__BEGIN_NAMESPACE__
//
URL URL::DummyURL;
////////////////////////////////////////////////////////////////////////////////////////
// class URL
// ----- ---
URL::URL()
{
}

URL::URL(const URL& _other)
{
    if(this != &_other)
    {
        URL_ = _other.URL_;
    }
}

URL::URL(const char* _url) : URL_(_url)
{
    Correct();
}

URL::~URL()
{
}

URL& URL::operator = (const URL& _other)
{
    if(this != &_other)
    {
        URL_ = _other.URL_;
    }
    return *this;
}

URL& URL::operator = (const char* _url)
{
    URL_ = _url;
    return *this;
}

_string URL::GetSchema() const
{
    if(URL_.empty())
    {
        return _string();
    }

    const char* p_buff = URL_.c_str();
    const char* p_curr;
    const char* p_last;

    if((p_curr = PalmText::StrStr(p_buff, "://")) == null || p_curr == p_buff)
    {
        // everything is a host or schema is invalid [://www...]
        return _string();
    }

    p_last = p_curr--;

    while(p_curr != p_buff && !URL::IsDelimiter(*p_curr))
    {
        --p_curr;
    }

    if(p_curr != p_buff)
    {
        ++p_curr;
    }

    return PalmText::GetString(p_curr, static_cast<uint32>(p_last-p_curr));
}

_string URL::GetSpecpart() const
{
    const char* p_curr = GetPtrToSpecpart();
    return p_curr == null ? _string() : _string(p_curr);
}

void URL::Correct()
{
    // the goal of the function is as follows (RFC 1738):
    //	trim leading, trailing and internal spaces
    //	encode all non US-ASCII chars 80-FF with escape (%xx)
    //  encode all ctl chars 00-1F & 7F with escape (%xx)
    // eliminates [URL:] entry
    const char* p_buff = URL_.c_str();

    // eliminate [URL:]
    if(PalmText::StrNCaselessCompare(p_buff, "url:", 4) == 0)
    {
        p_buff += 4;
    }
    //
	AutoPtrArray<char> buffer = new char[PalmText::StrLen(p_buff)*3+1]; // *3 -> %xx
    PalmText::StrCopy(buffer, p_buff);
	PalmText::ConvertEsc(buffer, true);
    URL_ = buffer;
}

const char* URL::GetPtrToSpecpart() const
{
    if(URL_.empty())
    {
        return null;
    }

    const char* p_buff = URL_.c_str();
    const char* p_curr;

    // here we have [schema://] or [www...]
    if((p_curr = PalmText::StrStr(p_buff, "://")) == null)
    {
        // everything is a spec part
        return p_buff;
    }
    else
    {
        while(*p_curr != 0 && URL::IsDelimiter(*p_curr))
        {
            ++p_curr;
        }
        return p_curr;
    }
}

bool URL::IsDelimiter(char _ch)
{
//  static char* _delimiters_ = "/:@?";
    static byte _lutable_[] = "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000/\000\000\000\000\000\000\000\000\000\000:\000\000\000\000?@\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000";
    return _lutable_[static_cast<byte>(_ch)] != 0;
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__
