#include "playersetupmanager.h"
#include "ui_playersetupmanager.h"
#include <vector>
#include <QString>
#include <QIcon>

using std::vector;

PlayerSetupManager::PlayerSetupManager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PlayerSetupManager)
{
    ui->setupUi(this);

    listComboBox.push_back(ui->comboBox1); listComboBox.push_back(ui->comboBox2);
    listComboBox.push_back(ui->comboBox3); listComboBox.push_back(ui->comboBox4);

    QIcon tmp1("Image/barrow"); QIcon tmp2("Image/car"); QIcon tmp3("Image/dog"); QIcon tmp4("Image/dragon");
    for (size_t i = 0; i < listComboBox.size(); i++)
    {
        listComboBox[i]->addItem(tmp1, "Xe cút kít");
        listComboBox[i]->addItem(tmp2, "Larmborgini");
        listComboBox[i]->addItem(tmp3, "Thịt cầy di động");
        listComboBox[i]->addItem(tmp4, "Rồng trắng mắt xanh");
    }

    ui->checkBox2->setChecked(true); ui->checkBox2->setChecked(false);
    ui->checkBox3->setChecked(true); ui->checkBox3->setChecked(false);
    ui->checkBox4->setChecked(true); ui->checkBox4->setChecked(false);
}

PlayerSetupManager::~PlayerSetupManager()
{
    delete ui;
}

void PlayerSetupManager::on_checkBox2_stateChanged(int arg1)
{
    ui->lineEdit2->setEnabled(arg1);
    ui->comboBox2->setEnabled(arg1);
}


void PlayerSetupManager::on_checkBox3_stateChanged(int arg1)
{
    ui->lineEdit3->setEnabled(arg1);
    ui->comboBox3->setEnabled(arg1);
}


void PlayerSetupManager::on_checkBox4_stateChanged(int arg1)
{
    ui->lineEdit4->setEnabled(arg1);
    ui->comboBox4->setEnabled(arg1);
}

void PlayerSetupManager::on_startButton_clicked()
{
    vector< vector<QString> > playerInformation;
    vector<QString> tmp;

    tmp.push_back(ui->lineEdit1->text()); tmp.push_back(ui->comboBox1->currentText()); playerInformation.push_back(tmp);
    tmp.clear();
    if (ui->checkBox2->isChecked())
    {
        tmp.push_back(ui->lineEdit2->text()); tmp.push_back(ui->comboBox2->currentText()); playerInformation.push_back(tmp);
        tmp.clear();
    }
    if (ui->checkBox3->isChecked())
    {
        tmp.push_back(ui->lineEdit3->text()); tmp.push_back(ui->comboBox3->currentText()); playerInformation.push_back(tmp);
        tmp.clear();
    }
    if (ui->checkBox4->isChecked())
    {
        tmp.push_back(ui->lineEdit4->text()); tmp.push_back(ui->comboBox4->currentText()); playerInformation.push_back(tmp);
        tmp.clear();
    }

    emit startGame(playerInformation);

    this->close();
}


void PlayerSetupManager::on_backButton_clicked()
{
    this->close();
}

