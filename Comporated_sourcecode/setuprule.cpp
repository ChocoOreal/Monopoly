#include "setuprule.h"
#include "ui_setuprule.h"

class SettingRule;

SetupRule::SetupRule(SettingRule *setting, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SetupRule)
{
    ui->setupUi(this);
    curSettingRule = setting;

    ui->comboBox->setCurrentIndex( setting->getParkOp() );
    ui->comboBox_2->setCurrentIndex( setting->getPassGoOp() );
    ui->comboBox_3->setCurrentIndex( setting->getParkOp() );
    ui->comboBox_4->setCurrentIndex( setting->getStartOp() );
}

SetupRule::~SetupRule()
{
    delete ui;
}

int SetupRule::translateParkOp()
{
    if (ui->comboBox->currentText() == "Miễn phí") return 0; else return 1;
}

int SetupRule::translatePassGoOp()
{
    if (ui->comboBox_2->currentText() == "Không có") return 0;
    else if (ui->comboBox_2->currentText() == "200") return 1;
    else return 2;
}

int SetupRule::translateInGoOp()
{
    if (ui->comboBox_3->currentText() == "Bình thường") return 0;
    else return 1;
}

int SetupRule::transelateStartOp()
{
    if (ui->comboBox_4->currentText() == "1000") return 0;
    else if (ui->comboBox_4->currentText() == "1500") return 1;
    else return 2;
}

void SetupRule::on_pushButton_clicked()
{
    curSettingRule->setSettingRule( translateParkOp(), translatePassGoOp(), translateInGoOp(), transelateStartOp() );

    this->close();
}

