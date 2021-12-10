#pragma once
#include "Player.h"
#include "Cell.h"
#include "Dice.h"
#include <vector>

class Game
{
private:
    vector<Player *> _listPlayer;
    //Board board; // Need the Board class ASAP
    int _idTurnPlayer;

    void initializePlayer(int);
    void endGame();
public:
    Game();
    Game(int);

    void ranking(){
        for(Player* curPlayer: _listPlayer){
            cout << curPlayer->toString() << '\n';
        }
    }

    ~Game()
    {
        endGame();
    }
};
