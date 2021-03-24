////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __UNDO_MANAGER_H__
#define __UNDO_MANAGER_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class Command
// ----- -------
class Command : public ListNodeBase<Command, uint>, private ObjectRef<>
{
    public:

    enum EMode
    {
        UndoMode = 0, RedoMode
    };

    public:
     // ctor/dtor
                    Command(uint = 0);
                    Command(const Command&);
     virtual       ~Command();

     Command&       operator = (const Command&);

     // access
     uint&          GetKey()        const;

     // protocol
     virtual int    Execute(Command::EMode);
     virtual void   GetDescription(tchar*);
};
////////////////////////////////////////////////////////////////////////////////////////
// struct _CommandKeyExtractor
// ------ --------------------
struct _CommandKeyExtractor
{
    const uint& operator () (const Command& _c) const { return _c.GetKey(); }
};
////////////////////////////////////////////////////////////////////////////////////////
// struct _CommandComparator
// ------ ------------------
struct _CommandComparator
{
    int operator () (const uint& _k1, const uint& _k2) const { return _k1 < _k2 ? -1 : _k1 == _k2 ? 0 : 1; }
};
//
typedef List<Command, uint, _CommandKeyExtractor, _CommandComparator, Synchronization::NullThreadMutex<> > _CommandList;
////////////////////////////////////////////////////////////////////////////////////////
// class MacroCommand
// ----- ------------
class MacroCommand : public Command
{
    private:
    _CommandKeyExtractor    Extractor;
    _CommandComparator      Comparator;
    _CommandList            Commands;
    public:
     // ctor/dtor
                            MacroCommand(uint = 0);
     virtual               ~MacroCommand();

     // access
     const _CommandList&    GetCommands()   const;
           _CommandList&    GetCommands();

     // protocol
     void                   AddCommand(Command*);
     int                    Execute(Command::EMode);
     void                   GetDescription(tchar*);
};
////////////////////////////////////////////////////////////////////////////////////////
// class CommandContext
// ----- --------------
class CommandContext
{
    private:
                     CommandContext(const CommandContext&);
     CommandContext& operator = (const CommandContext&);
    public:
                     CommandContext();
     virtual        ~CommandContext() = 0;
};
////////////////////////////////////////////////////////////////////////////////////////
// class UndoManager
// ----- -----------
template <typename _List = _CommandList, typename _Mutex = Synchronization::NullThreadMutex<> > class UndoManager
{
    public:
    
    enum EState
    {
        FreeState = 0, UndoState, RedoState, ErrorState
    };

    enum EStack
    {
        Stacks = 0, UndoStack, RedoStack
    };

    private:
     int                    LevelCount;
     EState                 State;
    _CommandKeyExtractor    Extractor;
    _CommandComparator      Comparator;
    _List                   UndoCommands;
    _List                   RedoCommands;
    _Mutex                  Mutex;
    public:
     // ctor/dtor
                            UndoManager(int = 2, const tchar* = null, uint = Synchronization::TimeoutNoLimit);
     virtual               ~UndoManager();

     // access
     int                    GetLevelCount()             const;
     void                   SetLevelCount(int);

     EState                 GetState()                  const;

     const _List&           GetUndoCommands()           const;
           _List&           GetUndoCommands();
     const _List&           GetRedoCommands()           const;
           _List&           GetRedoCommands();

     bool                   HasUndo(int = 1)            const;
     bool                   HasRedo(int = 1)            const;

     // protocol
     UndoManager::EStack    GetStack(const Command*)    const;

     void                   AddCommand(const Command*);
     void                   RemoveCommand(UndoManager::EStack = EStack::RedoStack);
     void                   Destroy(UndoManager::EStack = EStack::Stacks);

     Command*               Undo(int = 1);
     Command*               Redo(int = 1);
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __UNDO_MANAGER_H__

