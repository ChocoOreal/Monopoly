#ifndef PLAYERSETUPMANAGER_H
#define PLAYERSETUPMANAGER_H

#include <QMainWindow>
#include <QMenu>
#include <QComboBox>
#include <vector>

using std::vector;

namespace Ui {
class PlayerSetupManager;
}

class PlayerSetupManager : public QMainWindow
{
    Q_OBJECT

public:
    explicit PlayerSetupManager(QWidget *parent = nullptr);
    ~PlayerSetupManager();

    vector<QString> getPlayerInformation(int idPlayer);

signals:
    void startGame(vector< vector<QString> > playerInformation);

private slots:
    void on_checkBox2_stateChanged(int arg1);

    void on_checkBox3_stateChanged(int arg1);

    void on_checkBox4_stateChanged(int arg1);

    void on_startButton_clicked();

    void on_backButton_clicked();

private:
    Ui::PlayerSetupManager *ui;
    QMenu listPieces;
    vector <QComboBox*> listComboBox;
};

#endif // PLAYERSETUPMANAGER_H
