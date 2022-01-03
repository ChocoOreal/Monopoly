#include "mainwindow.h"
#include "Player.h"
#include "Cell.h"
#include "RunningGameMode.h"
#include <iostream>

#include <QApplication>

using namespace std;

int Player::InstanceCount = 0;
int Railroad::playerOwnerNum[4] = {};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    RunningGameMode gameRunning(4);

    return a.exec();
}
