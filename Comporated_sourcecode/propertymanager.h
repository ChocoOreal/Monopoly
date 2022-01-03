#ifndef PROPERTYMANAGER_H
#define PROPERTYMANAGER_H

#include <QMainWindow>

class MainWindow;
class MainScene;
class CommandHandler;
class myModelView;

namespace Ui {
class PropertyManager;
}

class PropertyManager : public QMainWindow
{
    Q_OBJECT

public:
    explicit PropertyManager(MainWindow*, CommandHandler*, MainScene*, myModelView*, QWidget *parent = nullptr);
    ~PropertyManager();


private:
    Ui::PropertyManager *ui;
    MainWindow *mainWindow;
    CommandHandler *invoker;
    MainScene *mainScene;
    myModelView *modelData;

    void showEvent(QShowEvent *event);
    void resizeEvent(QResizeEvent *event);
};

#endif // PROPERTYMANAGER_H
