#ifndef COMMAND_H
#define COMMAND_H

#include <vector>

class Player;
class Cell;
class Game;
class GUI;

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
    private:
        int *_idTurnPlayer;

    public:
        GoCommand(Game* game, int *_idTurnPlayer);
        void execute();
};

class PassCommand : public GameCommand
{
    private:
        int *_idTurnPlayer;

    public:
        PassCommand(Game* game, int *_idTurnPlayer);
        void execute();
};

class BuyCommand : public GameCommand
{
    private:
        int *_idTurnPlayer;

    public:
        BuyCommand(Game* game, int *_idTurnPlayer);
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
        GUI *mainWindow;

    public:
        NotifyCommand(Game *game, GUI *mainWindow) : GameCommand(game) {};
        void execute() {};
};

#endif