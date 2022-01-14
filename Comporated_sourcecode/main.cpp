#include "mainprogrammanager.h"
#include "RunningGameMode.h"
#include <iostream>

#include <QApplication>

using namespace std;



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    srand(time(0));
    //RunningGameMode gameRunning(4);

    MainProgramManager test;
    test.show();

    return a.exec();
}
