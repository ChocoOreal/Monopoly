QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Cell.cpp \
    Command.cpp \
    CommandHandler.cpp \
    Game.cpp \
    Player.cpp \
    RunningGameMode.cpp \
    Util.cpp \
    cellitem.cpp \
    main.cpp \
    mainScene.cpp \
    mainwindow.cpp \
    mymodelview.cpp \
    propertymanager.cpp \
    qmybutton.cpp

HEADERS += \
    Cell.h \
    Command.h \
    CommandHandler.h \
    Dice.h \
    Game.h \
    IGame.h \
    Player.h \
    RunningGameMode.h \
    Util.h \
    cellitem.h \
    mainScene.h \
    mainwindow.h \
    mymodelview.h \
    propertymanager.h \
    qmybutton.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    Welcome.ui \
    mainwindow.ui \
    propertymanager.ui

RESOURCES += \
    resources.qrc
