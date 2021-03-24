////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of UI Library.                                                      .
//  1998-2003 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __AIL_H__
#   include <ail.hpp>
#endif

#ifndef __IDELETEABLE_H__
#   include <IDeleteable.hpp>
#endif

#ifndef __IDELETEABLEIMPL_H__
#   include <IDeleteableImpl.hpp>
#endif

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// IDeleteableImpl
// ---------------
IDeleteableImpl::IDeleteableImpl(IDeleteableImpl::EDelState _state) : State(_state)
{
}

__INLINE__ bool IDeleteableImpl::ShouldDelete() const
{
    return State == IDeleteableImpl::eDelete;
}

__INLINE__ IDeleteableImpl::EDelState IDeleteableImpl::GetDelState() const
{
    return State;
}

__INLINE__ void IDeleteableImpl::SetDelState(IDeleteableImpl::EDelState _state)
{
    State = _state;
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__
