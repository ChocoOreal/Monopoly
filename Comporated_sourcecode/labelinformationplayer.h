#ifndef LABELINFORMATIONPLAYER_H
#define LABELINFORMATIONPLAYER_H

#include <QObject>
#include <vector>

using std::vector;

class MainWindow;

class LabelInformationPlayer
{
private:
    MainWindow *mainWindow;
    vector <QWidget *> listLabelPlayer;

public:
    LabelInformationPlayer(vector<QWidget *> listLabelPlayer, MainWindow* mainWindow);

    int getIdOfPlayer(const QString &name);

public slots:
    void setAvatarPlayer(int idPlayer, QString nameImage);
    void setNamePlayer(int idPlayer, QString name);
    void setInTurnPlayer(int idPlayer, bool inTurn);
    void setInCellPlayer(int idPlayer, bool inCell);
};

#endif // LABELINFORMATIONPLAYER_H
