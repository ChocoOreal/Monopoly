#include "mainwindow.h"
#include <sstream>
#include <fstream>
#include <locale>
#include <codecvt>
#include <windows.h>
#include <iostream>

#include <QApplication>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
