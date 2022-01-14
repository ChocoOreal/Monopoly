#ifndef MAINPROGRAMMANAGER_H
#define MAINPROGRAMMANAGER_H

#include <QMainWindow>
#include <vector>

using std::vector;

class PlayerSetupManager;
class RunningGameMode;
class SetupRule;
class SettingRule;

namespace Ui {
class MainProgramManager;
}

class MainProgramManager : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainProgramManager(QWidget *parent = nullptr);
    ~MainProgramManager();

private slots:
    void on_startGameButton_clicked();
    void on_settingButton_clicked();
    void createAGame(vector < vector<QString> > playerInformation);
    void destroyOldGame();

    void on_exitButton_clicked();

private:
    Ui::MainProgramManager *ui;

    PlayerSetupManager *playerSetupManager = nullptr;
    RunningGameMode *gameRunningMode = nullptr;
    SettingRule *curSettingRule = nullptr;
};

#endif // MAINPROGRAMMANAGER_H
