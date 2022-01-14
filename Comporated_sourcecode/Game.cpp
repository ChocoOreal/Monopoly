#include "Game.h"
#include "Player.h"
#include "Cell.h"

#include "Dice.h"
#include <random>

#include "CommandHandler.h"
#include "gamecomponents.h"
#include <iostream>
#include <fstream>
#include <QDebug>
#include "RunningGameMode.h"
#include <QString>
#include "settingrule.h"

Game::Game() 
{
}

Game::Game(int number, vector< vector<string> > playerInformation, RunningGameMode* runningGameMode, SettingRule *curSettingRule)
{
    globalGameStatus = new GlobalGameStatus(this);
    _notification = new Notify;
    Game::curSettingRule = curSettingRule;

    initializePlayer(number, playerInformation);
    initializeBoard();

    Cell::setInterfaceGame(this);

    Game::runningGameMode = runningGameMode;
}

void Game::initializeBoard() {
     //In case pointer of cells are invalid
     _listCell.resize(41);
     for (int i = 0; i <= 40; i++) _listCell[i] = nullptr;

     //Use to store data read from file data
     vector <string> tmpString;
     tmpString.resize(40);

     std::ifstream DataFile("Data\\cellsList.txt");
     for (int i = 0; i < 40; i++) std::getline(DataFile, tmpString[i]);

     _listCell[1] = new Go(tmpString[0]);
     _listCell[11] = new JailCell(tmpString[1]);
     _listCell[21] = new Park(tmpString[2]);
     _listCell[31] = new GoToJail(tmpString[3]);

     for (int i = 4; i <= 9; i++)
     {
         Card *tmpCell = new Card(tmpString[i]);
         _listCell[ tmpCell->getID() ] = tmpCell;
     }

     for (int i = 10; i <= 13; i++)
     {
         Railroad *tmpCell = new Railroad(tmpString[i]);
         _listCell[ tmpCell->getID() ] = tmpCell;
     }

     for (int i = 14; i <= 15; i++)
     {
         Factory *tmpCell = new Factory(tmpString[i]);
         _listCell[ tmpCell->getID() ] = tmpCell;
     }

     for (int i = 16; i <= 17; i++)
     {
         PayTax *tmpCell = new PayTax(tmpString[i]);
         _listCell[ tmpCell->getID() ] = tmpCell;
     }

     for (int i = 18; i <= 39; i++)
     {
         NormalLand *tmpCell = new NormalLand(tmpString[i]);
         _listCell[ tmpCell->getID() ] = tmpCell;
     }
}


void Game::initializePlayer(int numberOfPlayer, vector< vector<string> > &playerInformation)
{
    _listPlayer.resize(numberOfPlayer);
    
    for (Player *&curPlayer : _listPlayer)
    {
        curPlayer = new Player (this, playerInformation[Player::InstanceCount][0], playerInformation[Player::InstanceCount][1]);
    }
}

void Game::syncData()
{
    for (int i = 1; i <= 40; i++)
        if (_listCell[i] != nullptr) notifyChange("cell", i);
    for (int i = 0; i < Player::InstanceCount; i++) notifyChange("player", i);
    globalGameStatus->setTurnPlayer(0);

    notify( askStringName("player", 0) + " bắt đầu trò chơi đầu tiên");
}

void Game::rollDice()
{
    _dice1 = rand() % 6 + 1;
    _dice2 = rand() % 6 + 1;

    notifyChange("dice");
}

void Game::getDice(int &dice1, int &dice2)
{
    dice1 = _dice1;
    dice2 = _dice2;
}

void Game::transferMoney(int idPlayerFrom, int idPlayerTo, int amount)
{
    if (idPlayerFrom != -1) _listPlayer[idPlayerFrom]->changeMoney(-amount);
    if (idPlayerTo != -1) _listPlayer[idPlayerTo]->changeMoney(amount);
    if (idPlayerFrom != -1) _listPlayer[idPlayerFrom]->setDebtTo(idPlayerTo);

    notify( askStringName("player", idPlayerTo) + " nhận " + std::to_string(amount) + " từ " + askStringName("player", idPlayerFrom) );
}

string Game::notify(const string &text, const vector <string> &listQuery, const bool waitResponde)
{
    _notification->setNotify(text, listQuery, waitResponde);

    invoker->doCommand(7);

    return _notification->getAns();
}

/* 
    Di chuyen nguoi choi idPlayer toi o co id la pos
*/
void Game::movePlayer(int idPlayer, int amountPos)
{
    int temp = (_listPlayer[idPlayer]->Position() - 1 + amountPos) % 40;
    ++temp;

    if (_listPlayer[idPlayer]->Position() > temp) dynamic_cast<Go*>( _listCell[1])->passGoCell(idPlayer);
    _listPlayer[idPlayer]->setPosition(temp);
    if (temp != 11) _listCell[temp]->activateCell( idPlayer );
}

// thật ra thì cái state đó mình cũng ko cần phải quan tâm nhiều 
// theo định nghĩa của tên thì chỉ là thay đổi qua lại giữa hai trạng thái true / false.
// nên để một giá trị mặc định như vậy trước, nếu muốn thì đổi luôn cũng được.
void Game::changeJailedState(int idPlayer, bool jailed = false)
{
    _listPlayer[idPlayer]->changeInJail();   
}

void Game::notifyChange(const string &type, int id)
{
    _typeUpdate = type;
    _idUpdate = id;
    invoker->doCommand(8);
}

void Game::getNotifyChange(string &type, int &id)
{
    type = _typeUpdate;
    id = _idUpdate;
}

string Game::askStringName(const string &type, int id)
{
    if (type == "player") return ( (id >= 0 && id < Player::InstanceCount) ? _listPlayer[id]->Name() : "No" );
    else if (type == "cell") return ( (id >= 1 && id <= 40) ? _listCell[id]->getName() : "No" );

    return "";
}

int Game::querySettingRule(const string &queryOp)
{
    if (queryOp == "parkOp") return curSettingRule->getParkOp();
    else if (queryOp == "passGoOp") return curSettingRule->getPassGoOp();
    else if (queryOp == "inGoOp") return curSettingRule->getInGoOp();
    else return curSettingRule->getStartOp();
}

void Game::declareBankruptPlayer(int idPlayerBankrupt)
{
    int idCreditor = _listPlayer[idPlayerBankrupt]->debtTo();

    for (int i = 1; i <= 40; i++) _listCell[i]->bankruptThisCell(idPlayerBankrupt, idCreditor);
    transferMoney(idPlayerBankrupt, idCreditor, _listPlayer[idPlayerBankrupt]->Money() );
    _listPlayer[idPlayerBankrupt]->setGameOver();
    Player::NumberLeftPlayer--;
    qDebug() << Player::NumberLeftPlayer;
    if (Player::NumberLeftPlayer <= 1) endGame();
}

void Game::endGame()
{
    int playerWin(0);

    for (int i = 0; i < Player::InstanceCount; i++)
        if ( !_listPlayer[i]->IsGameOver() )
        {
            playerWin = i;
            break;
        }

    notify( askStringName("player", playerWin) + " đã may mắn chiến thắng một cách ngoạn mục!", {}, true);
    runningGameMode->notifyGameOver();
}

Game::~Game()
{
    for (int i = 0; i < _listPlayer.size(); i++) delete _listPlayer[i];
    for (int i = 1; i <= 40; i++) delete _listCell[i];
}

