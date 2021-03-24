////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __SYNCHRONIZATION_H__
#define __SYNCHRONIZATION_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class Synchronization
// ----- ---------------
namespace Synchronization
{
    //
    enum ETimeout
    {
        TimeoutTry     = 0,
#ifdef __MS_WINDOWS__
        TimeoutNoLimit = INFINITE
#else
        TimeoutNoLimit = 0xFFFFFFFF
#endif
    };
#ifndef __NO_THREADS__
    //////////////////
    // class IProtocol
    // ----- ---------
    template <typename _Dummy = byte> class IProtocol
    {
        protected:
         uint           Timeout;
        protected:
         // ctor/dtor
                        IProtocol(uint = Synchronization::TimeoutNoLimit);

         // methods
         virtual bool   Acquire(uint = Synchronization::TimeoutNoLimit) = 0;
         virtual bool   TryAcquire()                                    = 0;
         virtual bool   Release()                                       = 0;
         virtual bool   Destroy()                                       = 0;
        public:
         // access
         uint           GetTimeout()  const;
    };

    /////////////
    // class Base
    // ----- ----
    template <typename _Dummy = byte> class Base
    {
        protected:
         HANDLE     Handle;
        public: 
         // ctor/dtor
                    Base();
         virtual   ~Base();

         // access
         HANDLE     GetInstance()       const;
                    operator HANDLE()   const;

         // methods
         bool       Close();
    };

    ////////////////////
    // class ThreadMutex
    // ----- -----------
    template <typename _Dummy = byte> class ThreadMutex : public IProtocol<_Dummy>
    {
        private:
         bool                       Valid;
         CRITICAL_SECTION           CS;
        private:
                                    ThreadMutex(const ThreadMutex&);
         const ThreadMutex&         operator = (const ThreadMutex&);
        public:
         // ctor/dtor
                                    ThreadMutex(const tchar* = null, uint = Synchronization::TimeoutNoLimit);
         virtual                   ~ThreadMutex();

         // access
         const CRITICAL_SECTION&    GetInstance()                   const;

                                    operator CRITICAL_SECTION  ()   const;
                                    operator CRITICAL_SECTION* ()   const;

         // methods
         bool                       Acquire(uint = Synchronization::TimeoutNoLimit);
         bool                       TryAcquire();
         bool                       Release();
         bool                       Destroy();
    };

    ////////////////////////
    // class NullThreadMutex
    // ----- ---------------
    template <typename _Dummy = byte> class NullThreadMutex : public IProtocol<_Dummy>
    {
        private:
         bool                       Valid;
         CRITICAL_SECTION           CS;
        private:
                                    NullThreadMutex(const NullThreadMutex&);
         const NullThreadMutex&     operator = (const NullThreadMutex&);
        public:
         // ctor/dtor
                                    NullThreadMutex(const tchar* = null, uint = Synchronization::TimeoutNoLimit);
         virtual                   ~NullThreadMutex();

         // access
         const CRITICAL_SECTION&    GetInstance()                   const;

                                    operator CRITICAL_SECTION  ()   const;
                                    operator CRITICAL_SECTION* ()   const;

         // methods
         bool                       Acquire(uint = Synchronization::TimeoutNoLimit);
         bool                       TryAcquire();
         bool                       Release();
         bool                       Destroy();
    };

    /////////////////////
    // class ProcessMutex
    // ----- ------------
    template <typename _Dummy = byte> class ProcessMutex : public IProtocol<_Dummy>, public Base<_Dummy>
    {
        private:
                                ProcessMutex(const ProcessMutex&);
         const ProcessMutex&    operator = (const ProcessMutex&);
        public:
         // ctor/dtor
                                ProcessMutex(const tchar* = null, uint = Synchronization::TimeoutNoLimit, SECURITY_ATTRIBUTES* = null);
                                ProcessMutex(const tchar*, bool, uint = Synchronization::TimeoutNoLimit, uint = MUTEX_ALL_ACCESS);
                                ProcessMutex(HANDLE, uint = Synchronization::TimeoutNoLimit);

         // methods
         bool                   Acquire(uint = Synchronization::TimeoutNoLimit);
         bool                   TryAcquire();
         bool                   Release();
         bool                   Destroy();
    };

    /////////////////////////
    // class NullProcessMutex
    // ----- ----------------
    template <typename _Dummy = byte> class NullProcessMutex : public IProtocol<_Dummy>, public Base<_Dummy>
    {
        private:
                                    NullProcessMutex(const NullProcessMutex&);
         const NullProcessMutex&    operator = (const NullProcessMutex&);
        public:
         // ctor/dtor
                                    NullProcessMutex(const tchar* = null, uint = Synchronization::TimeoutNoLimit, SECURITY_ATTRIBUTES* = null);
                                    NullProcessMutex(const tchar*, bool, uint = Synchronization::TimeoutNoLimit, uint = MUTEX_ALL_ACCESS);
                                    NullProcessMutex(HANDLE, uint = Synchronization::TimeoutNoLimit);

         // methods
         bool                       Acquire(uint = Synchronization::TimeoutNoLimit);
         bool                       TryAcquire();
         bool                       Release();
         bool                       Destroy();
    };

