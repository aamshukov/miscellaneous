////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __SYNCHRONIZATION_INL__
#define __SYNCHRONIZATION_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
namespace Synchronization
{
#ifndef __NO_THREADS__
////////////////////////////////////////////////////////////////////////////////////////
// class IProtocol
// ----- ---------
template <typename _Dummy>
Synchronization::IProtocol<_Dummy>::IProtocol(uint _timeout) : Timeout(_timeout)
{
}

template <typename _Dummy>
uint Synchronization::IProtocol<_Dummy>::GetTimeout() const
{
    return Timeout;
}
////////////////////////////////////////////////////////////////////////////////////////
// class Base
// ----- ----
template <typename _Dummy>
Synchronization::Base<_Dummy>::Base() : Handle(0)
{
}

template <typename _Dummy>
Synchronization::Base<_Dummy>::~Base()
{
}

template <typename _Dummy>
__INLINE_TEMPLATE__ Synchronization::Base<_Dummy>::operator HANDLE () const
{
    return Handle;
}

template <typename _Dummy>
__INLINE_TEMPLATE__ HANDLE Synchronization::Base<_Dummy>::GetInstance() const
{
    return Handle;
}

template <typename _Dummy>
__INLINE_TEMPLATE__ bool Synchronization::Base<_Dummy>::Close()
{
    bool rc = true;

    if(Handle != 0)
    {
        rc = ::CloseHandle(Handle) > 0, Handle = 0;
    }

    return rc;
}
////////////////////////////////////////////////////////////////////////////////////////
// class ThreadMutex
// ----- -----------
template <typename _Dummy>
Synchronization::ThreadMutex<_Dummy>::ThreadMutex(const tchar*, uint _timeout) : IProtocol<>(_timeout)
{
    ::InitializeCriticalSection(&CS);
    Valid = true;
}

template <typename _Dummy>
Synchronization::ThreadMutex<_Dummy>::~ThreadMutex()
{
    Destroy();
}

template <typename _Dummy>
__INLINE_TEMPLATE__ const CRITICAL_SECTION& Synchronization::ThreadMutex<_Dummy>::GetInstance() const
{
    return CS;
}

template <typename _Dummy>
__INLINE_TEMPLATE__ Synchronization::ThreadMutex<_Dummy>::operator CRITICAL_SECTION() const
{
    return CS;
}

template <typename _Dummy>
__INLINE_TEMPLATE__ Synchronization::ThreadMutex<_Dummy>::operator CRITICAL_SECTION* () const
{
    return const_cast<CRITICAL_SECTION*>(&CS);
}

template <typename _Dummy>
__INLINE_TEMPLATE__ bool Synchronization::ThreadMutex<_Dummy>::Acquire(uint)
{
    _xassert(X, Valid, false, X::InvalidArg);
    ::EnterCriticalSection(&CS);
    return true;
}

template <typename _Dummy>
__INLINE_TEMPLATE__ bool Synchronization::ThreadMutex<_Dummy>::TryAcquire()
{
#if (_WIN32_WINNT >= 0x0400)
    return ::TryEnterCriticalSection(&CS) > 0;
#else
    return false;
#endif
}

template <typename _Dummy>
__INLINE_TEMPLATE__ bool Synchronization::ThreadMutex<_Dummy>::Release()
{
    _xassert(X, Valid, false, X::InvalidArg);
    ::LeaveCriticalSection(&CS);
    return true;
}

template <typename _Dummy>
__INLINE_TEMPLATE__ bool Synchronization::ThreadMutex<_Dummy>::Destroy()
{
    if(Valid)
    {
        ::DeleteCriticalSection(&CS);
    
        Valid = false;
    }
    return true;
}
////////////////////////////////////////////////////////////////////////////////////////
// class NullThreadMutex
// ----- ---------------
template <typename _Dummy>
Synchronization::NullThreadMutex<_Dummy>::NullThreadMutex(const tchar*, uint) : Valid(true)
{
}

template <typename _Dummy>
Synchronization::NullThreadMutex<_Dummy>::~NullThreadMutex()
{
}

template <typename _Dummy>
__INLINE_TEMPLATE__ const CRITICAL_SECTION& Synchronization::NullThreadMutex<_Dummy>::GetInstance() const
{
    return CS;
}

template <typename _Dummy>
__INLINE_TEMPLATE__ Synchronization::NullThreadMutex<_Dummy>::operator CRITICAL_SECTION() const
{
    return CS;
}

template <typename _Dummy>
__INLINE_TEMPLATE__ Synchronization::NullThreadMutex<_Dummy>::operator CRITICAL_SECTION* () const
{
    return const_cast<CRITICAL_SECTION*>(&CS);
}

template <typename _Dummy>
__INLINE_TEMPLATE__ bool Synchronization::NullThreadMutex<_Dummy>::Acquire(uint)
{
    return false;
}

template <typename _Dummy>
__INLINE_TEMPLATE__ bool Synchronization::NullThreadMutex<_Dummy>::TryAcquire()
{
    return false;
}

template <typename _Dummy>
__INLINE_TEMPLATE__ bool Synchronization::NullThreadMutex<_Dummy>::Release()
{
    return false;
}

template <typename _Dummy>
__INLINE_TEMPLATE__ bool Synchronization::NullThreadMutex<_Dummy>::Destroy()
{
    return false;
}
////////////////////////////////////////////////////////////////////////////////////////
// class ProcessMutex
// ----- ------------
template <typename _Dummy>
Synchronization::ProcessMutex<_Dummy>::ProcessMutex(const tchar* _name, uint _timeout, SECURITY_ATTRIBUTES* _sa) : IProtocol<>(_timeout)
{
    Handle = ::CreateMutex(_sa, false, _name);
    _xassertv(X, Handle != 0, X::InvalidArg);
}

template <typename _Dummy>
Synchronization::ProcessMutex<_Dummy>::ProcessMutex(const tchar* _name, bool _inherit, uint _timeout, uint _access) : IProtocol<>(_timeout)
{
    Handle = ::OpenMutex(_access, _inherit, _name);
    _xassertv(X, Handle != 0, X::InvalidArg);
}

template <typename _Dummy>
Synchronization::ProcessMutex<_Dummy>::ProcessMutex(HANDLE _handle, uint _timeout) : IProtocol<>(_timeout)
{
    ::DuplicateHandle(::GetCurrentProcess(), _handle, ::GetCurrentProcess(), &Handle, 0, false, DUPLICATE_SAME_ACCESS);
    _xassertv(X, Handle != 0, X::InvalidArg);
}

template <typename _Dummy>
__INLINE_TEMPLATE__ bool Synchronization::ProcessMutex<_Dummy>::Acquire(uint _timeout)
{
    _xassert(X, Handle != 0, false, X::InvalidArg);

    ulong rc = ::WaitForSingleObject(Handle, INFINITE);

    if(rc != WAIT_OBJECT_0 && rc != WAIT_ABANDONED)
    {
        return false;
    }
    return true;
}

template <typename _Dummy>
__INLINE_TEMPLATE__ bool Synchronization::ProcessMutex<_Dummy>::TryAcquire()
{
    _xassert(X, Handle != 0, false, X::InvalidArg);

    ulong rc = ::WaitForSingleObject(Handle, 0);

    if(rc != WAIT_OBJECT_0 && rc != WAIT_ABANDONED)
    {
        return false;
    }
    return true;
}

template <typename _Dummy>
__INLINE_TEMPLATE__ bool Synchronization::ProcessMutex<_Dummy>::Release()
{
    _xassert(X, Handle != 0, false, X::InvalidArg);
    return ::ReleaseMutex(Handle) > 0;
}

template <typename _Dummy>
__INLINE_TEMPLATE__ bool Synchronization::ProcessMutex<_Dummy>::Destroy()
{
    return Base<_Dummy>::Close();
}
////////////////////////////////////////////////////////////////////////////////////////
// class NullProcessMutex
// ----- ----------------
template <typename _Dummy>
Synchronization::NullProcessMutex<_Dummy>::NullProcessMutex(const tchar*, uint, SECURITY_ATTRIBUTES*)
{
}

template <typename _Dummy>
Synchronization::NullProcessMutex<_Dummy>::NullProcessMutex(const tchar*, bool, uint, uint)
{
}

template <typename _Dummy>
Synchronization::NullProcessMutex<_Dummy>::NullProcessMutex(HANDLE, uint)
{
}

template <typename _Dummy>
__INLINE_TEMPLATE__ bool Synchronization::NullProcessMutex<_Dummy>::Acquire(uint)
{
    return false;
}

template <typename _Dummy>
__INLINE_TEMPLATE__ bool Synchronization::NullProcessMutex<_Dummy>::TryAcquire()
{
    return false;
}

template <typename _Dummy>
__INLINE_TEMPLATE__ bool Synchronization::NullProcessMutex<_Dummy>::Release()
{
    return false;
}

template <typename _Dummy>
__INLINE_TEMPLATE__ bool Synchronization::NullProcessMutex<_Dummy>::Destroy()
{
    return false;
}
////////////////////////////////////////////////////////////////////////////////////////
// class Semaphore
// ----- ---------
template <typename _Dummy>
Synchronization::Semaphore<_Dummy>::Semaphore(int _count, int _maxcount, const tchar* _name, uint _timeout, SECURITY_ATTRIBUTES* _sa) : IProtocol<>(_timeout)
{
    Handle = ::CreateSemaphore(_sa, _count, _maxcount, _name);
    _xassertv(X, Handle != 0, X::InvalidArg);
}

template <typename _Dummy>
Synchronization::Semaphore<_Dummy>::Semaphore(const tchar* _name, bool _inherit, uint _timeout, uint _access) : IProtocol<>(_timeout)
{
    Handle = ::OpenSemaphore(_access, _inherit, _name);
    _xassertv(X, Handle != 0, X::InvalidArg);
}

template <typename _Dummy>
Synchronization::Semaphore<_Dummy>::Semaphore(HANDLE _handle, uint _timeout) : IProtocol<>(_timeout)
{
    ::DuplicateHandle(::GetCurrentProcess(), _handle, ::GetCurrentProcess(), &Handle, 0, false, DUPLICATE_SAME_ACCESS);
    _xassertv(X, Handle != 0, X::InvalidArg);
}

template <typename _Dummy>
__INLINE_TEMPLATE__ bool Synchronization::Semaphore<_Dummy>::Acquire(uint _timeout)
{
    _xassert(X, Handle != 0, false, X::InvalidArg);

    ulong rc = ::WaitForSingleObject(Handle, min(_timeout, Timeout));

    if(rc != WAIT_OBJECT_0 && rc != WAIT_ABANDONED)
    {
        return false;
    }
    return true;
}

template <typename _Dummy>
__INLINE_TEMPLATE__ bool Synchronization::Semaphore<_Dummy>::TryAcquire()
{
    _xassert(X, Handle != 0, false, X::InvalidArg);

    ulong rc = ::WaitForSingleObject(Handle, 0);

    if(rc != WAIT_OBJECT_0 && rc != WAIT_ABANDONED)
    {
        return false;
    }
    return true;
}

template <typename _Dummy>
__INLINE_TEMPLATE__ bool Synchronization::Semaphore<_Dummy>::Release()
{
    _xassert(X, Handle != 0, false, X::InvalidArg);
    return ::ReleaseSemaphore(Handle, 1, 0) > 0;
}

template <typename _Dummy>
__INLINE_TEMPLATE__ bool Synchronization::Semaphore<_Dummy>::Destroy()
{
    return Base<_Dummy>::Close();
}
////////////////////////////////////////////////////////////////////////////////////////
// class NullSemaphore
// ----- -------------
template <typename _Dummy>
Synchronization::NullSemaphore<_Dummy>::NullSemaphore(int, int, const tchar*, uint, SECURITY_ATTRIBUTES*)
{
}

template <typename _Dummy>
Synchronization::NullSemaphore<_Dummy>::NullSemaphore(const tchar*, bool, uint, uint)
{
}

template <typename _Dummy>
Synchronization::NullSemaphore<_Dummy>::NullSemaphore(HANDLE, uint)
{
}

template <typename _Dummy>
__INLINE_TEMPLATE__ bool Synchronization::NullSemaphore<_Dummy>::Acquire(uint)
{
    return false;
}

template <typename _Dummy>
__INLINE_TEMPLATE__ bool Synchronization::NullSemaphore<_Dummy>::TryAcquire()
{
    return false;
}

template <typename _Dummy>
__INLINE_TEMPLATE__ bool Synchronization::NullSemaphore<_Dummy>::Release()
{
    return false;
}

template <typename _Dummy>
__INLINE_TEMPLATE__ bool Synchronization::NullSemaphore<_Dummy>::Destroy()
{
    return false;
}
////////////////////////////////////////////////////////////////////////////////////////
// class Event
// ----- -----
template <typename _Dummy>
Synchronization::Event<_Dummy>::Event(bool _manual_reset, bool _initial_state, const tchar* _name, uint _timeout, SECURITY_ATTRIBUTES* _sa) : Timeout(_timeout)
{
    Handle = ::CreateEvent(_sa, _manual_reset, _initial_state, _name);
    _xassertv(X, Handle != 0, X::InvalidArg);
}

template <typename _Dummy>
Synchronization::Event<_Dummy>::Event(const tchar* _name, bool _inherit, uint _timeout, uint _access) : Timeout(_timeout)
{
    Handle = ::OpenEvent(_access, _inherit, _name);
    _xassertv(X, Handle != 0, X::InvalidArg);
} 

template <typename _Dummy>Synchronization::Event<_Dummy>::Event(HANDLE _handle, uint _timeout) : Timeout(_timeout)
{
    ::DuplicateHandle(::GetCurrentProcess(), _handle, ::GetCurrentProcess(), &Handle, 0, false, DUPLICATE_SAME_ACCESS);
    _xassertv(X, Handle != 0, X::InvalidArg);
}

template <typename _Dummy>
__INLINE_TEMPLATE__ uint Synchronization::Event<_Dummy>::GetTimeout() const
{
    return Timeout;
}

template <typename _Dummy>
__INLINE_TEMPLATE__ bool Synchronization::Event<_Dummy>::Set()
{
    _xassert(X, Handle != 0, false, X::InvalidArg);
    return ::SetEvent(Handle) > 0;
}

template <typename _Dummy>
__INLINE_TEMPLATE__ bool Synchronization::Event<_Dummy>::Reset()
{
    _xassert(X, Handle != 0, false, X::InvalidArg);
    return ::ResetEvent(Handle) > 0;
}

template <typename _Dummy>
__INLINE_TEMPLATE__ bool Synchronization::Event<_Dummy>::Pulse()
{
    _xassert(X, Handle != 0, false, X::InvalidArg);
    return ::PulseEvent(Handle) > 0;
}

template <typename _Dummy>
__INLINE_TEMPLATE__ bool Synchronization::Event<_Dummy>::Wait(uint _timeout)
{
    _xassert(X, Handle != 0, false, X::InvalidArg);

    ulong rc = ::WaitForSingleObject(Handle, Timeout);

    if(rc != WAIT_OBJECT_0)
    {
        return false;
    }

    return true;
}

template <typename _Dummy>
__INLINE_TEMPLATE__ bool Synchronization::Event<_Dummy>::Destroy()
{
    return Base<_Dummy>::Close();
}
////////////////////////////////////////////////////////////////////////////////////////
// class NullEvent
// ----- ---------
template <typename _Dummy>
Synchronization::NullEvent<_Dummy>::NullEvent(bool, bool, const tchar*, uint, SECURITY_ATTRIBUTES*)
{
}

template <typename _Dummy>
Synchronization::NullEvent<_Dummy>::NullEvent(const tchar*, bool, uint, uint)
{
} 

template <typename _Dummy>Synchronization::NullEvent<_Dummy>::NullEvent(HANDLE, uint)
{
}

template <typename _Dummy>
__INLINE_TEMPLATE__ bool Synchronization::NullEvent<_Dummy>::Set()
{
    return false;
}

template <typename _Dummy>
__INLINE_TEMPLATE__ bool Synchronization::NullEvent<_Dummy>::Reset()
{
    return false;
}

template <typename _Dummy>
__INLINE_TEMPLATE__ bool Synchronization::NullEvent<_Dummy>::Pulse()
{
    return false;
}

template <typename _Dummy>
__INLINE_TEMPLATE__ bool Synchronization::NullEvent<_Dummy>::Wait(uint)
{
    return false;
}

template <typename _Dummy>
__INLINE_TEMPLATE__ bool Synchronization::NullEvent<_Dummy>::Destroy()
{
    return false;
}
////////////////////////////////////////////////////////////////////////////////////////
// class MutexAdapter
// ----- ------------
template <typename _Mutex> Synchronization::MutexAdapter<_Mutex>::MutexAdapter(const _Mutex& _mutex) : Mutex(const_cast<_Mutex&>(_mutex))
{
}

template <typename _Mutex> Synchronization::MutexAdapter<_Mutex>::~MutexAdapter()
{
    Destroy();
}

template <typename _Mutex> __INLINE_TEMPLATE__ const _Mutex& Synchronization::MutexAdapter<_Mutex>::GetInstance() const
{
    return Object;
}

template <typename _Mutex> __INLINE_TEMPLATE__ bool Synchronization::MutexAdapter<_Mutex>::Acquire(uint _timeout)
{
    return Mutex.Acquire(_timeout);
}

template <typename _Mutex> __INLINE_TEMPLATE__ bool Synchronization::MutexAdapter<_Mutex>::TryAcquire()
{
    return Mutex.TryAcquire();
}

template <typename _Mutex> __INLINE_TEMPLATE__ bool Synchronization::MutexAdapter<_Mutex>::Release()
{
    return Mutex.Release();
}

template <typename _Mutex> __INLINE_TEMPLATE__ bool Synchronization::MutexAdapter<_Mutex>::Destroy()
{
    return Mutex.Destroy();
}
////////////////////////////////////////////////////////////////////////////////////////
// class ReadWriteMutex
// ----- --------------
template <typename _Mutex> Synchronization::ReadWriteMutex<_Mutex>::ReadWriteMutex(const tchar* _name, uint _timeout) : OkToReadGuard(false, false), OkToWriteGuard(false, false), MutexGuard(_name), Timeout(_timeout)
{
    ActiveReaderCount  = 0;
    ActiveWriterCount  = 0;
    WaitingReaderCount = 0;
    WaitingWriterCount = 0;
}

template <typename _Mutex> Synchronization::ReadWriteMutex<_Mutex>::~ReadWriteMutex()
{
    Destroy();
}

template <typename _Mutex> uint Synchronization::ReadWriteMutex<_Mutex>::GetTimeout() const
{
    return Timeout;
}

template <typename _Mutex> bool Synchronization::ReadWriteMutex<_Mutex>::AcquireRead(uint _timeout)
{
    if(MutexGuard.Acquire())
    {
        while(ActiveWriterCount+WaitingWriterCount > 0)
        {
            // if any writers - wait
            ++WaitingReaderCount;

            MutexGuard.Release();
            OkToReadGuard.Wait();
            MutexGuard.Acquire(_timeout);

            --WaitingReaderCount;
        }

        ++ActiveReaderCount;

        MutexGuard.Release();
        return true;
    }

    return false;
}

template <typename _Mutex> bool Synchronization::ReadWriteMutex<_Mutex>::AcquireWrite(uint _timeout)
{
    if(MutexGuard.Acquire())
    {
        while(ActiveWriterCount+ActiveReaderCount > 0)
        {
            // if any writer or readers
            ++WaitingWriterCount;

            MutexGuard.Release();
            OkToWriteGuard.Wait();
            MutexGuard.Acquire(_timeout);

            --WaitingWriterCount;
        }

        ++ActiveWriterCount;

        MutexGuard.Release();
        return true;
    }

    return false;
}

template <typename _Mutex> bool Synchronization::ReadWriteMutex<_Mutex>::ReleaseRead()
{
    if(MutexGuard.Acquire())
    {
        // if no other readers still active, wake up writer
        if(--ActiveReaderCount == 0 && WaitingWriterCount > 0)
        {
            OkToWriteGuard.Set();
        }

        MutexGuard.Release();
        return true;
    }

    return false;
}

template <typename _Mutex> bool Synchronization::ReadWriteMutex<_Mutex>::ReleaseWrite()
{
    if(MutexGuard.Acquire())
    {
        --ActiveWriterCount;

        if(WaitingWriterCount > 0)
        {
            // give priority to other writer
            OkToWriteGuard.Set();
        }
        else if(WaitingReaderCount > 0)
        {
            OkToReadGuard.Set();
        }

        MutexGuard.Release();
        return true;
    }

    return false;
}

template <typename _Mutex> bool Synchronization::ReadWriteMutex<_Mutex>::Destroy()
{
    MutexGuard.Acquire();

    ActiveReaderCount  = 0;
    ActiveWriterCount  = 0;
    WaitingReaderCount = 0;
    WaitingWriterCount = 0;

    MutexGuard.Release();

    OkToReadGuard.Destroy();
    OkToWriteGuard.Destroy();

    MutexGuard.Destroy();
    return true;
}
////////////////////////////////////////////////////////////////////////////////////////
// class Lock
// ----- ----
template <typename _Dummy>
Synchronization::Lock<_Dummy>::Lock()
{
}

template <typename _Dummy>
Synchronization::Lock<_Dummy>::~Lock()
{
}
////////////////////////////////////////////////////////////////////////////////////////
// class LockAdapter
// ----- -----------
template <typename _Mutex, typename _Dummy>
Synchronization::LockAdapter<_Mutex, _Dummy>::LockAdapter(const _Mutex& _mutex) : Mutex(const_cast<_Mutex&>(_mutex))
{
}

template <typename _Mutex, typename _Dummy>
Synchronization::LockAdapter<_Mutex, _Dummy>::~LockAdapter()
{
}

template <typename _Mutex, typename _Dummy>
const _Mutex& Synchronization::LockAdapter<_Mutex, _Dummy>::GetInstance() const
{
    return Mutex;
}

template <typename _Mutex, typename _Dummy>
__INLINE_TEMPLATE__ bool Synchronization::LockAdapter<_Mutex, _Dummy>::Acquire(uint _timeout)
{
    return Mutex.Acquire(_timeout);
}

template <typename _Mutex, typename _Dummy>
__INLINE_TEMPLATE__ bool Synchronization::LockAdapter<_Mutex, _Dummy>::TryAcquire()
{
    return Mutex.TryAcquire();
}

template <typename _Mutex, typename _Dummy>
__INLINE_TEMPLATE__ bool Synchronization::LockAdapter<_Mutex, _Dummy>::Release()
{
    return Mutex.Release();
}

template <typename _Mutex, typename _Dummy>
__INLINE_TEMPLATE__ bool Synchronization::LockAdapter<_Mutex, _Dummy>::Destroy()
{
    return Mutex.Destroy();
}
////////////////////////////////////////////////////////////////////////////////////////
// class LockRWAdapter
// ----- -------------
template <typename _Mutex, typename _Dummy>
Synchronization::LockRWAdapter<_Mutex, _Dummy>::LockRWAdapter(const ReadWriteMutex<_Mutex>& _mutex) : Mutex(const_cast<ReadWriteMutex<_Mutex>&>(_mutex))
{
}

template <typename _Mutex, typename _Dummy>
Synchronization::LockRWAdapter<_Mutex, _Dummy>::~LockRWAdapter()
{
}

template <typename _Mutex, typename _Dummy>
const _Mutex& Synchronization::LockRWAdapter<_Mutex, _Dummy>::GetInstance() const
{
    return Mutex;
}

template <typename _Mutex, typename _Dummy>
__INLINE_TEMPLATE__ bool Synchronization::LockRWAdapter<_Mutex, _Dummy>::Acquire(uint)
{
    return true;
}

template <typename _Mutex, typename _Dummy>
__INLINE_TEMPLATE__ bool Synchronization::LockRWAdapter<_Mutex, _Dummy>::TryAcquire()
{
    return true;
}

template <typename _Mutex, typename _Dummy>
__INLINE_TEMPLATE__ bool Synchronization::LockRWAdapter<_Mutex, _Dummy>::Release()
{
    return true;
}

template <typename _Mutex, typename _Dummy>
__INLINE_TEMPLATE__ bool Synchronization::LockRWAdapter<_Mutex, _Dummy>::AcquireRead(uint _timeout)
{
    return Mutex.AcquireRead(_timeout);
}

template <typename _Mutex, typename _Dummy>
__INLINE_TEMPLATE__ bool Synchronization::LockRWAdapter<_Mutex, _Dummy>::AcquireWrite(uint _timeout)
{
    return Mutex.AcquireWrite(_timeout);
}

template <typename _Mutex, typename _Dummy>
__INLINE_TEMPLATE__ bool Synchronization::LockRWAdapter<_Mutex, _Dummy>::ReleaseRead()
{
    return Mutex.ReleaseRead();
}

template <typename _Mutex, typename _Dummy>
__INLINE_TEMPLATE__ bool Synchronization::LockRWAdapter<_Mutex, _Dummy>::ReleaseWrite()
{
    return Mutex.ReleaseWrite();
}

template <typename _Mutex, typename _Dummy>
__INLINE_TEMPLATE__ bool Synchronization::LockRWAdapter<_Mutex, _Dummy>::Destroy()
{
    return Mutex.Destroy();
}
////////////////////////////////////////////////////////////////////////////////////////
// class Guard
// ----- -----
template <typename _Lock>
Synchronization::Guard<_Lock>::Guard(const _Lock& _lock, bool _block) : Lock(const_cast<_Lock&>(_lock))
{
    Lock.Acquire();
}

template <typename _Lock>
Synchronization::Guard<_Lock>::~Guard()
{
    Lock.Release();
}

template <typename _Lock>
const _Lock& Synchronization::Guard<_Lock>::GetInstance() const
{
    return Lock;
}
////////////////////////////////////////////////////////////////////////////////////////
// class ReadGuard
// ----- ---------
template <typename _Lock>
Synchronization::ReadGuard<_Lock>::ReadGuard(const _Lock& _lock, bool _block) : Lock(const_cast<_Lock&>(_lock))
{
    Lock.AcquireRead();
}

template <typename _Lock>
Synchronization::ReadGuard<_Lock>::~ReadGuard()
{
    Lock.ReleaseRead();
}
////////////////////////////////////////////////////////////////////////////////////////
// class WriteGuard
// ----- ----------
template <typename _Lock>
Synchronization::WriteGuard<_Lock>::WriteGuard(const _Lock& _lock, bool _block) : Lock(const_cast<_Lock&>(_lock))
{
    Lock.AcquireWrite();
}

template <typename _Lock>
Synchronization::WriteGuard<_Lock>::~WriteGuard()
{
    Lock.ReleaseWrite();
}
////////////////////////////////////////////////////////////////////////////////////////
#endif // __NO_THREADS__
} // namespace Synchronization
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __SYNCHRONIZATION_INL__
