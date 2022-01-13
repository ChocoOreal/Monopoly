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
        now = new Park(line);
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
        now = new Park(line);   
        return;
    }
    else 
    if (type == "gotojail"){
        now = new GoToJail(line);
        return;
    }
    else 
    if (type == "card"){
        now = new Card;
        return;
    }
    // if something missing, this will flag;
    cout << "missing something\nStop to check that please\n";
}


void Game::initializeBoard() {
    _listCell.resize(41); // ListCell[0] will always be NULL (empty space) for nothing much.
    std::ifstream inp;
    inp.open("cellsList.txt");

    for(int i = 0; i < 40; ++i){
        string line;
        std::getline(inp, line);
        std::stringstream ss(line);
        int ID;
        ss >> ID; // getting the block ID;
        string type;
        ss >> type; // reading pass the @.
        ss >> type; // reading the land type.
        // change according the the type and ID.
        
        changeTypeListCell(_listCell[ID], type, line);

        // chỗ này chỉ dùng để cout ra màn hình để check thôi nha :V
        for(string x: _listCell[ID]->toString()){
            cout << x << ' ';
        }
        cout << '\n';
    }
    // close file
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

void Game::transferMoney(int idPlayerFrom, int idPlayerTo, int amnt)
{
    if (idPlayerFrom != -1) _listPlayer[idPlayerFrom]->changeMoney(-amnt);
    if (idPlayerTo != -1) _listPlayer[idPlayerTo]->changeMoney(amnt);
    notifyChange("player", idPlayerFrom);
    notifyChange("player", idPlayerTo);
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
    int temp = (_listPlayer[idPlayer]->Position() - 1 + amountPos) % 40;
    ++temp;
    _listPlayer[idPlayer]->setPosition(temp);
    notifyChange("player", idPlayer);
}

// Di chuyen nguoi choi idPlayer den o co idPlace
void Game::movePlayerTo(int idPlayer, int idPlace){
    int temp = (_listPlayer[idPlayer]->Position() - 1);
    --idPlace;
    if (idPlace >= temp){ // đi trực tiếp.
        movePlayer(idPlayer, idPlace - temp);
    } else { // đi một vòng tròn đến vị trí đó.
        movePlayer(idPlayer, 40 - temp);
        movePlayer(idPlayer, idPlace);
    }
    notifyChange("player", idPlayer);
}

void Game::changeJailedState (int idPlayer, bool& jailed)
{
    _listPlayer[idPlayer]->changeInJail(jailed);   
    notifyChange("player", idPlayer);
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
