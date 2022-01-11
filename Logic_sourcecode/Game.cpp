#include "Game.h"
#include "Player.h"
#include "Cell.h"
#include "Dice.h"
#include "CommandHandler.h"
#include <fstream>

Game::Game() 
{
    _idTurnPlayer = 0;
    initializePlayer(0);
}

Game::Game(int number) 
{
    _idTurnPlayer = number - 1;
    initializePlayer(number);

    Cell::setInterfaceGame(this);
    initializeBoard();
    // _listCell.resize(45);
    // _listCell[16] = new NormalLand("16 @ normalland @ Hi @ Hi @ 0 @ 0 @ 0 @ 0 @ 0");
    // _listCell[17] = new NormalLand("17 @ normalland @ Hi @ Hi @ 1000 @ 200 @ 2 @ 200 @ 100");
    
}


void changeTypeListCell(Cell*& now, string type, string& line){
    if (type == "go"){
        now = new Go(line);
        return;
    } else 
    if (type == "normalland"){
        now = new NormalLand(line);
        return;
    } else 
    if (type == "jailcell"){
        now = new JailCell(line);
        return;
    } else 
    if (type == "paytax"){
        now = new PayTax(line);
        return;
    } else 
    if (type == "railroad"){
        now = new Railroad(line);
        return;
    } else
    if (type == "factory"){
        now = new Factory(line);
        return;
    } else
    if (type == "park"){
        now = new Go(line);
        
    }
    
    // if something missing, this will flag;
    cout << "missing something\nStop to check that please";
}

// nên cài đặt vào trong đây nha Như.
void Game::initializeBoard() {
    _listCell.resize(40);
    std::ifstream inp;
    inp.open("cellList.txt");

    for(int i = 0; i < 40; ++i){
        string line;
        std::getline(inp, line);
        std::stringstream ss(line);
        int ID;
        ss >> ID;
        string type;
        ss >> type;
        ss >> type;
        
        changeTypeListCell(_listCell[ID], type, line);
    }
    inp.close();
}


void Game::initializePlayer(int numberOfPlayer)
{
    _idTurnPlayer = numberOfPlayer - 1;
    _listPlayer.resize(numberOfPlayer);
    
    for (Player *&curPlayer : _listPlayer)
    {
        curPlayer = new Player (this, "Hoang");
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

void Game::transferMoney(int idPlayerFrom, int idPlayerTo, int amount)
{
    if (idPlayerFrom != -1) _listPlayer[idPlayerFrom]->changeMoney(-amount);
    if (idPlayerTo != -1) _listPlayer[idPlayerTo]->changeMoney(amount);
    notifyChange("player", idPlayerFrom);
    notifyChange("player", idPlayerTo);
}

string Game::notify(const string &text, const vector <string> &listQuery, const bool waitResponde)
{
    _notification.textNotify = text;
    _notification.listQuery = listQuery;

    //invoker->doCommand(7);

    return _notification.ans;
}

/* 
    Di chuyen nguoi choi idPlayer toi o co id la pos
*/
void Game::movePlayer(int idPlayer, int amountPos)
{
    int temp = (_listPlayer[idPlayer]->Position() - 1 + amountPos) % 40;
    ++temp;
    _listPlayer[idPlayer]->setPosition(temp);
    notifyChange("player", idPlayer);
}

// thật ra thì cái state đó mình cũng ko cần phải quan tâm nhiều 
// theo định nghĩa của tên thì chỉ là thay đổi qua lại giữa hai trạng thái true / false.
// nên để một giá trị mặc định như vậy trước, nếu muốn thì đổi luôn cũng được.
void Game::changeJailedState(int idPlayer, bool jailed = false)
{
    _listPlayer[idPlayer]->changeInJail();   
    notifyChange("player", idPlayer);
}

void Game::notifyChange(const string &type, int id)
{
    _typeUpdate = type;
    _idUpdate = id;
    //invoker->doCommand(8);
}

void Game::getNotifyChange(string &type, int &id)
{
    type = _typeUpdate;
    id = _idUpdate;
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


