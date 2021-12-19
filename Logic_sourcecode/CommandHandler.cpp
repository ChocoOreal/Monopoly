#include "CommandHandler.h"
#include "Command.h"
#include <iostream>

CommandHandler::CommandHandler() {};

void CommandHandler::addFixedCommand(Command* command)
{
    _listFixedCommand.push_back(command);
}

void CommandHandler::doCommand(int idCommand)
{
    _listFixedCommand[idCommand]->execute();
}

void CommandHandler::doCommand(Command* command)
{
    command->execute();
}

CommandHandler::~CommandHandler()
{
    for (int i = 0; i < _listFixedCommand.size(); i++) delete _listFixedCommand[i];
}