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

    modeButtons(1);
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
    int cellSelected = ui->listProperty->selectionModel()->selectedRows().back().row();
    mainWindow->updateInforBetweenWindow( ui->listProperty->model()->index(cellSelected, 0).data().toInt() );

    if (modeSelected == "build") invoker->doCommand(3);
    else if (modeSelected == "sell") invoker->doCommand(4);
    else if (modeSelected == "mortgage") invoker->doCommand(5);
    else if (modeSelected == "redeem") invoker->doCommand(6);
}

void PropertyManager::on_exitButton_clicked()
{
    this->close();
}

void PropertyManager::on_backButton_clicked()
{
    modeButtons(1);
}

//Resize mainScene automatically when Main Window show up
void PropertyManager::showEvent(QShowEvent *event)
{
    ui->boardImage->fitInView(mainScene->sceneRect(), Qt::KeepAspectRatio);
    //qDebug() << scene->sceneRect().width() << " " << scene->sceneRect().height() << scene->sceneRect().x() << scene->sceneRect().y();
}

//Resize mainScene automatically when Main Window changes size
void PropertyManager::resizeEvent(QResizeEvent *event)
{
    ui->boardImage->fitInView(mainScene->sceneRect(), Qt::KeepAspectRatio);
    //qDebug() << "Resize: " << scene->sceneRect().width() << " " << scene->sceneRect().height() << scene->sceneRect().x() << scene->sceneRect().y();
}

PropertyManager::~PropertyManager()
{
    delete ui;
}
