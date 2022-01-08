#pragma once

#include "IGame.h"
#include <vector>
#include <iostream>
#include <string>

class Player;
class Cell;
class GameCommand;
class RunningGameMode;
class CommandHandler;

using std::vector; using std::cout; using std::string;

class Game : public IGame
{
    private:
        vector <Player *> _listPlayer;
        vector <Cell *> _listCell;
        int _idTurnPlayer;
        int _dice1, _dice2;
        CommandHandler* invoker;

        string _typeUpdate; int _idUpdate;

        //This is the query or notification that game need to show for player deciding or knowing
        struct Notify
        {
            string textNotify; //Information show what happened in game
            vector <string> listQuery; //List of choices for a given textNotify
            string ans; //Choice player have chose in the listQuery
        } _notification;

        void initializePlayer(int);
        void initializeBoard();
        
        void endGame();
        
    public:
        Game();
        Game(int);

        void rollDice();

        void getDice(int &dice1, int &dice2);

        void transferMoney(int idPlayerFrom, int idPlayerTo, int amnt);

        string notify(const string &text, const vector <string> &listQuery = {}, const bool waitResponde = false);

        void movePlayer(int idPlayer, int pos);

        void changeJailedState (int idPlayer, bool jailed);

        void notifyChange(const string &type, int id = 0);

        void getNotifyChange(string &type, int &id);

        void ranking();

        ~Game()
        {
            endGame();
        }

        friend GameCommand;
        friend RunningGameMode;
};
