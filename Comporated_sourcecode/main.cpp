#include "mainprogrammanager.h"
#include "RunningGameMode.h"
#include <iostream>

#include <QApplication>

using namespace std;



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    
    //RunningGameMode gameRunning(4);

    MainProgramManager test;
    test.show();

    return a.exec();
}
