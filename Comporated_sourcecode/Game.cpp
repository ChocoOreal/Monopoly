#include "Game.h"
#include "Player.h"
#include "Cell.h"
#include "Dice.h"
#include "CommandHandler.h"

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
        curPlayer = new Player (this);
    }
}

void Game::rollDice()
{
    _dice1 = Dice::Rand(1, 6);
    _dice2 = Dice::Rand(1, 6);

    notifyChange("dice");
}

void Game::getDice(int &dice1, int &dice2)
{
    dice1 = _dice1;
    dice2 = _dice2;
}

void Game::transferMoney(int idPlayerFrom, int idPlayerTo, int amnt)
{
    
}

string Game::notify(const string &text, const vector <string> &listQuery, const bool waitResponde)
{
    _notification.textNotify = text;
    _notification.listQuery = listQuery;

    invoker->doCommand(7);

    return _notification.ans;
}

/* Di chuyen nguoi choi idPlayer toi o co id la pos
*/
void Game::movePlayer(int idPlayer, int amountPos)
{
    //tinh toan o moi va goi ham thay doi cua nguoi choi
    //goi ham activateCell cua o moi nguoi choi vua buoc vao
}

void Game::changeJailedState (int idPlayer, bool& jailed)
{
    
}

void Game::notifyChange(const string &type, int id)
{
    _typeUpdate = type;
    _idUpdate = id;
    invoker->doCommand(3);
}

void Game::getNotifyChange(string &type, int &id)
{
    type = _typeUpdate;
    id = _idUpdate;
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