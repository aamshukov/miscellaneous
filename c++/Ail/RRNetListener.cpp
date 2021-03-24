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

#ifndef __RR_NET_LISTENER_INC__
#   include <RRNetListener.inc>
#endif

__BEGIN_NAMESPACE__
__BEGIN_RRT_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class RRNetListener
// ----- -------------
RRNetListener::RRNetListener(ushort _port)
             : Port(_port)
{
}

RRNetListener::~RRNetListener()
{
}

int RRNetListener::Run()
{
    /////////////////////////////
    #define terminate()         \
        if(ShouldTerminate())   \
        {                       \
            break;              \
        }                       \
    /////////////////////////////
    try
    {
        Logfile::Instance().LogMessage(_t("entered into listener"), Logfile::Informational);

        RRNetManager* manager = null;

        Connection.GetLocalAddress().SetPort(Port);
        Connection.Listen();

        for(;;)
        {
            terminate()

            if(manager == null)
            {
                manager = new RRNetManager();
            }

            terminate()

            Logfile::Instance().LogMessage(_t("about to accept connection"), Logfile::Informational);
            Connection.Accept(manager->GetConnection());
            
            terminate()

            {
                tchar buffer[128];
                tchar ip[64];
                StrCopy(buffer, _t("accepted connection: "));
                manager->GetConnection().GetRemoteAddress().GetAddressAsString(ip);
                StrCaten(buffer, ip);
                Logfile::Instance().LogMessage(buffer, Logfile::Informational);
            }

            terminate()

            if(manager != null)
            {
                Logfile::Instance().LogMessage(_t("about to register connection with RRDispatcher"), Logfile::Informational);
                RRDispatcher::Instance().RegisterNetManager(manager);
                manager = null;
            }
        }
        Logfile::Instance().LogMessage(_t("about to leave the net listener"), Logfile::Informational);
        return 0;
    }
    catch(...)
    {
        Logfile::Instance().LogMessage(_t("exception net listener"), Logfile::Fatal);
        Listener::Instance().PostMessage(WM_USER+0x42, 0, 0);
        return -1;
    }
    ////////////////
    #undef terminate
    ////////////////
}

void RRNetListener::StopListener()
{
    if(State != Thread::Finished && State != Thread::Invalid)
    {
        Terminate();
        //
        IPv4Address address(_t("127.0.0.1"), Port);
        StreamSocket dummy(address);
        dummy.Connect();
    }
}
////////////////////////////////////////////////////////////////////////////////////////
__END_RRT_NAMESPACE__
__END_NAMESPACE__