    //////////////////
    // class Semaphore
    // ----- ---------
    template <typename _Dummy = byte> class Semaphore : public IProtocol<_Dummy>, public Base<_Dummy>
    {
        private:
                            Semaphore(const Semaphore&);
         const Semaphore&   operator = (const Semaphore&);
        public:
         // ctor/dtor
                            Semaphore(int = 0, int = 0, const tchar* = null, uint = Synchronization::TimeoutNoLimit, SECURITY_ATTRIBUTES* = null);
                            Semaphore(const tchar*, bool, uint = Synchronization::TimeoutNoLimit, uint = SEMAPHORE_ALL_ACCESS);
                            Semaphore(HANDLE, uint = Synchronization::TimeoutNoLimit);

         // methods
         bool               Acquire(uint = Synchronization::TimeoutNoLimit);
         bool               TryAcquire();
         bool               Release();
         bool               Destroy();
    };

    //////////////////////
    // class NullSemaphore
    // ----- -------------
    template <typename _Dummy = byte> class NullSemaphore : public IProtocol<_Dummy>, public Base<_Dummy>
    {
        private:
                                NullSemaphore(const NullSemaphore&);
         const NullSemaphore&   operator = (const NullSemaphore&);
        public:
         // ctor/dtor
                                NullSemaphore(int = 0, int = 0, const tchar* = null, uint = Synchronization::TimeoutNoLimit, SECURITY_ATTRIBUTES* = null);
                                NullSemaphore(const tchar*, bool, uint = Synchronization::TimeoutNoLimit, uint = SEMAPHORE_ALL_ACCESS);
                                NullSemaphore(HANDLE, uint = Synchronization::TimeoutNoLimit);

         // methods
         bool                   Acquire(uint = Synchronization::TimeoutNoLimit);
         bool                   TryAcquire();
         bool                   Release();
         bool                   Destroy();
    };

    //////////////
    // class Event
    // ----- -----
    template <typename _Dummy = byte> class Event : public Base<_Dummy>
    {
        private:
         uint           Timeout;
        private:
                        Event(const Event&);
         const Event&   operator = (const Event&);
        public:
         // ctor/dtor
                        Event(bool = false, bool = false, const tchar* = null, uint = Synchronization::TimeoutNoLimit, SECURITY_ATTRIBUTES* = null);
                        Event(const tchar*, bool, uint = Synchronization::TimeoutNoLimit, uint = SEMAPHORE_ALL_ACCESS);
                        Event(HANDLE, uint = Synchronization::TimeoutNoLimit);

         // access
         uint           GetTimeout()  const;

         // methods
         bool           Set();
         bool           Reset();
         bool           Pulse();
         bool           Wait(uint = INFINITE);
         bool           Destroy();
    };

    //////////////////
    // class NullEvent
    // ----- ---------
    template <typename _Dummy = byte> class NullEvent : public Base<_Dummy>
    {
        private:
         uint               Timeout;
        private:
                            NullEvent(const NullEvent&);
         const NullEvent&   operator = (const NullEvent&);
        public:
         // ctor/dtor
                            NullEvent(bool = false, bool = false, const tchar* = null, uint = Synchronization::TimeoutNoLimit, SECURITY_ATTRIBUTES* = null);
                            NullEvent(const tchar*, bool, uint = Synchronization::TimeoutNoLimit, uint = SEMAPHORE_ALL_ACCESS);
                            NullEvent(HANDLE, uint = Synchronization::TimeoutNoLimit);

         // access
         uint               GetTimeout()  const;

         // methods
         bool               Set();
         bool               Reset();
         bool               Pulse();
         bool               Wait(uint = INFINITE);
         bool               Destroy();
    };

    /////////////////////
    // class MutexAdapter
    // ----- ------------
    template <typename _Mutex = ThreadMutex<> > class MutexAdapter
    {
        private:
        _Mutex&         Mutex;
        public:
         // ctor/dtor
                        MutexAdapter(const _Mutex&);
                       ~MutexAdapter();

         // access
         const _Mutex&  GetInstance()   const;
     
         // methods
         bool           Acquire(uint = Synchronization::TimeoutNoLimit);
         bool           TryAcquire();
         bool           Release();
         bool           Destroy();
    };

