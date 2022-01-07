#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "CommandHandler.h"
#include "mymodelview.h"
#include "propertymanager.h"
#include <QPropertyAnimation>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new MainScene(this);
    ui->graphicsView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing);
    ui->graphicsView->setScene(scene);
    scene->setupMainScene();

    gameModel = new myModelView();
    gameModel->attachViewWithModel(ui->tableCellInfo, 2);
    gameModel->attachViewWithModel(ui->listPlayer, 3);
    ui->listPlayer->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->listPlayer->setSelectionMode(QAbstractItemView::SingleSelection);
}

void MainWindow::updateCell(int idCell, vector<string> info)
{
    gameModel->updateCellData(idCell, info);
}

void MainWindow::updateDiceData(int number, int idDice)
{
    scene->setDiceImage(number, idDice);
}

void MainWindow::updatePlayer(int idPlayer, vector<string> info)
{
    gameModel->updatePlayerData(idPlayer, info);
    scene->setPiece(scene->piece, std::stoi(info[2]) );
    ui->listPlayer->setCurrentIndex( ui->listPlayer->model()->index(idPlayer - 1, 0) );
}

void MainWindow::updateInforBetweenWindow(int id)
{
    idChose.push_back(id);
}

void MainWindow::showCellInfo(int idCell)
{
    for (int i = 0; i < 40; i++) ui->tableCellInfo->hideColumn(i);
    ui->tableCellInfo->showColumn(idCell - 1);
}

//Resize mainScene automatically when Main Window show up
void MainWindow::showEvent(QShowEvent *event)
{
    ui->graphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
    //qDebug() << scene->sceneRect().width() << " " << scene->sceneRect().height() << scene->sceneRect().x() << scene->sceneRect().y();
}

//Resize mainScene automatically when Main Window changes size
void MainWindow::resizeEvent(QResizeEvent *event)
{
    ui->graphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
    //qDebug() << "Resize: " << scene->sceneRect().width() << " " << scene->sceneRect().height() << scene->sceneRect().x() << scene->sceneRect().y();
}

string MainWindow::showMessageBox(const string &text, const vector<string> &listQuery, const bool waitResponde)
{
    QMessageBox msgBox;
    msgBox.setText(QString::fromStdString(text));

    if (waitResponde)
    {
        int numQuery = listQuery.size();
        if (numQuery != 0)
        {
            vector <QPushButton *> listButton(numQuery);
            for (int i = 0; i < numQuery; i++) listButton[i] = msgBox.addButton( QString::fromStdString(listQuery[i]), QMessageBox::AcceptRole);
            msgBox.exec();
            for (int i = 0; i < numQuery; i++)
            {
                if (msgBox.clickedButton() == listButton[i]) return listQuery[i];
            }
        }
        msgBox.exec();
        return "";
    }

    QGraphicsTextItem *textItem;
    textItem = scene->addText(QString::fromStdString(text), QFont("Arial", 50) );
    textItem->setPos(500, 500);
    QPropertyAnimation *animation = new QPropertyAnimation(textItem, "pos");
    animation->setDuration(1000);
    animation->setStartValue(textItem->pos());
    animation->setEndValue( textItem->pos().transposed() += QPointF(0, -100) );
    animation->start();
    QObject::connect(animation, &QPropertyAnimation::finished, textItem, &QObject::deleteLater);
    QObject::connect(scene, &QGraphicsScene::changed, ui->graphicsView, &QGraphicsView::updateScene);

    return "";
}

void MainWindow::on_buttonGo_clicked()
{
    /*qint32 resultDice = QRandomGenerator::global()->bounded(6) + 1;
    setDiceImage(resultDice, 0);
    posPiece += resultDice;
    resultDice = QRandomGenerator::global()->bounded(6) + 1;
    setDiceImage(resultDice, 1);*/
    invoker->doCommand(0);

    showMessageBox("You have go", {});
}

void MainWindow::on_buttonBuy_clicked()
{
    invoker->doCommand(2);
}

void MainWindow::on_manageButton_clicked()
{
    QModelIndexList model = ui->listPlayer->selectionModel()->selectedRows(0);
    QModelIndex modelIndexSelected = model.back();
    int idPlayerSelect = modelIndexSelected.data().toInt();

    idChose.clear();
    idChose.push_back( idPlayerSelect );

    PropertyManager *propertyManager = new PropertyManager (this, invoker, scene, gameModel, gameModel->getNameOfIdPlayer(idPlayerSelect));
    propertyManager->setWindowModality(Qt::ApplicationModal);
    propertyManager->setAttribute(Qt::WA_DeleteOnClose);
    propertyManager->show();
}

MainWindow::~MainWindow()
{
    delete MainWindow::scene;
    delete ui;
}

