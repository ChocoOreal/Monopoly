#include "propertymanager.h"
#include "ui_propertymanager.h"
#include "mainwindow.h"
#include "CommandHandler.h"
#include <mymodelview.h>

PropertyManager::PropertyManager(MainWindow* mainWindow, CommandHandler* invoker,
                                 MainScene* mainScene, myModelView* modelData, QString player, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PropertyManager)
{
    ui->setupUi(this);

    this->mainWindow = mainWindow;
    this->invoker = invoker;
    this->mainScene = mainScene;
    this->modelData = modelData;
    this->playerDoTask = player;

    ui->boardImage->setScene(mainScene);
    modelData->attachViewWithModel(ui->cellInfor, 2);
    modelData->attachViewWithModel(ui->listProperty, 5);

    for (int i = 0; i < 13; i++) ui->listProperty->hideColumn(i);
    ui->listProperty->showColumn(0); ui->listProperty->showColumn(1); ui->listProperty->showColumn(2);
    ui->listProperty->showColumn(4); ui->listProperty->showColumn(9); ui->listProperty->showColumn(10);
    ui->listProperty->showColumn(12);
    ui->listProperty->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->listProperty->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    ui->listProperty->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    ui->listProperty->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter | (Qt::Alignment)Qt::TextWordWrap);
    ui->listProperty->horizontalHeader()->setMinimumHeight(50);

    ui->cellInfor->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    modeButtons(1);
    showCellInfo(1);
}

void PropertyManager::modeButtons(int mode)
{
    if (mode == 1)
    {
        ui->buildButton->show();
        ui->mortgageButton->show();
        ui->redeemButton->show();
        ui->sellButton->show();
        ui->confirmButton->hide();
        ui->backButton->hide();
    }
    else
    {
        ui->buildButton->hide();
        ui->mortgageButton->hide();
        ui->redeemButton->hide();
        ui->sellButton->hide();
        ui->confirmButton->show();
        ui->backButton->show();
    }
}

void PropertyManager::showCellInfo(int idCell)
{
    for (int i = 0; i < 40; i++) ui->cellInfor->hideColumn(i);
    ui->cellInfor->showColumn(idCell - 1);
    ui->cellInfor->resizeRowsToContents();
    mainScene->chooseCell(idCell);
}

void PropertyManager::on_buildButton_clicked()
{
    modelData->setTypeFilterProperty("build", playerDoTask);
    modeSelected = "build";
    modeButtons(2);
}

void PropertyManager::on_sellButton_clicked()
{
    modelData->setTypeFilterProperty("sell", playerDoTask);
    modeSelected = "sell";
    modeButtons(2);
}

void PropertyManager::on_mortgageButton_clicked()
{
    modelData->setTypeFilterProperty("mortgage", playerDoTask);
    modeSelected = "mortgage";
    modeButtons(2);
}

void PropertyManager::on_redeemButton_clicked()
{
    modelData->setTypeFilterProperty("redeem", playerDoTask);
    modeSelected = "redeem";
    modeButtons(2);
}

void PropertyManager::on_confirmButton_clicked()
{
    QModelIndexList tmpModelList =  ui->listProperty->selectionModel()->selectedRows(0);
    if (tmpModelList.size() != 0)
    {
        int cellSelected = tmpModelList.back().data().toInt();
        mainWindow->updateInforBetweenWindow( cellSelected );

        if (modeSelected == "build") invoker->doCommand(3);
        else if (modeSelected == "sell") invoker->doCommand(4);
        else if (modeSelected == "mortgage") invoker->doCommand(5);
        else if (modeSelected == "redeem") invoker->doCommand(6);
    }
    else
    {
        mainWindow->showMessageBox("Nothing have been chosen!", {}, true);
    }

}

void PropertyManager::on_exitButton_clicked()
{
    modelData->setTypeFilterProperty("normal", playerDoTask);
    this->close();
}

void PropertyManager::on_backButton_clicked()
{
    modelData->setTypeFilterProperty("normal", playerDoTask);
    modeButtons(1);
}

void PropertyManager::on_listProperty_clicked(const QModelIndex& index)
{
    int cellClicked = ui->listProperty->selectionModel()->selectedRows(0).back().data().toInt();

    showCellInfo(cellClicked);
}

//Resize mainScene automatically when Main Window show up
void PropertyManager::showEvent(QShowEvent *event)
{
    ui->boardImage->fitInView(mainScene->sceneRect(), Qt::KeepAspectRatio);
    ui->listProperty->resizeRowsToContents();
    ui->cellInfor->resizeRowsToContents();
}

//Resize mainScene automatically when Main Window changes size
void PropertyManager::resizeEvent(QResizeEvent *event)
{
    ui->boardImage->fitInView(mainScene->sceneRect(), Qt::KeepAspectRatio);
    ui->listProperty->resizeRowsToContents();
    ui->cellInfor->resizeRowsToContents();
}

PropertyManager::~PropertyManager()
{
    delete ui;
}