    ///////////////////////
    // class ReadWriteMutex
    // ----- --------------
    template <typename _Mutex = ThreadMutex<> > class ReadWriteMutex
    {
        // ALGORITHM:
        //  if a thread modifies the shared resource, other threads can not modify that resource (write protection)
        //  if a thread modifies the shared resource, other threads have not access to that resource (read protection)
        //  if a thread has access to the shared resource, other threads can not modify that resource (write protection)
        //  if a thread has access to the shared resource, other threads have access as well
        //  as soon as a writer begins to wait, no more readers are allowed to modify
        private:
         uint                   Timeout;

         ulong                  ActiveReaderCount;  // # of active readers
         ulong                  ActiveWriterCount;  // # of active writers

         ulong                  WaitingReaderCount; // # of waiting readers
         ulong                  WaitingWriterCount; // # of waiting writers

         Event<>                OkToReadGuard;      // ok to read
         Event<>                OkToWriteGuard;     // ok to write

        _Mutex                  MutexGuard;
        private:
                                ReadWriteMutex(const ReadWriteMutex&);
         const ReadWriteMutex&  operator = (const ReadWriteMutex&);
        public:
         // ctor/dtor
                                ReadWriteMutex(const tchar* = null, uint = Synchronization::TimeoutNoLimit);
                               ~ReadWriteMutex();
                                
         // access
         uint                   GetTimeout()          const;

         // methods
         bool                   AcquireRead(uint = Synchronization::TimeoutNoLimit);
         bool                   AcquireWrite(uint = Synchronization::TimeoutNoLimit);
         bool                   ReleaseRead();
         bool                   ReleaseWrite();
         bool                   Destroy();
    };

    /////////////
    // class Lock
    // ----- ----
    template <typename _Dummy = byte> class Lock : public IProtocol<_Dummy>
    {
        public:
         // ctor/dtor
                    Lock();
         virtual   ~Lock();
    };

    ////////////////////
    // class LockAdapter
    // ----- -----------
    template <typename _Mutex, typename _Dummy = char> class LockAdapter : public Lock<_Dummy>
    {
        private:
        _Mutex&         Mutex;
        public:
         // ctor/dtor
                        LockAdapter(const _Mutex&);
                       ~LockAdapter();

         // access
         const _Mutex&  GetInstance()   const;
     
         // methods
         bool           Acquire(uint = Synchronization::TimeoutNoLimit);
         bool           TryAcquire();
         bool           Release();
         bool           Destroy();
    };

    //////////////////////
    // class LockRWAdapter
    // ----- -------------
    template <typename _Mutex = ThreadMutex<>, typename _Dummy = char> class LockRWAdapter : public Lock<_Dummy>
    {
        private:
         ReadWriteMutex<_Mutex>&  Mutex;
        public:
         // ctor/dtor
                                  LockRWAdapter(const ReadWriteMutex<_Mutex>&);
                                 ~LockRWAdapter();

         // access
         const _Mutex&            GetInstance()   const;
     
         // methods
         bool                     Acquire(uint = Synchronization::TimeoutNoLimit);
         bool                     TryAcquire();
         bool                     Release();

         bool                     AcquireRead(uint = Synchronization::TimeoutNoLimit);
         bool                     AcquireWrite(uint = Synchronization::TimeoutNoLimit);
         bool                     ReleaseRead();
         bool                     ReleaseWrite();
         bool                     Destroy();
    };

    //////////////
    // class Guard
    // ----- -----
    template <typename _Lock> class Guard
    {
        protected:
        _Lock&          Lock;
        public:
         // ctor/dtor
                        Guard(const _Lock&, bool = true);
                       ~Guard();
         // access
         const _Lock&   GetInstance() const;
    };

    //////////////////
    // class ReadGuard
    // ----- ---------
    template <typename _Lock> class ReadGuard
    {
        protected:
        _Lock&          Lock;
        public:
         // ctor/dtor
                        ReadGuard(const _Lock&, bool = true);
                       ~ReadGuard();

         // access
         const _Lock&   GetInstance() const;
    };

    ///////////////////
    // class WriteGuard
    // ----- ----------
    template <typename _Lock> class WriteGuard
    {
        protected:
        _Lock&          Lock;
        public:
         // ctor/dtor
                        WriteGuard(const _Lock&, bool = true);
                       ~WriteGuard();

         // access
         const _Lock&   GetInstance() const;
    };

    //////////////////////////
    // class Trigger
    // ----- -------
    class __DECLSPEC__ ETrigger
    {
        private:
         Event<>    E;
        public:
         // ctor/dtor
                    ETrigger();
                   ~ETrigger();

         // protocol
         bool       WaitEvent(uint = -1);
         void       Trigger();
    };
    //////////////////////////
#else
    ////////////////////
    // class ThreadMutex
    // ----- -----------
    template <typename _Dummy = byte> class ThreadMutex
    {
    };
    ////////////////////////
    // class NullThreadMutex
    // ----- ---------------
    template <typename _Dummy = byte> class NullThreadMutex
    {
    };
#endif
} // namespace Synchronization
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __SYNCHRONIZATION_H__
