#include "propertymanager.h"
#include "ui_propertymanager.h"
#include "mainwindow.h"
#include <mymodelview.h>

PropertyManager::PropertyManager(MainWindow* mainWindow, CommandHandler* invoker,
                                 MainScene* mainScene, myModelView* modelData, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PropertyManager)
{
    ui->setupUi(this);

    this->mainWindow = mainWindow;
    this->invoker = invoker;
    this->mainScene = mainScene;
    this->modelData = modelData;

    ui->boardImage->setScene(mainScene);
    modelData->attachViewWithModel(ui->cellInfor, 2);
    modelData->attachViewWithModel(ui->listProperty, 1);
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
