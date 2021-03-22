////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __AIL_H__
#   include <ail.hpp>
#endif

#ifndef __SOCKET_MANAGER_INC__
#   include <SocketManager.inc>
#endif

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class SocketManager
// ----- -------------
SocketManager::SocketManager(bool _auto_startup, bool _unload) : StartupCount(0)
{
    InitMemory(&Info, sizeof(WSAData));
    //
    if(_auto_startup)
    {
        Startup();
    }
}

SocketManager::~SocketManager()
{
    Shutdown();
}

int SocketManager::Startup(ushort _version)
{
    int rc = SocketModule::Startup(_version, &Info);

    if(rc == 0)
    {
        ++StartupCount;
    }
    return rc;
}

int SocketManager::Shutdown()
{
    while(StartupCount != 0)
    {
        if(SocketModule::Cleanup() != 0)
        {
            return SocketModule::GetLastError();
        }

        --StartupCount;
    }
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__
