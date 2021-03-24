////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __URL_H__
#define __URL_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class URL
// ----- ---
class __DECLSPEC__ URL : public NetAddress
{
    // <URL>:<schema>:<schema-specific-part>
    typedef String<> _String;

    protected:
    _String             URL_;
    protected:
     void               Correct();
     const tchar*       GetPtrToSpecpart()              const;
     //
     static bool	    IsDelimiter(tchar);
    public:
     static URL         DummyURL;
    public:
     // ctor/dtor
                        URL();
                        URL(const URL&);
                        URL(const tchar*);
     virtual           ~URL();

     // operators
     URL&               operator =  (const URL&);
     URL&               operator =  (const tchar*);

     bool               operator == (const URL&)        const;
     bool               operator == (const tchar*)      const;
     bool               operator != (const URL&)        const;
     bool               operator != (const tchar*)      const;

                        operator tchar* ();
                        operator const tchar* ()        const;

     // access
     bool               IsURL()                         const;
    _String             GetURL()                        const;
     void               SetURL(const tchar*);

     // protocol
    _String             GetSchema()                     const;
    _String             GetSpecpart()                   const;

     virtual _String    GetHost()                       const;
     virtual ushort     GetPort()                       const;

     ulong              Hash()                          const;
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __URL_H__
