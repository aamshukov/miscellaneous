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

#ifndef __RR_DISPATCHER_INC__
#   include <RRDispatcher.inc>
#endif

__BEGIN_NAMESPACE__
__BEGIN_RRT_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class DEntry
// ----- ------
RRDispatcher::DEntry::DEntry() : Transaction(null), Manager(null)
{
}

RRDispatcher::DEntry::DEntry(const RRTransaction* _transaction, const RRNetManager* _manager)
            : Transaction(_transaction), Manager(_manager)
{
}

RRDispatcher::DEntry::DEntry(const DEntry& _other)
{
    if(this != &_other)
    {
        Transaction = _other.Transaction;
        Manager     = _other.Manager;
    }
}

RRDispatcher::DEntry& RRDispatcher::DEntry::operator = (const RRDispatcher::DEntry& _other)
{
    if(this != &_other)
    {
        Transaction = _other.Transaction;
        Manager     = _other.Manager;
    }
    return *this;
}
////////////////////////////////////////////////////////////////////////////////////////
// class RRDispatcher
// ----- ------------
RRDispatcher::RRDispatcher()
            : Interleave(8),
              DAllocator(sizeof(RRDispatcher::DEntry), 32, 8),
              OutQueue(DKeyExtractor, DComparator),
              InQueue(PKeyExtractor, PComparator),
              TransQueue(TKeyExtractor, TComparator),
              Managers(4, 2),
              NetManagers(NKeyExtractor, NComparator),
              MaxConnections(1024)
{
    Sender.Start();
    Receiver.Start();
}

RRDispatcher::~RRDispatcher()
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    //
    for(uint i = 0; i < Managers.GetCount(); i++)
    {
        if(Managers[i] != null)
        {
            delete Managers[i], Managers[i] == null;
        }
    }
    
    if(Sender.GetState() == Thread::Running)
    {
        if(Sender.TerminateAndWait(TimeoutManager::Instance().GetThreadTL()) != WAIT_OBJECT_0)
        {
            ::TerminateThread(Sender, -1);
        }
    }

    if(Receiver.GetState() == Thread::Running)
    {
        if(Receiver.TerminateAndWait(TimeoutManager::Instance().GetThreadTL()) != WAIT_OBJECT_0)
        {
            ::TerminateThread(Receiver, -1);
        }
    }
}

void RRDispatcher::Register(RRManager* _manager)
{
    // takes ownership
    if(_manager != null)
    {
        Synchronization::Guard<_Mutex> guard(Mutex);

        // find free slot
        for(uint i = 0; i < Managers.GetCount(); i++)
        {
            if(Managers[i] == null)
            {
                Managers[i] = _manager;
                return;
            }
        }
        Managers.Resize(Managers.GetCount()+2);
        Managers[i] = _manager;
    }
}

void RRDispatcher::Unregister(RRManager* _manager)
{
    // takes ownership
    if(_manager != null)
    {
        Synchronization::Guard<_Mutex> guard(Mutex);

        // find entry
        for(uint i = 0; i < Managers.GetCount(); i++)
        {
            if(Managers[i] == _manager)
            {
                delete Managers[i], Managers[i] == null;
                return;
            }
        }
    }
}

void RRDispatcher::QueueTransaction(const RRTransaction* _transaction, const RRNetManager* _manager)
{
    // put transactions to the queue
    // sender will split them to packets and feed the net manager
    if(_transaction == null || _manager == null)
    {
        return;
    }
    //
    SMutex.Acquire();
    void* p = DAllocator.Allocate();
    OutQueue.LinkTail(new (p) RRDispatcher::DEntry(_transaction, _manager));
    SMutex.Release();
    STrigger.Trigger();
}

void RRDispatcher::QueuePacket(const RRTransaction::Packet* _packet)
{
    // put packet to the queue
    // receiver will assemble a transaction
    if(_packet == null)
    {
        return;
    }
    //
    RMutex.Acquire();
    InQueue.LinkTail(const_cast<RRTransaction::Packet*>(_packet));
    RMutex.Release();
    RTrigger.Trigger();
}

void RRDispatcher::RegisterNetManager(RRNetManager* _manager)
{
    if(NetManagers.GetCount() >= MaxConnections)
    {
        //?? process reject connection
        return;
    }

    if(_manager != null)
    {
        NetManagers.LinkHead(_manager);
        Listener::Instance().PostMessage(WM_USER+0x43, 0, NetManagers.GetCount());
    }
}

void RRDispatcher::UnregisterNetManager(RRNetManager* _manager)
{
    if(_manager != null)
    {
        NetManagers.Unlink(_manager);
    }
}

void RRDispatcher::CleanUp()
{
    Sender.Suspend();
    Receiver.Suspend();
    //
    Synchronization::Guard<_Mutex> guard(Mutex);
    //
    DAllocator.Compact();
    //
    Sender.Resume();
    Receiver.Resume();
}
////////////////////////////////////////////////////////////////////////////////////////
// class DSender
// ----- -------
RRDispatcher::DSender::DSender()
{
}

RRDispatcher::DSender::~DSender()
{
}

