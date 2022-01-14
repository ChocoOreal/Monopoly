#ifndef COMMAND_H
#define COMMAND_H

#include <vector>
#include <string>

class Player;
class Cell;
class Game;
class MainWindow;
class Notify;

using std::vector;

class Command
{
    public:
        virtual void execute() = 0;
};

class GameCommand : public Command
{
    protected:
        Game* _game;
        vector <Player *> *_listPlayer;
        vector <Cell *> *_listCell;

    public:
        GameCommand(Game *game);
};

class GoCommand : public GameCommand
{
    public:
        GoCommand(Game* game);
        void execute();
};

class PassCommand : public GameCommand
{
    public:
        PassCommand(Game* game);
        void execute();
};

class BuyCommand : public GameCommand
{
    public:
        BuyCommand(Game* game);
        void execute();
};

class SellCommand : public GameCommand
{
    private:
        vector <int> *_idChose;

    public:
        SellCommand(Game* game, vector <int> *_idChose);
        void execute();
};

class Mortage : public GameCommand
{
    private:
        vector <int> *_idChose;

    public:
        Mortage(Game* game, vector <int> *_idChose);
        void execute();
};

class Redeem : public GameCommand
{
    private:
        vector <int> *_idChose;

    public:
        Redeem(Game* game, vector <int> *_idChose);
        void execute();
};

class Build : public GameCommand
{
    private:
        vector <int> *_idChose;

    public:
        Build(Game *game, vector <int> *_idChose);
        void execute();
};

class NotifyCommand : public GameCommand
{
    private:
        MainWindow *mainWindow;
        Notify *notification;

    public:
        NotifyCommand(Game *game, MainWindow *mainWindow, Notify *notification);
        void execute();
};

class Update : public GameCommand
{
    private:
        MainWindow *mainWindow;

    public:
        Update(Game *game, MainWindow *mainWindow);
        void execute();
};

class BankruptCommand : public GameCommand
{
    private:
        vector <int> *_idChose;

    public:
        BankruptCommand(Game *game, vector <int> *_idChose) : GameCommand(game) { BankruptCommand::_idChose = _idChose; }
        void execute();
};

class ExitGameCommand : public GameCommand
{
    public:
        ExitGameCommand(Game *game) : GameCommand(game) {};
        void execute();
};

#endif
