////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of UI Library.                                                      .
//  1989-2003 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __AIL_H__
#   include <ail.hpp>
#endif

#ifndef __AUTOPTR_INC__
#   include <AutoPtr.inc>
#endif

#ifndef __LIST_INC__
#   include <List.inc>
#endif

#ifndef __OBJECT_H__
#   include <Object.hpp>
#endif

#ifndef __ICOMPARABLE_H__
#   include <IComparable.hpp>
#endif

#ifndef __ERRORENTRY_H__
#   include <ErrorEntry.hpp>
#endif

#ifndef __IERROR_H__
#   include <IError.hpp>
#endif

#ifndef __IERRORIMPL_H__
#   include <IErrorImpl.hpp>
#endif

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// IErrorImpl
// ----------
IErrorImpl::IErrorImpl() : List(ErrorKeyExtractor, ErrorComparator)
{
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__
