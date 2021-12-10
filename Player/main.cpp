#include "Player.h"
#include "Dice.h"
#include <iostream>

#include "Cell.h"
using namespace std;
/*
int main(){
    int cnt[11] = {0};
    for(int i = 0; i < 1e5; ++i){
        cnt[Dice::Rand(1, 10)]++;
    }
    for(int i = 1; i <= 10; ++i){
        cout << cnt[i] << ' ';
    }
}*/
int Player::InstanceCount = 0;
int main () {
    int ID = 1;
    Player A(1000, false, 3, "Player A", "");
    A.setID(ID);
    cout << A.toString() << '\n';

    getchar();

    Card c;
    string info;
    int amount;
    int type;
    c.drawCard(info, amount, type);
    cout << info << '\n';

    getchar();

    if (type == 1) A.changeMoney(amount); else A.setPosition( A.Position() + amount );
    cout << A.toString() << '\n';
}