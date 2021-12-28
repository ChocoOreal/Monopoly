#pragma once

#include "IGame.h"
#include <vector>
#include <iostream>
#include <string>

class Player;
class Cell;
class GameCommand;
class RunningGameMode;

using std::vector; using std::cout; using std::string;

class Game : public IGame
{
    private:
        vector <Player *> _listPlayer;
        vector <Cell *> _listCell;
        int _idTurnPlayer;
        int _dice1, _dice2;

        //This is the query or notification that game need to show for player deciding or knowing
        struct Notify
        {
            string textNotify; //Information show what happened in game
            vector <string> listQuery; //List of choices for a given textNotify
            string ans; //Choice player have chose in the listQuery
        } _notification;

        void initializePlayer(int);
        void endGame();
        
    public:
        Game();
        Game(int);

        void rollDice();
        int getDice();
        void transferMoney(int idPlayerFrom, int idPlayerTo, int moneyValue);
        void notify(string text, vector <string> listQuery);

        void ranking();

        ~Game()
        {
            endGame();
        }

        friend GameCommand;
        friend RunningGameMode;
};
