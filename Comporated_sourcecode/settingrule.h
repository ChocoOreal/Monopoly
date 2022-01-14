#ifndef SETTINGRULE_H
#define SETTINGRULE_H


class SettingRule
{
public:
    SettingRule();

private:
    int parkOp;
    int passGoOp;
    int inGoOp;
    int startOp;

public:
    void setSettingRule( int parkOp, int passGoOp, int inGoOp, int startOp );
    int getParkOp() { return parkOp; }
    int getPassGoOp() { return passGoOp; }
    int getInGoOp() { return inGoOp; }
    int getStartOp() { return startOp; }
};

#endif // SETTINGRULE_H
