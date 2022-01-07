#include "Command.h"
#include "Game.h"
#include "Player.h"
#include "Cell.h"
#include "Dice.h"
#include "mainwindow.h"
#include "Util.h"

GameCommand::GameCommand(Game *game)
{
    this->_game = game;
    this->_listPlayer = &game->_listPlayer;
    this->_listCell = &game->_listCell;
}

GoCommand::GoCommand(Game *game, int *_idTurnPlayer) : GameCommand(game)
{
    GoCommand::_idTurnPlayer = _idTurnPlayer;
}

void GoCommand::execute()
{
    int dice1, dice2;

    _game->rollDice();
    _game->getDice(dice1, dice2);
    int newPos = ( (*_listPlayer)[*_idTurnPlayer]->Position() + dice1 + dice2 ) % 40;
    if (newPos == 0) newPos = 40;
    (*_listPlayer)[*_idTurnPlayer]->setPosition(newPos); 
}

PassCommand::PassCommand(Game *game, int *_idTurnPlayer) : GameCommand(game)
{
    PassCommand::_idTurnPlayer = _idTurnPlayer;
}

void PassCommand::execute()
{
    *_idTurnPlayer = (*_idTurnPlayer + 1) % Player::InstanceCount;
}

BuyCommand::BuyCommand(Game *game, int *_idTurnPlayer) : GameCommand(game)
{
    BuyCommand::_idTurnPlayer = _idTurnPlayer;
}

void BuyCommand::execute()
{
    Player* player = (*_listPlayer)[*_idTurnPlayer];
    NormalLand *cell = dynamic_cast< NormalLand* >( (*_listCell)[ player->Position() ] );
    int price;

    cell->buyLand( player->ID(), price);
    player->changeMoney( -price );
}

SellCommand::SellCommand(Game *game, vector <int> *_idChose) : GameCommand(game)
{
    SellCommand::_idChose = _idChose;
}

void SellCommand::execute()
{
    int idPlayer = (*_idChose)[0];
    int idLand = (*_idChose)[1];
    Player* player = (*_listPlayer)[idPlayer];
    NormalLand *cell = dynamic_cast< NormalLand* > ( (*_listCell)[ idLand ] );
    int price;

    cell->sellHouse(price);
    player->changeMoney( price );
}

Mortage::Mortage(Game *game, vector <int> *_idChose) : GameCommand(game)
{
    Mortage::_idChose = _idChose;
}

void Mortage::execute()
{
    int idPlayer = (*_idChose)[0];
    int idLand = (*_idChose)[1];
    int price(0);
    Player* player = (*_listPlayer)[idPlayer];
    RealEstate *cell = dynamic_cast< RealEstate* > ( (*_listCell)[ idLand ] );

    cell->mortgage(price);
    player->changeMoney(price);
}

Redeem::Redeem(Game *game, vector <int> *_idChose) : GameCommand(game)
{
    Redeem::_idChose = _idChose;
}

void Redeem::execute()
{
    int idPlayer = (*_idChose)[0];
    int idLand = (*_idChose)[1];
    Player* player = (*_listPlayer)[idPlayer];
    NormalLand *cell = dynamic_cast< NormalLand* > ( (*_listCell)[ idLand ] );
    //REDEEM FUNCTION
}

Build::Build(Game *game, vector <int> *_idChose) : GameCommand(game)
{
    Build::_idChose = _idChose;
}

void Build::execute()
{
    int idPlayer = (*_idChose)[0];
    int idLand = (*_idChose)[1];
    Player* player = (*_listPlayer)[idPlayer];
    NormalLand *cell = dynamic_cast< NormalLand* > ( (*_listCell)[idLand] );
    int price;

    cell->build(price);
    player->changeMoney( -price );
}

Update::Update(Game *game, MainWindow *mainWindow) : GameCommand(game)
{
    this->mainWindow = mainWindow;
}

void Update::execute()
{
    string typeUpdate;
    int idUpdate;
    _game->getNotifyChange(typeUpdate, idUpdate);

    //Update the dice result
    if (typeUpdate == "dice")
    {
        int dice1, dice2;

        _game->getDice(dice1, dice2);
        mainWindow->updateDiceData(dice1, 0);
        mainWindow->updateDiceData(dice2, 1);
    }
    else if (typeUpdate == "player")
    {
        string tmpString = (*_listPlayer)[idUpdate]->toString();
        mainWindow->updatePlayer(idUpdate, Util::parse(tmpString,"_", 0) );
    }
    else
    {
        mainWindow->updateCell(idUpdate, (*_listCell)[idUpdate]->toString());
    }
}
