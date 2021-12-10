#include "Command.h"
#include "Dice.h"

GoCommand::GoCommand(vector <Player*> &_listPlayer, int &_idTurnPlayer)
{
    GoCommand::_listPlayer = &_listPlayer;
    GoCommand::_idTurnPlayer = &_idTurnPlayer;
};

void GoCommand::execute()
{
    int dice1 = Dice::Rand(1, 6);
    int dice2 = Dice::Rand(1, 6);

    (*_listPlayer)[*_idTurnPlayer]->setPosition( dice1 + dice2 ); 
}

PassCommand::PassCommand(int &_idTurnPlayer)
{
    PassCommand::_idTurnPlayer = &_idTurnPlayer;
}

void PassCommand::execute()
{
    _idTurnPlayer;
}

BuyCommand::BuyCommand(vector <Player*> &_listPlayer, int &_idTurnPlayer)
{
    BuyCommand::_listPlayer = &_listPlayer;
    BuyCommand::_idTurnPlayer = &_idTurnPlayer;
}

void BuyCommand::execute()
{
    Player* player = (*_listPlayer)[*_idTurnPlayer];
    NormalLand *cell = dynamic_cast< NormalLand* >( (*_listCell)[ player->Position() ] );

    player->changeMoney( cell->buyLand(player) );
}

SellCommand::SellCommand(vector <Player*> &_listPlayer, vector <int> &_idChose)
{
    SellCommand::_listPlayer = &_listPlayer;
    SellCommand::_idChose = &_idChose;
}

void SellCommand::execute()
{
    int idPlayer = (*_idChose)[0];
    int idLand = (*_idChose)[1];
    Player* player = (*_listPlayer)[idPlayer];
    NormalLand *cell = dynamic_cast< NormalLand* > ( (*_listCell)[ idLand ] );

    player->changeMoney( cell->sellHouse() );
}

Mortage::Mortage(vector <Player*> &_listPlayer, vector <int> &_idChose)
{
    Mortage::_listPlayer = &_listPlayer;
    Mortage::_idChose = &_idChose;
}

void Mortage::execute()
{
    int idPlayer = (*_idChose)[0];
    int idLand = (*_idChose)[1];
    Player* player = (*_listPlayer)[idPlayer];
    NormalLand *cell = dynamic_cast< NormalLand* > ( (*_listCell)[ idLand ] );

    cell->Mortgage();
    //CHANGE MONEY
}

Redeem::Redeem(vector <Player*> &_listPlayer, vector <int> &_idChose)
{
    Redeem::_listPlayer = &_listPlayer;
    Redeem::_idChose = &_idChose;
}

void Redeem::execute()
{
    int idPlayer = (*_idChose)[0];
    int idLand = (*_idChose)[1];
    Player* player = (*_listPlayer)[idPlayer];
    NormalLand *cell = dynamic_cast< NormalLand* > ( (*_listCell)[ idLand ] );
    //REDEEM FUNCTION
}

Build::Build(vector <Player*> &_listPlayer, vector <int> &_idChose)
{
    Build::_listPlayer = &_listPlayer;
    Build::_idChose = &_idChose;
}

void Build::execute()
{
    int idPlayer = (*_idChose)[0];
    Player* player = (*_listPlayer)[idPlayer];
    NormalLand *cell = dynamic_cast< NormalLand* > ( (*_listCell)[ player->Position() ] );

    //CHECK NUMBER OF HOUSE TO CALL BUILD HOUSE FUNCTION OR BUILD HOTEL FUNTION RESPECTIVELY
    //CHANGE PLAYER MONEY
}

