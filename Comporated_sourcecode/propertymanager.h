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
    explicit PropertyManager(MainWindow*, CommandHandler*, MainScene*, myModelView*, QString, QWidget *parent = nullptr);
    ~PropertyManager();


private slots:
    void on_buildButton_clicked();
    void on_sellButton_clicked();
    void on_mortgageButton_clicked();
    void on_redeemButton_clicked();
    void on_exitButton_clicked();
    void on_confirmButton_clicked();
    void on_backButton_clicked();
    void on_listProperty_clicked(const QModelIndex& index);

private:
    Ui::PropertyManager *ui;
    MainWindow *mainWindow;
    CommandHandler *invoker;
    MainScene *mainScene;
    myModelView *modelData;
    QString modeSelected, playerDoTask;

    void modeButtons(int mode);
    void showCellInfo(int idCell);

    void showEvent(QShowEvent *event);
    void resizeEvent(QResizeEvent *event);
};

#endif // PROPERTYMANAGER_H