int RRDispatcher::DSender::Run()
{
    try
    {
        RRDispatcher& dispatcher = RRDispatcher::Instance();

        for(;;)
        {
            if(ShouldTerminate())
            {
                break;
            }

            ushort interleave = dispatcher.GetInterleave();

            /////////////////////////////////////////////////////////////////////////////////////
            #define PROCESS_TRANSACTION(_priority)                                              \
                if(ShouldTerminate())                                                           \
                {                                                                               \
                    goto _exit;                                                                 \
                }                                                                               \
                                                                                                \
                RRTransaction* t = const_cast<RRTransaction*>(iter.Current().Transaction);      \
                RRNetManager*  m = const_cast<RRNetManager*>(iter.Current().Manager);           \
                                                                                                \
                if(t == null || m == null)                                                      \
                {                                                                               \
                    continue;                                                                   \
                }                                                                               \
                                                                                                \
                if(t->GetPriority() == _priority)                                               \
                {                                                                               \
                    Synchronization::Guard<_Mutex> guard(dispatcher.SMutex);                    \
                    RRTransaction::Packet* packet = RRMemManager::Instance().ConstructPacket(); \
                                                                                                \
                    if(t->PopPacket(packet))                                                    \
                    {                                                                           \
                        DEntry* e = (DEntry*)iter.GetCurrentNode();                             \
                        iter++;                                                                 \
                        dispatcher.OutQueue.Unlink(e, false);                                   \
                        e->~DEntry();                                                           \
                        dispatcher.DAllocator.Deallocate(e);                                    \
                    }                                                                           \
                                                                                                \
                    m->QueuePacket(packet);                                                     \
                }                                                                               \
            /////////////////////////////////////////////////////////////////////////////////////

            if(!dispatcher.STrigger.WaitEvent(TimeoutManager::Instance().GetTriggerTimeout()))
            {
                // timeout
                continue;
            }

            while(dispatcher.OutQueue.GetCount() > 0)
            {
                // phase I (process high priority transactions, ignore interleave)
                ListIterator<DEntry, uint> iter(dispatcher.OutQueue.GetHead());

                for(; iter; iter++)
                {
                    PROCESS_TRANSACTION(RRTransaction::HighPriority)
                }

                // phase II (process normal priority transactions)
                iter.Restart(dispatcher.OutQueue.GetHead());

                for(; iter; iter++)
                {
                    PROCESS_TRANSACTION(RRTransaction::NormalPriority)

                    if(interleave-- == 0)
                    {
                        break;
                    }
                }

                // phase II (process low priority transactions)
                iter.Restart(dispatcher.OutQueue.GetHead());

                for(; iter; iter++)
                {
                    PROCESS_TRANSACTION(RRTransaction::LowPriority)
                }

                Sleep(0); // release timeslice
            }

            //////////////////////////
            #undef PROCESS_TRANSACTION
            //////////////////////////
        }
_exit:
        return 0;
    }
    catch(...)
    {
        return -1;
    }
}
////////////////////////////////////////////////////////////////////////////////////////
// class DReceiver
// ----- ---------
RRDispatcher::DReceiver::DReceiver()
{
}

RRDispatcher::DReceiver::~DReceiver()
{
}

int RRDispatcher::DReceiver::Run()
{
    try
    {
        RRDispatcher& dispatcher = RRDispatcher::Instance();

        for(;;)
        {
            if(ShouldTerminate())
            {
                break;
            }

            if(!dispatcher.RTrigger.WaitEvent(TimeoutManager::Instance().GetTriggerTimeout()))
            {
                // timeout
                continue;
            }

            ListIterator<RRTransaction::Packet, uint> iter(dispatcher.InQueue.GetHead());

            for(; iter; iter++)
            {
                if(ShouldTerminate())
                {
                    goto _exit;
                }

                RRTransaction::Packet* p = (RRTransaction::Packet*)iter.GetCurrentNode();
                RRTransaction* t = (RRTransaction*)dispatcher.TransQueue.Search(p->GetTransactionID());

                // if first packet
                if(t == null)
                {
                    t = RRMemManager::Instance().ConstructTransaction();
                    dispatcher.SMutex.Acquire();
                    dispatcher.TransQueue.Insert(t);
                    dispatcher.SMutex.Release();
                }

                // assemble transaction
                if(t->PushPacket(p))
                {
                    for(ushort i = 0; i < dispatcher.Managers.GetCount(); i++)
                    {
                        dispatcher.TransQueue.Remove(t);

                        if(dispatcher.Managers[i] != null && dispatcher.Managers[i]->CanHandle(t))
                        {
                            dispatcher.Managers[i]->Process(t);
                        }
                    }
                }

                // release packet
                iter++;
                dispatcher.InQueue.Unlink(p);
                RRMemManager::Instance().DestroyPacket(p);
            }

            Sleep(0); // release timeslice
        }
_exit:
        return 0;
    }
    catch(...)
    {
        return -1;
    }
}
////////////////////////////////////////////////////////////////////////////////////////
__END_RRT_NAMESPACE__
__END_NAMESPACE__
