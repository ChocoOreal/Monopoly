#ifndef COMMAND_H
#define COMMAND_H

#include "Game.h"
#include "Player.h"
#include "Cell.h"
#include <vector>

using std::vector;

class Command
{
    public:
        virtual void execute() = 0;
};

class GoCommand : public Command
{
    private:
        vector <Player*> *_listPlayer;
        int *_idTurnPlayer;

    public:
        GoCommand(vector <Player*> &_listPlayer, int &_idTurnPlayer);
        void execute();
};

class PassCommand : public Command
{
    private:
        int *_idTurnPlayer;

    public:
        PassCommand(int &_idTurnPlayer);
        void execute();
};

class BuyCommand : public Command
{
    private:
        vector <Player*> *_listPlayer;
        vector <Cell*> *_listCell;
        int *_idTurnPlayer;

    public:
        BuyCommand(vector <Player*> &_listPlayer, int &_idTurnPlayer);
        void execute();
};

class SellCommand : public Command
{
    private:
        vector <Player*> *_listPlayer;
        vector <Cell*> *_listCell;
        vector <int> *_idChose;

    public:
        SellCommand(vector <Player*> &_listPlayer, vector <int> &_idChose);
        void execute();
};

class Mortage : public Command
{
    private:
        vector <Player*> *_listPlayer;
        vector <Cell*> *_listCell;
        vector <int> *_idChose;

    public:
        Mortage(vector <Player*> &_listPlayer, vector <int> &_idChose);
        void execute();
};

class Redeem : public Command
{
    private:
        vector <Player*> *_listPlayer;
        vector <Cell*> *_listCell;
        vector <int> *_idChose;

    public:
        Redeem(vector <Player*> &_listPlayer, vector <int> &_idChose);
        void execute();
};

class Build : public Command
{
    private:
        vector <Player*> *_listPlayer;
        vector <Cell*> *_listCell;
        vector <int> *_idChose;

    public:
        Build(vector <Player*> &_listPlayer, vector <int> &_idChose);
        void execute();
};

//Command used for: call suitable command for cell that this _player standing. We use this command when a player go to a new position
class ActivateCell : public Command
{
    private:
        Player* _player;
        Cell* _cell;

    public:
        ActivateCell(Player &_player);
        void execute();
};

#endif