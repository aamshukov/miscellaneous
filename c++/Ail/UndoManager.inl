////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __UNDO_MANAGER_INL__
#define __UNDO_MANAGER_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class Command
// ----- -------
__INLINE__ void Command::GetDescription(tchar* _buffer)
{
    if(_buffer == null)
    {
        return;
    }

   _buffer[0] = 0;
}

__INLINE__ uint& Command::GetKey() const
{
    return const_cast<uint&>(Id);
}
////////////////////////////////////////////////////////////////////////////////////////
// class MacroCommand
// ----- ------------
__INLINE__ const _CommandList& MacroCommand::GetCommands() const
{
    return Commands;
}

__INLINE__ _CommandList& MacroCommand::GetCommands()
{
    return Commands;
}

__INLINE__ void MacroCommand::GetDescription(tchar* _buffer)
{
    if(_buffer == null)
    {
        return;
    }

   _buffer[0] = 0;
}

__INLINE__ void MacroCommand::AddCommand(Command* _command)
{
    Commands.LinkHead(_command);
}
////////////////////////////////////////////////////////////////////////////////////////
// class UndoManager
// ----- -----------
template <typename _List, typename _Mutex> UndoManager<_List, _Mutex>::UndoManager(int _count, const tchar* _mutex_name, uint _timeout)
    : LevelCount(_count),
      State(UndoManager::FreeState),
      Mutex(_mutex_name, _timeout),
      UndoCommands(Extractor, Comparator),
      RedoCommands(Extractor, Comparator)
{
    UndoCommands.SetState(StateObject::NoDelete);
    RedoCommands.SetState(StateObject::NoDelete);
}

template <typename _List, typename _Mutex> UndoManager<_List, _Mutex>::~UndoManager()
{
    Destroy();
}

template <typename _List, typename _Mutex> __INLINE_TEMPLATE__ int UndoManager<_List, _Mutex>::GetLevelCount() const
{
    return LevelCount;
}

template <typename _List, typename _Mutex> __INLINE_TEMPLATE__ void UndoManager<_List, _Mutex>::SetLevelCount(int _count)
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    //
    LevelCount = _count;
    Destroy();
}

template <typename _List, typename _Mutex> __INLINE_TEMPLATE__ UndoManager<_List, _Mutex>::EState UndoManager<_List, _Mutex>::GetState() const
{
    return State;
}

template <typename _List, typename _Mutex> __INLINE_TEMPLATE__ const _List& UndoManager<_List, _Mutex>::GetUndoCommands() const
{
    return UndoCommands;
}

template <typename _List, typename _Mutex> __INLINE_TEMPLATE__ _List& UndoManager<_List, _Mutex>::GetUndoCommands()
{
    return UndoCommands;
}

template <typename _List, typename _Mutex> __INLINE_TEMPLATE__ const _List& UndoManager<_List, _Mutex>::GetRedoCommands() const
{
    return RedoCommands;
}

template <typename _List, typename _Mutex> __INLINE_TEMPLATE__ _List& UndoManager<_List, _Mutex>::GetRedoCommands()
{
    return RedoCommands;
}

template <typename _List, typename _Mutex> UndoManager<_List, _Mutex>::EStack UndoManager<_List, _Mutex>::GetStack(const Command* _command) const
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    //
    ListIterator<Command, uint> iter(UndoCommands.GetHead());

    for(; iter; iter++)
    {
        if(_command == &iter.Current())
        {
            return UndoManager<_List, _Mutex>::UndoStack;
        }
    }

    iter.Restart(RedoCommands.GetHead());

    for(; iter; iter++)
    {
        if(_command == &iter.Current())
        {
            return UndoManager<_List, _Mutex>::RedoStack;
        }
    }

    return UndoManager<_List, _Mutex>::Stacks;
}

template <typename _List, typename _Mutex> void UndoManager<_List, _Mutex>::AddCommand(const Command* _command)
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    //
    if(_command == null)
    {
        // destroy stacks
        Destroy();
        return;
    }

    if(State == UndoManager::FreeState)
    {
        // put on the undo stack & destroy the redo stack
        if(UndoCommands.GetCount() == LevelCount)
        {
            UndoCommands.UnlinkTail();
        }
        UndoCommands.LinkHead(const_cast<Command*>(_command));
        Destroy(UndoManager::RedoStack);
    }
    else if(State == UndoManager::UndoState)
    {
        // put on the redo stack
        if(RedoCommands.GetCount() == LevelCount)
        {
            RedoCommands.UnlinkTail();
        }
        RedoCommands.LinkHead(const_cast<Command*>(_command));
    }
    else if(State == UndoManager::RedoState)
    {
        // put on the undo stack & DO NOT destroy the redo stack
        if(UndoCommands.GetCount() == LevelCount)
        {
            UndoCommands.UnlinkTail();
        }
        UndoCommands.LinkHead(const_cast<Command*>(_command));
    }
    else
    {
        // unknown state
        State = UndoManager::FreeState;
        return;
    }
}

