#include "RunningGameMode.h"
#include "CommandHandler.h"
#include "Command.h"
#include "Game.h"
#include "mainwindow.h"
#include "settingrule.h"

/* Remove mainwindow.h and all relevant class for running in VSCode */

RunningGameMode::RunningGameMode()
{
    mainWindow = nullptr;
    invoker = nullptr;
    game = nullptr;
}

RunningGameMode::RunningGameMode(int numPlayer, vector< vector<string> > playerInformation, SettingRule *curSettingRule)
{
    mainWindow = new MainWindow(numPlayer);
    invoker = new CommandHandler;
    game = new Game(numPlayer, playerInformation, this, curSettingRule);
    RunningGameMode::curSettingRule = curSettingRule;

    invoker->addFixedCommand( new GoCommand(game) );
    invoker->addFixedCommand( new PassCommand(game) );
    invoker->addFixedCommand( new BuyCommand(game) );
    invoker->addFixedCommand( new Build(game, &mainWindow->idChose) );
    invoker->addFixedCommand( new SellCommand(game, &mainWindow->idChose) );
    invoker->addFixedCommand( new Mortage(game, &mainWindow->idChose) );
    invoker->addFixedCommand( new Redeem(game, &mainWindow->idChose) );
    invoker->addFixedCommand( new NotifyCommand(game, mainWindow, game->_notification) );
    invoker->addFixedCommand( new Update(game, mainWindow) );
    invoker->addFixedCommand( new BankruptCommand(game, &mainWindow->idChose) );
    invoker->addFixedCommand( new ExitGameCommand(game) );

    game->invoker = invoker;
    mainWindow->invoker = invoker;
    game->syncData();
    mainWindow->runWhenStart();

    mainWindow->showMaximized();

    QObject::connect(mainWindow, &MainWindow::showSetting, this, &RunningGameMode::receiveShowSettingRequest);
}

void RunningGameMode::receiveShowSettingRequest()
{
    emit showSetting();
}

void RunningGameMode::notifyGameOver()
{
    emit gameOver();
}

RunningGameMode::~RunningGameMode()
{
    delete mainWindow;
    delete invoker;
    delete game;
}

CommandHandler* RunningGameMode::getCommandHandler()
{
    return invoker;
}
