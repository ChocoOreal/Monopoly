#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H

#include <vector>

class Command;

using std::vector;

class CommandHandler
{
    private:
        vector <Command*> _listFixedCommand;

    public:
        CommandHandler();

        void addFixedCommand(Command* command);
        void doCommand(int idCommand);
        void doCommand(Command* command);

        ~CommandHandler();
};

#endif