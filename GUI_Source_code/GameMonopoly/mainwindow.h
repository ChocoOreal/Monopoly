#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mainScene.h"
#include "cellitem.h"
#include <QDebug>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QRandomGenerator>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    void setupMainScene();
    void setupCell();
    void setDiceImage(QGraphicsPixmapItem *&dice, int number, int idDice);
    void setPiece(QGraphicsPixmapItem *&piece, int idCell);

    void showEvent(QShowEvent *event);
    void resizeEvent(QResizeEvent *event);

    ~MainWindow();

private:
    Ui::MainWindow *ui;
    MainScene *scene;
    CellItem *cellItem[41];
    QGraphicsPixmapItem *board;
    QGraphicsPixmapItem *dice1 = nullptr;
    QGraphicsPixmapItem *dice2 = nullptr;
    QGraphicsPixmapItem *piece = nullptr;

    int posPiece = 1;

private slots:
    void on_buttonGo_clicked();
};
#endif // MAINWINDOW_H
