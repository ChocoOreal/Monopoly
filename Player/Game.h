#pragma once
#include "Player.h"
#include "Cell.h"
#include "Dice.h"
#include <vector>

class Game
{
private:
    vector<Player *> _Players;
    //Board board; // Need the Board class ASAP
    int _currentPlayer;

    void initializePlayer(int);
    void endGame();
public:
    Game();
    Game(int);

    void ranking(){
        for(Player* curPlayer: _Players){
            cout << curPlayer->toString() << '\n';
        }
    }

    ~Game()
    {
        endGame();
    }
};
