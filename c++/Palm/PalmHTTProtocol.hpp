////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PALM_HTT_PROTOCOL_H__
#define __PALM_HTT_PROTOCOL_H__

#ifdef __PALM_OS__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class HTTProtocol (RFC 2616)
// ----- ----------- ----------
class __DECLSPEC__ HTTProtocol
{
    public:

    class __DECLSPEC__ HTTPContext
    {
        typedef AutoPtrArray<char> _array;
        //
        public:
        _array      Accept;
        _array      AcceptCharset;
        _array      AcceptEncoding;
        _array      AcceptLanguage;
        _array      AcceptRanges;
        _array      Age;
        _array      Allow;
        _array      Authentication;
        _array      Authorization;
        _array      CacheControl;
        _array      Connection; 
        _array      ContentBase;
        _array      ContentEncoding; 
        _array      ContentLanguage; 
        _array      ContentLength;
         uint32     Size;
         bool       Chunked;
        _array      ContentLocation; 
        _array      ContentMD5; 
        _array      ContentRange;
        _array      ContentTransferEncoding;
        _array      ContentType;
		_array		Cookie;
        _array      Date;
        _array      DerivedFrom;
        _array      ETag;
        _array      Expect;
        _array      Expires;
        _array      From;
        _array      Forwarded;
        _array      Host;
        _array      IfMatch;
        _array      IfMatchAny;
        _array      IfModifiedSince;
        _array      IfNoneMatch;
        _array      IfNoneMatchAny;
        _array      IfRange;
        _array      IfUnmodifiedSince;
        _array      KeepAlive;
        _array      LastModified;
        _array      Link;
        _array      Location;
        _array      MaxForwards;
        _array      MessageId;
        _array      MIME;
        _array      Pragma;
        _array      ProxyAuthenticate;
        _array      ProxyAuthorization;
        _array      Range;
        _array      Referer;
        _array      RetryAfter;
        _array      Server;
        _array      SetCookie;
        _array      TE;
        _array      Trailer;
        _array      TransferEncoding;
        _array      Upgrade;
        _array      URI;
        _array      UserAgent;
        _array      Vary;
        _array      Version;
        _array      Via;
        _array      Warning;
        _array      WWWAuthenticate;
         //
        _string     Unknown;
        _string     Request;
        public:
         // ctor/dtor
                HTTPContext();
    };

    public:

    enum ECode
    {
        eCode0   = 0,   // Unknown 
        eCode100 = 100, // Continue
        eCode101 = 101, // Switching Protocols
        eCode200 = 200, // OK
        eCode201 = 201, // Created
        eCode202 = 202, // Accepted
        eCode203 = 203, // Non-Authoritative Information
        eCode204 = 204, // No Content
        eCode205 = 205, // Reset Content
        eCode206 = 206, // Partial Content
        eCode300 = 300, // Multiple Choices
        eCode301 = 301, // Moved Permanently
        eCode302 = 302, // Found
        eCode303 = 303, // See Other
        eCode304 = 304, // Not Modified
        eCode305 = 305, // Use Proxy
        eCode306 = 306, // (Unused)
        eCode307 = 307, // Temporary Redirect
        eCode400 = 400, // Bad Request
        eCode401 = 401, // Unauthorized
        eCode402 = 402, // Payment Required
        eCode403 = 403, // Forbidden
        eCode404 = 404, // Not Found
        eCode405 = 405, // Method Not Allowed
        eCode406 = 406, // Not Acceptable
        eCode407 = 407, // Proxy Authentication Required
        eCode408 = 408, // Request Timeout
        eCode409 = 409, // Conflict
        eCode410 = 410, // Gone
        eCode411 = 411, // Length Required
        eCode412 = 412, // Precondition Failed
        eCode413 = 413, // Request Entity Too Large
        eCode414 = 414, // Request-URI Too Long
        eCode415 = 415, // Unsupported Media Type
        eCode416 = 416, // Requested Range Not Satisfiable
        eCode417 = 417, // Expectation Failed
        eCode500 = 500, // Internal Server Error
        eCode501 = 501, // Not Implemented
        eCode502 = 502, // Bad Gateway
        eCode503 = 503, // Service Unavailable
        eCode504 = 504, // Gateway Timeout
        eCode505 = 505  // HTTP Version Not Supported
    };

    typedef HTTProtocol::ECode httpcode;

    public:
     // ctor/dtor
                            HTTProtocol();
                           ~HTTProtocol();

     // api
     static httpcode        GetResponseCode(const char*);
     static int32           GetMajorVersion(const char*);
     static int32           GetMinorVersion(const char*);
     static _time_t         GetDate(const char*);
     static bool            IsKeepCRLF(const char*);
     static bool            IsChunked(const char*);
     static uint32          GetChunkSize(const char*);
     static fsize_t_        GetContentSize(const char*);
     static void            GetContentRange(const char*, fsize_t_&, fpos_t_&, fpos_t_&);
     static const char*     GetUserAgentField();
     static char*           GetLocation(const char*, char*);
     static char*           GetType(const char*, char*);
     static char*           GetEntityBoundary(const char*);

     static char*           SkipComments(char*);
     static char*           GetLine(const char*, char*, bool = true);
     //
     static void            ProcessHeader(const char*, HTTProtocol::HTTPContext&);

    public:

    class __DECLSPEC__ XHTTProtocol : public PalmError
    {
        public:

        enum EErrors
        {
            // appErrorClass+'http'
        };

        public:
         virtual void LoadErrorDescriptions();
    };

    friend class XHTTProtocol;
};
//
typedef HTTProtocol::ECode httpcode;
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__
#endif // __PALM_HTT_PROTOCOL_H__
