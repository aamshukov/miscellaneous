////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of UI Library.                                                      .
//  1998-2003 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __IERRORIMPL_H__
#define __IERRORIMPL_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// IErrorImpl
// ----------
interface __DECLSPEC__ IErrorImpl
{
    private:
       _ErrorKeyExtractor   ErrorKeyExtractor;
       _ErrorComparator     ErrorComparator;
        ErrorList           List;
    public:
        // ctor/dtor
                            IErrorImpl();

        // access
        const ErrorList&    GetErrorList() const;

        // api
        void                AddError(uint32);
        void                AddError(uint32, const tchar*);

        void                Discard();
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __IERRORIMPL_H__
