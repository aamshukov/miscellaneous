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

#ifndef __URL_INC__
#   include <URL.inc>
#endif

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
    operator = (_other);
}

URL::URL(const tchar* _url) : URL_(_url)
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

URL& URL::operator = (const tchar* _url)
{
    URL_ = _url;
    return *this;
}

String<> URL::GetSchema() const
{
    if(URL_.IsEmpty())
    {
        return String<>();
    }

    const tchar* p_buff = URL_;
    const tchar* p_curr;
    const tchar* p_last;

    if((p_curr = StrSubstr(p_buff, _t("://"))) == null || p_curr == p_buff)
    {
        // everything is a host or schema is invalid [://www...]
        return String<>();
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

    return GetString(p_curr, (int)(p_last-p_curr));
}

String<> URL::GetSpecpart() const
{
    const tchar* p_curr = GetPtrToSpecpart();
    return p_curr == null ? String<>() : String<>(p_curr);
}

void URL::Correct()
{
    // the goal of the function is as follows (RFC 1738):
    //	trim leading, trailing and internal spaces
    //	encode all non US-ASCII chars 80-FF with escape (%xx)
    //  encode all ctl chars 00-1F & 7F with escape (%xx)
    // eliminates [URL:] entry
    const tchar* p_buff = URL_;

    // eliminate [URL:]
    if(StrNICompare(p_buff, _t("url:"), 4) == 0)
    {
        p_buff += 4;
    }
    //
	AutoPtrArray<tchar> buffer = new tchar[StrLen(p_buff)*3+1]; // *3 -> %xx
    StrCopy(buffer, p_buff);
	ConvertEsc(buffer, true);
    URL_ = buffer;
}

const tchar* URL::GetPtrToSpecpart() const
{
    if(URL_.IsEmpty())
    {
        return null;
    }

    const tchar* p_buff = URL_;
    const tchar* p_curr;

    // here we have [schema://] or [www...]
    if((p_curr = strstr(p_buff, _t("://"))) == null)
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

bool URL::IsDelimiter(tchar _ch)
{
//  static tchar* _delimiters_ = _t("/:@?");
    static byte _lutable_[] = "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000/\000\000\000\000\000\000\000\000\000\000:\000\000\000\000?@\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000";
    return _lutable_[static_cast<byte>(_ch)] != 0;
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__
