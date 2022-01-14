#ifndef SETUPRULE_H
#define SETUPRULE_H

#include <QMainWindow>
#include <settingrule.h>

namespace Ui {
class SetupRule;
}

class SetupRule : public QMainWindow
{
    Q_OBJECT

public:
    explicit SetupRule(SettingRule *settingRule, QWidget *parent = nullptr);
    ~SetupRule();

private slots:
    void on_pushButton_clicked();

private:
    Ui::SetupRule *ui;

    int translateParkOp();
    int translatePassGoOp();
    int translateInGoOp();
    int transelateStartOp();

    SettingRule *curSettingRule;
};

#endif // SETUPRULE_H
