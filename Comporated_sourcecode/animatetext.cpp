#include "animatetext.h"
#include "mainwindow.h"

AnimateText::AnimateText(MainWindow *mainWindow)
{
    AnimateText::mainWindow = mainWindow;
    timeUpdate = new QTimer;
    QObject::connect(timeUpdate, &QTimer::timeout, this, &AnimateText::animateNotifyText);
}

void AnimateText::addText(QGraphicsTextItem *textItem)
{
    QPropertyAnimation *animation = new QPropertyAnimation(textItem, "pos");
    animation->setDuration(1000);
    animation->setStartValue(textItem->pos());
    animation->setEndValue( textItem->pos() + QPointF(0, -200) );

    listPendingNotify.push( animation );

    QObject::connect(animation, &QPropertyAnimation::finished, textItem, &QObject::deleteLater);

    timeUpdate->start(500);
}

void AnimateText::animateNotifyText()
{
    QPropertyAnimation *animation = listPendingNotify.front();
    listPendingNotify.pop();
    animation->start();
    if (listPendingNotify.empty() ) timeUpdate->stop();
}
