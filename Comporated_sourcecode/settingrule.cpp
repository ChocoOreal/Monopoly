#include "settingrule.h"

SettingRule::SettingRule()
{
    parkOp = 0;
    passGoOp = 1;
    inGoOp = 0;
    startOp = 2;
}

void SettingRule::setSettingRule(int parkOp, int passGoOp, int inGoOp, int startOp)
{
    SettingRule::parkOp = parkOp;
    SettingRule::passGoOp = passGoOp;
    SettingRule::inGoOp = inGoOp;
    SettingRule::startOp = startOp;
}
