////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __HTT_PROTOCOL_H__
#define __HTT_PROTOCOL_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class HTTProtocol (RFC 2616)
// ----- ----------- ----------
class __DECLSPEC__ HTTProtocol
{
    public:

    ////////////////////
    // class HTTPContext
    // ----- -----------
    class __DECLSPEC__ HTTPContext
    {
        typedef AutoPtrArray<char> _Array;
        //
        public:
        _Array      Accept;
        _Array      AcceptCharset;
        _Array      AcceptEncoding;
        _Array      AcceptLanguage;
        _Array      AcceptRanges;
        _Array      Age;
        _Array      Allow;
        _Array      Authentication;
        _Array      Authorization;
        _Array      CacheControl;
        _Array      Connection; 
        _Array      ContentBase;
        _Array      ContentEncoding; 
        _Array      ContentLanguage; 
        _Array      ContentLength;
         uint64     Size;
         bool       Chunked;
        _Array      ContentLocation; 
        _Array      ContentMD5; 
        _Array      ContentRange;
        _Array      ContentTransferEncoding;
        _Array      ContentType;
		_Array		Cookie;
        _Array      Date;
        _Array      DerivedFrom;
        _Array      ETag;
        _Array      Expect;
        _Array      Expires;
        _Array      From;
        _Array      Forwarded;
        _Array      Host;
        _Array      IfMatch;
        _Array      IfMatchAny;
        _Array      IfModifiedSince;
        _Array      IfNoneMatch;
        _Array      IfNoneMatchAny;
        _Array      IfRange;
        _Array      IfUnmodifiedSince;
        _Array      KeepAlive;
        _Array      LastModified;
        _Array      Link;
        _Array      Location;
        _Array      MaxForwards;
        _Array      MessageId;
        _Array      MIME;
        _Array      Pragma;
        _Array      ProxyAuthenticate;
        _Array      ProxyAuthorization;
        _Array      Range;
        _Array      Referer;
        _Array      RetryAfter;
        _Array      Server;
        _Array      SetCookie;
        _Array      TE;
        _Array      Trailer;
        _Array      TransferEncoding;
        _Array      Upgrade;
        _Array      URI;
        _Array      UserAgent;
        _Array      Vary;
        _Array      Version;
        _Array      Via;
        _Array      Warning;
        _Array      WWWAuthenticate;
         //
         String<>   Unknown;
         String<>   Request;
        public:
         // ctor/dtor
                HTTPContext();
    };

    public:

    enum ECode
    {
        Code0   = 0,   // Unknown 
        Code100 = 100, // Continue
        Code101 = 101, // Switching Protocols
        Code200 = 200, // OK
        Code201 = 201, // Created
        Code202 = 202, // Accepted
        Code203 = 203, // Non-Authoritative Information
        Code204 = 204, // No Content
        Code205 = 205, // Reset Content
        Code206 = 206, // Partial Content
        Code300 = 300, // Multiple Choices
        Code301 = 301, // Moved Permanently
        Code302 = 302, // Found
        Code303 = 303, // See Other
        Code304 = 304, // Not Modified
        Code305 = 305, // Use Proxy
        Code306 = 306, // (Unused)
        Code307 = 307, // Temporary Redirect
        Code400 = 400, // Bad Request
        Code401 = 401, // Unauthorized
        Code402 = 402, // Payment Required
        Code403 = 403, // Forbidden
        Code404 = 404, // Not Found
        Code405 = 405, // Method Not Allowed
        Code406 = 406, // Not Acceptable
        Code407 = 407, // Proxy Authentication Required
        Code408 = 408, // Request Timeout
        Code409 = 409, // Conflict
        Code410 = 410, // Gone
        Code411 = 411, // Length Required
        Code412 = 412, // Precondition Failed
        Code413 = 413, // Request Entity Too Large
        Code414 = 414, // Request-URI Too Long
        Code415 = 415, // Unsupported Media Type
        Code416 = 416, // Requested Range Not Satisfiable
        Code417 = 417, // Expectation Failed
        Code500 = 500, // Internal Server Error
        Code501 = 501, // Not Implemented
        Code502 = 502, // Bad Gateway
        Code503 = 503, // Service Unavailable
        Code504 = 504, // Gateway Timeout
        Code505 = 505  // HTTP Version Not Supported
    };

    typedef HTTProtocol::ECode httpcode;

    public:
     // ctor/dtor
                            HTTProtocol();
                           ~HTTProtocol();

     // protocol
     static httpcode        GetResponseCode(const char*);
     static int             GetMajorVersion(const char*);
     static int             GetMinorVersion(const char*);
     static Time            GetDate(const char*);
     static bool            IsKeepCRLF(const char*);
     static bool            IsChunked(const char*);
     static uint            GetChunkSize(const char*);
     static fsize_t_        GetContentSize(const char*);
     static void            GetContentRange(const char*, fsize_t_&, fpos_t_&, fpos_t_&);
     static const tchar*    GetUserAgentField();
     static tchar*          GetLocation(const tchar*, tchar*);
     static tchar*          GetType(const char*, char*);
     static char*           GetEntityBoundary(const char*);

     static char*           SkipComments(char*);
     static char*           GetLine(const char*, char*, bool = true);
     //
     static void            ProcessHeader(const char*, HTTProtocol::HTTPContext&);
};
//
typedef HTTProtocol::ECode httpcode;
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __HTT_PROTOCOL_H__
