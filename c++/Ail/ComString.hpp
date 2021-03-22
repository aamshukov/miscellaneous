////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __COMSTRING_H__
#define __COMSTRING_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class ComString
// ----- ---------
class __DECLSPEC__ ComString
{
    private:
     BSTR               Str;
    private:
     char*             _W2A(BSTR);
     wchar*            _A2W(const char*);
    public:
                        ComString();
                        ComString(const ComString&);
                        ComString(uint);
                        ComString(uint, const wchar*);
                        ComString(const char*);
                        ComString(const wchar*);
                        ComString(const GUID&);
                       ~ComString();

     const ComString&   operator = (const ComString&);
     const ComString&   operator = (const wchar*);

                        operator BSTR ()                const;
     bool               operator ! ()                   const;
     BSTR*              operator & ();

     ComString&         operator += (const ComString&);
     bool               operator < (BSTR)               const;
     bool               operator == (BSTR)              const;
     bool               operator < (const char*);
     bool               operator == (const char*);

     bool               IsEmpty()                       const;

     char*              GetAsText();
     BSTR               GetStr()                        const;
     uint               GetCount()                      const;

     BSTR               Copy()                          const;
     HRESULT            CopyTo(BSTR*);

     void               Attach(BSTR);
     BSTR               Detach();
     void               Empty();

     HRESULT            Append(const wchar*);
     HRESULT            Append(const wchar*, uint);
     HRESULT            Append(const ComString&);
     HRESULT            AppendBSTR(BSTR);

     HRESULT            ToLower();
     HRESULT            ToUpper();

     bool               LoadString(HINSTANCE, uint);

     HRESULT            ReadFromStream(IStream*);
     HRESULT            WriteToStream(IStream*);
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __COMSTRING_H__