template <typename _List, typename _Mutex> void UndoManager<_List, _Mutex>::RemoveCommand(UndoManager::EStack _stack)
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    //
    UndoCommands.SetState(StateObject::Delete);
    RedoCommands.SetState(StateObject::Delete);
   _stack == UndoManager::UndoStack ? UndoCommands.UnlinkHead() : RedoCommands.UnlinkHead();
    UndoCommands.SetState(StateObject::NoDelete);
    RedoCommands.SetState(StateObject::NoDelete);
}

template <typename _List, typename _Mutex> void UndoManager<_List, _Mutex>::Destroy(UndoManager::EStack _stack)
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    //
    if(_stack == UndoManager::Stacks)
    {
        // destroy undo stack
        UndoCommands.SetState(StateObject::Delete);
        UndoCommands.Destroy();
        UndoCommands.SetState(StateObject::NoDelete);

        // destroy redo stack
        RedoCommands.SetState(StateObject::Delete);
        RedoCommands.Destroy();
        RedoCommands.SetState(StateObject::NoDelete);
    }
    else if(_stack == UndoManager::UndoStack)
    {
        // destroy undo stack
        UndoCommands.SetState(StateObject::Delete);
        UndoCommands.Destroy();
        UndoCommands.SetState(StateObject::NoDelete);
    }
    else if(_stack == UndoManager::RedoStack)
    {
        // destroy redo stack
        RedoCommands.SetState(StateObject::Delete);
        RedoCommands.Destroy();
        RedoCommands.SetState(StateObject::NoDelete);
    }

    State = UndoManager::FreeState;
}

template <typename _List, typename _Mutex> bool UndoManager<_List, _Mutex>::HasUndo(int _n) const
{
    if(UndoCommands.GetCount() == 0)
    {
        return false;
    }

    Synchronization::Guard<_Mutex> guard(Mutex);
    //
    ListIterator<Command, uint> iter(UndoCommands.GetHead());

    for(; iter && _n > 0; iter++)
    {
        _n--;
    }
    return _n == 0;
}

template <typename _List, typename _Mutex> bool UndoManager<_List, _Mutex>::HasRedo(int _n) const
{
    if(RedoCommands.GetCount() == 0)
    {
        return false;
    }

    Synchronization::Guard<_Mutex> guard(Mutex);
    //
    ListIterator<Command, uint> iter(RedoCommands.GetHead());

    for(; iter && _n > 0; iter++)
    {
        _n--;
    }
    return _n == 0;
}

template <typename _List, typename _Mutex> Command* UndoManager<_List, _Mutex>::Undo(int _n)
{
    if(!HasUndo())
    {
        return 0;
    }

    Synchronization::Guard<_Mutex> guard(Mutex);
    //
    Command* command = null;
    State = UndoManager::UndoState;

    for(int i = 0; i < _n; i++)
    {
        command = (Command*)UndoCommands.GetHead();

        UndoCommands.Unlink(command);
        RedoCommands.LinkHead(command);
    
#ifndef _DEBUG
        try
#endif
        {
            if(command->Execute(Command::UndoMode) == 0)
            {
#ifdef _DEBUG
              ::MessageBox(0, "Undo Mode: Execute returned 0", "UndoManager", MB_OK|MB_ICONSTOP);
#endif
                // if fail just give up
                State = UndoManager::ErrorState;
                Destroy();
                return null;
            }
        }
#ifndef _DEBUG
        catch(...)
        {
                // if fail just give up
                State = UndoManager::ErrorState;
                Destroy();
                return null;
        }
#endif
    }

    State = UndoManager::FreeState;
    return command;
}

template <typename _List, typename _Mutex> Command* UndoManager<_List, _Mutex>::Redo(int _n)
{
    if(!HasRedo())
    {
        return 0;
    }

    Synchronization::Guard<_Mutex> guard(Mutex);
    //
    Command* command = null;
    State = UndoManager::RedoState;

    for(int i = 0; i < _n; i++)
    {
        command = (Command*)RedoCommands.GetHead();

        RedoCommands.Unlink(command);
        UndoCommands.LinkHead(command);
    
#ifndef _DEBUG
        try
#endif
        {
            if(command->Execute(Command::RedoMode) == 0)
            {
#ifdef _DEBUG
              ::MessageBox(0, "Redo Mode: Execute returned 0", "UndoManager", MB_OK|MB_ICONSTOP);
#endif
                // if fail just give up
                State = UndoManager::ErrorState;
                Destroy();
                return null;
            }
        }
#ifndef _DEBUG
        catch(...)
        {
                // if fail just give up
                State = UndoManager::ErrorState;
                Destroy();
                return null;
        }
#endif
    }

    State = UndoManager::FreeState;
    return command;
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __UNDO_MANAGER_INL__
