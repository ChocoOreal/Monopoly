#include "Game.h"

Game::Game(){
    _currentPlayer = 0;
    initializePlayer(0);
}

Game::Game(int number){
    _currentPlayer = number;
    initializePlayer(number);
}

void Game::initializePlayer(int numberOfPlayer)
{
    _currentPlayer = numberOfPlayer;
    _Players.resize(numberOfPlayer);
    for (Player *&curPlayer : _Players)
    {
        curPlayer = new Player;
    }
}

void Game::endGame()
{
    _currentPlayer = 0;
    for(Player*& curPlayer: _Players){
        if (curPlayer != NULL){
            delete curPlayer;
        }
    }

}