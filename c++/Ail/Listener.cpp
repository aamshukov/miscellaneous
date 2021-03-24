////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __AIL_H__
#   include <ail.hpp>
#endif

#ifndef __LISTENER_INC__
#   include <Listener.inc>
#endif

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class Listener
// ----- --------
Listener::Listener() : HListener(0)
{
}

Listener::~Listener()
{
    HListener = 0;
}

int Listener::SendMessage(uint _message, uint _p1, uint _p2)
{
    if(HListener != 0)
    {
        return ::SendMessage(HListener, _message, _p1, _p2);
    }
    return 0;
}

int Listener::PostMessage(uint _message, uint _p1, uint _p2)
{
    if(HListener != 0)
    {
        return ::PostMessage(HListener, _message, _p1, _p2);
    }
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__
