////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __OBJECTREF_H__
#define __OBJECTREF_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class ObjectRef
// ----- ---------
template <typename _T = uint> class ObjectRef
{
    private:
                        ObjectRef(const ObjectRef&);
     const ObjectRef&   operator = (const ObjectRef&);
    protected:
    _T                  Id;
    _T                  Reference;
    protected:
     virtual _T         AddReference();
     virtual _T         ReleaseReference();
    public:
     // ctor/dtor
                        ObjectRef();
                        ObjectRef(_T);
                       ~ObjectRef();

     // access
    _T                  GetId()             const;
     void               SetId(_T);

    _T                  GetReference()      const;
     void               AdjustReference(_T);
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __OBJECTREF_H__
