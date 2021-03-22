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

#ifndef __OBJECT_H__
#   include <Object.hpp>
#endif

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// Value
// -----
Object::Object() : Id(0)
{
}

Object::~Object()
{
}

uint32 Object::GetId() const
{
    return Id;
}

void Object::SetId(uint32 _id)
{
    Id = _id;
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__
