#include "labelinformationplayer.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>
#include "mainwindow.h"

LabelInformationPlayer::LabelInformationPlayer(vector<QWidget *> listLabelPlayer, MainWindow *mainWindow)
{
    LabelInformationPlayer::listLabelPlayer = listLabelPlayer;
    LabelInformationPlayer::mainWindow = mainWindow;

    for (int i = 0; i < listLabelPlayer.size(); i++)
    {
        QHBoxLayout *layout = new QHBoxLayout;
        QVBoxLayout *innerLayout = new QVBoxLayout;
        QLabel *labelName = new QLabel;
        QLabel *labelAvatar = new QLabel;
        QLabel *inTurnLabel = new QLabel;
        QLabel *inCellLabel = new QLabel;

        labelAvatar->setObjectName("labelAvatar");
        labelName->setObjectName("labelName");
        inTurnLabel->setObjectName("labelInTurn");
        inCellLabel->setObjectName("labelCell");

        labelName->setWordWrap(true);
        labelName->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        labelName->setWordWrap(true);
        inTurnLabel->setText("Trong lượt");
        inTurnLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        inTurnLabel->setWordWrap(true);
        inTurnLabel->hide();
        inCellLabel->setText("Đang bị giam");
        inCellLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        inCellLabel->setWordWrap(true);
        inCellLabel->hide();

        innerLayout->addWidget(labelName);
        innerLayout->addWidget(inTurnLabel);
        innerLayout->addWidget(inCellLabel);
        layout->addWidget(labelAvatar);
        layout->addLayout(innerLayout);
        listLabelPlayer[i]->setLayout( layout );

        QString color;
        if (MainWindow::colorOfPlayer[i] == Qt::darkGreen) color = "darkGreen";
        else if (MainWindow::colorOfPlayer[i] == Qt::red) color = "red";
        else if (MainWindow::colorOfPlayer[i] == Qt::blue) color = "blue";
        else if (MainWindow::colorOfPlayer[i] == Qt::yellow) color = "yellow";
        listLabelPlayer[i]->setStyleSheet("background-color: " + color);

        listLabelPlayer[i]->findChild<QLabel *>("labelName")->setStyleSheet("font: bold 15px");
        listLabelPlayer[i]->findChild<QLabel *>("labelInTurn")->setStyleSheet("font: bold 15px");
        listLabelPlayer[i]->findChild<QLabel *>("labelCell")->setStyleSheet("font: bold 15px");
    }
}

int LabelInformationPlayer::getIdOfPlayer(const QString &name)
{
    for (size_t i = 0; i < listLabelPlayer.size(); i++)
    {
        if (listLabelPlayer[i]->findChild<QLabel *>("labelName")->text() == name) return i;
    }

    return -1;
}

void LabelInformationPlayer::setNamePlayer(int idPlayer, QString name)
{
    listLabelPlayer[idPlayer]->findChild<QLabel *>("labelName")->setText(name);
}

void LabelInformationPlayer::setAvatarPlayer(int idPlayer, QString name)
{
    listLabelPlayer[idPlayer]->findChild<QLabel *>("labelAvatar")->setPixmap( QPixmap(name).scaled(50, 50, Qt::KeepAspectRatio) );
    listLabelPlayer[idPlayer]->update();
}

void LabelInformationPlayer::setInTurnPlayer(int idPlayer, bool inTurn)
{
    if (inTurn) listLabelPlayer[idPlayer]->findChild<QLabel *>("labelInTurn")->show(); else
        listLabelPlayer[idPlayer]->findChild<QLabel *>("labelInTurn")->hide();
}

void LabelInformationPlayer::setInCellPlayer(int idPlayer, bool inCell)
{
    if (inCell) listLabelPlayer[idPlayer]->findChild<QLabel *>("labelCell")->show(); else
        listLabelPlayer[idPlayer]->findChild<QLabel *>("labelCell")->hide();
}
