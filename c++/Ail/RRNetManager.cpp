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

#ifndef __RR_NET_MANAGER_INC__
#   include <RRNetManager.inc>
#endif

__BEGIN_NAMESPACE__
__BEGIN_RRT_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class RRSender
// ----- --------
RRNetManager::RRSender::RRSender(RRNetManager& _manager)
            : Manager(_manager)
{
}

RRNetManager::RRSender::~RRSender()
{
}

int RRNetManager::RRSender::Run()
{
    try
    {
        for(;;)
        {
            if(ShouldTerminate())
            {
                break;
            }

            Manager.STrigger.WaitEvent(TimeoutManager::Instance().GetTriggerTimeout());

            while(!Manager.PQ.IsEmpty())
            {
                if(ShouldTerminate())
                {
                    goto _exit;
                }

                RRTransaction::Packet* p = (RRTransaction::Packet*)Manager.PQ.GetRoot();

                // assemble packet
//    Synchronization::Guard<_Mutex> guard(Mutex);
/*
                STACK_BUFFER(RRTransaction::PacketSize, byte)
                InitMemory(buffer, RRTransaction::PacketSize);
                p->AssemblePacket(buffer);
                Manager.Decoder_.Encode(buffer, RRTransaction::PacketSize);

                // send packet
                Manager.Connection.Send(buffer, RRTransaction::PacketSize, TimeoutManager::Instance().GetNetTimeout());
*/
                // delete packet
                Manager.PQ.Remove(p, false);
            }
            Sleep(0);
        }
_exit:
        return 0;
    }
    catch(...)
    {
//      RRListener::Instance().PostMessage(...);
        return -1;
    }
}
////////////////////////////////////////////////////////////////////////////////////////
// class RRReceiver
// ----- ----------
RRNetManager::RRReceiver::RRReceiver(RRNetManager& _manager)
            : Manager(_manager)
{
}

RRNetManager::RRReceiver::~RRReceiver()
{
}

int RRNetManager::RRReceiver::Run()
{
    try
    {
        //
        const ushort _buffer_size_ = 4096;
        //
        STACK_BUFFER(_buffer_size_, byte)

        for(;;)
        {
            if(ShouldTerminate())
            {
                break;
            }

            uint count = Manager.Connection.Receive(buffer, _buffer_size_, TimeoutManager::Instance().GetReadPolling());

            if(count == 0)
            {
                continue;
            }
            
//            Synchronization::Guard<_Mutex> guard(Mutex);

            Sleep(0);
        }
        return 0;
    }
    catch(...)
    {
        return -1;
    }
}
////////////////////////////////////////////////////////////////////////////////////////
// class RRNetManager
// ----- ------------
RRNetManager::RRNetManager()
            : ObjectRef<>(1),
              Allocator(sizeof(RRTransaction::Packet), 64, 8),
              PQ(KeyExtractor, Comparator),
              Sender(*this),
              Receiver(*this)
{
    InitMemory(&Key, sizeof(Key));
}

RRNetManager::RRNetManager(const IPv4Address& _address)
            : ObjectRef<>(1),
              Connection(_address),
              Allocator(sizeof(RRTransaction::Packet), 64, 8),
              PQ(KeyExtractor, Comparator),
              Sender(*this),
              Receiver(*this)
{
    InitMemory(&Key, sizeof(Key));
}

RRNetManager::~RRNetManager()
{
}

void RRNetManager::Connect()
{
    try
    {
        // setup connection
        Connection.Connect();
        Connection.SetBufferSize();

        // setup key
        uint ip = IsClientSide() ? Connection.GetLocalAddress().GetIPv4Address() : Connection.GetRemoteAddress().GetIPv4Address();
        HexToStr(reinterpret_cast<byte*>(&ip), 4, reinterpret_cast<byte*>(&Key));
        Decoder_.SetupKey(Key);

        // start helpers
        Sender.Start();
        Receiver.Start();
    }
    catch(...)
    {
    }
}

void RRNetManager::QueuePacket(const RRTransaction::Packet* _packet)
{
    if(_packet == null)
    {
        return;
    }
    //
    Mutex.Acquire();
    PQ.Insert(const_cast<RRTransaction::Packet*>(_packet));
    Mutex.Release();
    STrigger.Trigger();
}
////////////////////////////////////////////////////////////////////////////////////////
__END_RRT_NAMESPACE__
__END_NAMESPACE__
