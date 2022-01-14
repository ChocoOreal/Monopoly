#ifndef ANIMATETEXT_H
#define ANIMATETEXT_H

#include <QObject>
#include <QPropertyAnimation>
#include <QTimer>
#include <QGraphicsTextItem>
#include <queue>

using std::queue;

class MainWindow;

class AnimateText : public QObject
{
    Q_OBJECT

public:
    AnimateText(MainWindow *mainWindow);

    void addText(QGraphicsTextItem *textItem);

private:
    MainWindow *mainWindow;
    std::queue<QPropertyAnimation *> listPendingNotify;
    QTimer* timeUpdate;

private slots:
    void animateNotifyText();

};

#endif // ANIMATETEXT_H
