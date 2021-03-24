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

#ifndef __UNDO_MANAGER_INC__
#   include <UndoManager.inc>
#endif

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class Command
// ----- -------
Command::Command(uint _id) : ObjectRef<>(_id)
{
}

Command::Command(const Command& _other)
{
    operator = (_other);
}

Command::~Command()
{
}

Command& Command::operator = (const Command& _other)
{
    return *this;
}

int Command::Execute(Command::EMode)
{
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////
// class MacroCommand
// ----- ------------
MacroCommand::MacroCommand(uint _id) : Command(_id), Commands(Extractor, Comparator)
{
}

MacroCommand::~MacroCommand()
{
}

int MacroCommand::Execute(Command::EMode _mode)
{
    ListIterator<Command, uint> iter(Commands.GetHead());
    //
    for(; iter; iter++)
    {
        static_cast<Command&>(iter.Current()).Execute(_mode);
    }

    return 1;
}
////////////////////////////////////////////////////////////////////////////////////////
// class CommandContext
// ----- --------------
CommandContext::CommandContext()
{
}

CommandContext::~CommandContext()
{
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__
