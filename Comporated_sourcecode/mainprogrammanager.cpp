#include "mainprogrammanager.h"
#include "ui_mainprogrammanager.h"
#include "playersetupmanager.h"
#include "RunningGameMode.h"
#include "setuprule.h"
#include "settingrule.h"

MainProgramManager::MainProgramManager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainProgramManager)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    curSettingRule = new SettingRule;
}

MainProgramManager::~MainProgramManager()
{
    delete ui;
}

void MainProgramManager::on_startGameButton_clicked()
{
    playerSetupManager = new PlayerSetupManager;
    playerSetupManager->setAttribute(Qt::WA_DeleteOnClose);
    playerSetupManager->show();
    QObject::connect(playerSetupManager, &PlayerSetupManager::startGame, this, &MainProgramManager::createAGame);
}

void MainProgramManager::on_settingButton_clicked()
{
    SetupRule *setupRule = new SetupRule(curSettingRule);
    setupRule->setAttribute(Qt::WA_DeleteOnClose);
    setupRule->show();
}

void MainProgramManager::createAGame(vector< vector<QString> > playerInformation)
{
    vector< vector<string> > tmpPlayerInformationString;
    tmpPlayerInformationString.resize( playerInformation.size() );

    for (size_t i = 0; i < playerInformation.size(); i++)
    {
        for (int j = 0; j < 2; j++) tmpPlayerInformationString[i].push_back( playerInformation[i][j].toStdString() );
    }
    this->hide();

    gameRunningMode = new RunningGameMode(playerInformation.size(), tmpPlayerInformationString, curSettingRule);
    QObject::connect(gameRunningMode, &RunningGameMode::gameOver, this, &MainProgramManager::destroyOldGame);
    QObject::connect(gameRunningMode, &RunningGameMode::showSetting, this, &MainProgramManager::on_settingButton_clicked);
}

void MainProgramManager::destroyOldGame()
{
    delete gameRunningMode;
    this->show();
}

void MainProgramManager::on_exitButton_clicked()
{
    this->close();
}

