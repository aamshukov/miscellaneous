////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PALM_URL_H__
#define __PALM_URL_H__

#ifdef __PALM_OS__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class URL
// ----- ---
class __DECLSPEC__ URL
{
    // <URL>:<schema>:<schema-specific-part>
    protected:
    _string             URL_;
    protected:
     void               Correct();
     const char*        GetPtrToSpecpart()              const;
     //
     static bool	    IsDelimiter(char);
    public:
     static URL         DummyURL;
    public:
     // ctor/dtor
                        URL();
                        URL(const URL&);
                        URL(const char*);
     virtual           ~URL();

     // operators
     URL&               operator =  (const URL&);
     URL&               operator =  (const char*);

     bool               operator == (const URL&)        const;
     bool               operator == (const char*)       const;
     bool               operator != (const URL&)        const;
     bool               operator != (const char*)       const;

                        operator const char* ()         const;

     // access
     bool               IsURL()                         const;
    _string             GetURL()                        const;
     void               SetURL(const char*);

     // protocol
    _string             GetSchema()                     const;
    _string             GetSpecpart()                   const;

     virtual _string    GetHost()                       const;
     virtual uint16     GetPort()                       const;

     uint32             Hash()                          const;
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__
#endif // __PALM_URL_H__
