////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __RR_NET_LISTENER_H__
#define __RR_NET_LISTENER_H__

#pragma once

__BEGIN_NAMESPACE__
__BEGIN_RRT_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class RRNetListener
// ----- -------------
class __DECLSPEC__ RRNetListener : public Thread
{
    private:
     ushort         Port;
     StreamSocket   Connection;
    protected:
     virtual int    Run();
    public:
     // ctor/dtor
                    RRNetListener(ushort);
                   ~RRNetListener();

     // protocol
     void           StopListener();
};
////////////////////////////////////////////////////////////////////////////////////////
__END_RRT_NAMESPACE__
__END_NAMESPACE__

#endif // __RR_NET_LISTENER_H__
