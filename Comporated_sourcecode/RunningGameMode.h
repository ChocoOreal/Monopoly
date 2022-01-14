#ifndef RUNNINGGAMEMODE_H
#define RUNNINGGAMEMODE_H

#include <QObject>
#include <vector>
#include <string>

using std::vector; using std::string;

class MainWindow;
class CommandHandler;
class Game;
class SettingRule;

class RunningGameMode : public QObject
{
    Q_OBJECT;

    private:
        MainWindow *mainWindow;
        CommandHandler *invoker;
        Game *game;
        SettingRule *curSettingRule;

    public:
        RunningGameMode();
        RunningGameMode(int numPlayer, vector< vector<string> >, SettingRule *curSettingRule); //In fact this will be a config class contain setting used in a game
        ~RunningGameMode();

        void notifyGameOver();

        CommandHandler *getCommandHandler();

    signals:
        void gameOver();
        void showSetting();

    private slots:
        void receiveShowSettingRequest();
};

#endif
