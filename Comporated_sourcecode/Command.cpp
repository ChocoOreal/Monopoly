#include "Command.h"
#include "Game.h"
#include "Player.h"
#include "Cell.h"
#include "Dice.h"
#include "mainwindow.h"
#include "Util.h"
#include "gamecomponents.h"

/* In this file, the mainwindow.h and all relevant class must be eleminated for running in VSCode*/

GameCommand::GameCommand(Game *game)
{
    this->_game = game;
    this->_listPlayer = &game->_listPlayer;
    this->_listCell = &game->_listCell;
}

GoCommand::GoCommand(Game *game) : GameCommand(game)
{
}

void GoCommand::execute()
{
    static int timeDoubleRoll(0); //Count number of double roll using for moving
    int dice1, dice2;
    int idTurnPlayer = _game->getGlobalGameStatus()->getTurnPlayer();

    //Nếu lệnh đi thực hiện khi trong tù: gọi kích hoạt chức năng của ô Ở tù
    if ( (*_listPlayer)[idTurnPlayer]->isInJail() )
    {
        (*_listCell)[11]->activateCell(idTurnPlayer);
        //Nếu đã đi ra khỏi ô Nhà tù: đã thực hiện lệnh đi bằng xúc xắc đôi, cập nhật chuyển giao lượt chơi và thoát lệnh Đi
        if ( (*_listPlayer)[idTurnPlayer]->Position() != 11 || (*_listPlayer)[idTurnPlayer]->isInJail() )
        {
            _game->getGlobalGameStatus()->setRepeatTurn(false);
            return;
        }
    }

    //Lệnh đi bình thường
    _game->rollDice();
    _game->getDice(dice1, dice2);

    if (dice1 == dice2)
    {
        timeDoubleRoll++;
        _game->notify( _game->askStringName("player", idTurnPlayer) + " thả được số đôi " + std::to_string(dice1) );
    }
    else
    {
        timeDoubleRoll = 0;
        _game->notify( _game->askStringName("player", idTurnPlayer) + " thả được " + std::to_string(dice1 + dice2) );
    }

    if (timeDoubleRoll < 3)
    {
        _game->movePlayer(idTurnPlayer, dice1 + dice2);
        if (timeDoubleRoll != 0) _game->getGlobalGameStatus()->setRepeatTurn(true); else _game->getGlobalGameStatus()->setRepeatTurn(false);
    }
    else
    {
        timeDoubleRoll = 0;
        (*_listPlayer)[idTurnPlayer]->changeInJail();
    }
}

PassCommand::PassCommand(Game *game) : GameCommand(game)
{
}

void PassCommand::execute()
{
    for (int i = 0; i < Player::InstanceCount; i++)
        if ( (*_listPlayer)[i]->Money() < 0)
        {
            _game->notify("Tồn tại người chơi đang nợ tiền, cần phải xử lý việc này trước khi qua lượt mới", {}, true);
            return;
        }

    int tmp(1), nextTurn;
    while ( (*_listPlayer)[ nextTurn = ( _game->getGlobalGameStatus()->getTurnPlayer() + tmp) % Player::InstanceCount ]->IsGameOver() )
        tmp++;
    _game->getGlobalGameStatus()->setTurnPlayer( nextTurn );
    _game->notify( _game->askStringName("player", nextTurn) + " bắt đầu lượt của mình");
}

BuyCommand::BuyCommand(Game *game) : GameCommand(game)
{
}

void BuyCommand::execute()
{
    Player* player = (*_listPlayer)[ _game->getGlobalGameStatus()->getTurnPlayer() ];
    RealEstate *cell = dynamic_cast< RealEstate* >( (*_listCell)[ player->Position() ] );
    int price;

    cell->buyLand( player->ID(), price);
    player->changeMoney( -price );

    _game->notify( player->Name() + " mua " + cell->getName() + " với giá " + std::to_string(price) );
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

    _game->notify( player->Name() + " đã bán căn nhà tại " + cell->getName() + " nhận được " + std::to_string(price) );
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

    _game->notify( player->Name() + " cầm cố " + cell->getName() + " nhận được " + std::to_string(price) );
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
    RealEstate *cell = dynamic_cast< RealEstate* > ( (*_listCell)[ idLand ] );

    int money;
    cell->redeem(money);
    player->changeMoney(-money);

    _game->notify( player->Name() + " nhận lại " + cell->getName() + " với chi phí " + std::to_string(money) );
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

    _game->notify( player->Name() + " xây nhà tại " + cell->getName() + " với chi phí " + std::to_string(price) );
}

NotifyCommand::NotifyCommand(Game *game, MainWindow *mainWindow, Notify *notification) : GameCommand(game)
{
    NotifyCommand::mainWindow = mainWindow;
    NotifyCommand::notification = notification;
}

void NotifyCommand::execute()
{
    notification->ans = mainWindow->showMessageBox(notification->textNotify, notification->listQuery, notification->waitResponde);
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
    else if (typeUpdate == "cell")
    {
        mainWindow->updateCell(idUpdate, (*_listCell)[idUpdate]->toString());
    }
    else if (typeUpdate == "gameStatus")
    {
        mainWindow->updateGameStatus( Util::parse( _game->getGlobalGameStatus()->toString(), "_", 0) );
    }
}

void BankruptCommand::execute()
{
    _game->declareBankruptPlayer( (*_idChose)[0] );
    _game->getGlobalGameStatus()->setRepeatTurn(false);
}

void ExitGameCommand::execute()
{
    _game->endGame();
}
