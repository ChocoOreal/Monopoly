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
    animatetext.cpp \
    cellitem.cpp \
    labelinformationplayer.cpp \
    main.cpp \
    mainScene.cpp \
    mainprogrammanager.cpp \
    mainwindow.cpp \
    mymodelview.cpp \
    playersetupmanager.cpp \
    propertymanager.cpp \
    settingrule.cpp \
    setuprule.cpp

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
    animatetext.h \
    cellitem.h \
    gamecomponents.h \
    labelinformationplayer.h \
    mainScene.h \
    mainprogrammanager.h \
    mainwindow.h \
    mymodelview.h \
    playersetupmanager.h \
    propertymanager.h \
    settingrule.h \
    setuprule.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    mainprogrammanager.ui \
    mainwindow.ui \
    playersetupmanager.ui \
    propertymanager.ui \
    setuprule.ui

RESOURCES += \
    resources.qrc
