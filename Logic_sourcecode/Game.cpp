#include "Game.h"
#include "Player.h"
#include "Cell.h"
#include "Dice.h"

Game::Game() 
{
    _idTurnPlayer = 0;
    initializePlayer(0);
}

Game::Game(int number) 
{
    _idTurnPlayer = number - 1;
    initializePlayer(number);
}

void Game::initializePlayer(int numberOfPlayer)
{
    _idTurnPlayer = numberOfPlayer - 1;
    _listPlayer.resize(numberOfPlayer);
    
    for (Player *&curPlayer : _listPlayer)
    {
        curPlayer = new Player;
    }
}

void Game::rollDice()
{
    _dice1 = Dice::Rand(1, 6);
    _dice2 = Dice::Rand(1, 6);
}

int Game::getDice()
{
    return _dice1 + _dice2;
}

void Game::transferMoney(int idPlayerFrom, int idPlayerTo, int moneyValue)
{
    
}

void Game::notify(string text, vector <string> listQuery)
{
    
}

void Game::ranking()
{
}

void Game::endGame()
{
    _idTurnPlayer = 0;

    for (Player*& curPlayer: _listPlayer) 
    {
        if (curPlayer != NULL) 
        {   
            delete curPlayer;
        }
    }

}