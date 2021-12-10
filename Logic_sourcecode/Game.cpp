#include "Game.h"

Game::Game(){
    _idTurnPlayer = 0;
    initializePlayer(0);
}

Game::Game(int number){
    _idTurnPlayer = number;
    initializePlayer(number);
}

void Game::initializePlayer(int numberOfPlayer)
{
    _idTurnPlayer = numberOfPlayer;
    _listPlayer.resize(numberOfPlayer);
    for (Player *&curPlayer : _listPlayer)
    {
        curPlayer = new Player;
    }
}

void Game::endGame()
{
    _idTurnPlayer = 0;
    for(Player*& curPlayer: _listPlayer){
        if (curPlayer != NULL){
            delete curPlayer;
        }
    }

}