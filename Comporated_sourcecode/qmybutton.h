#ifndef QMYBUTTON_H
#define QMYBUTTON_H

#include <QObject>

class QMyButton : public QObject
{
    Q_OBJECT
public:
    explicit QMyButton(QObject *parent = nullptr);

signals:

};

#endif // QMYBUTTON_H
