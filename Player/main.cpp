#include "Player.h"
#include <iostream>
using namespace std;

int main(){
    Player A(10, false, 0, "Nguyen Van A", "Avatar");
    A.earnMoney(200);
    cout << "Current player money = " << A.Money() << '\n';
    cout << "Current player name = " << A.Name() << '\n';
    cout << "Current player Avatar path = " << A.Avatar() << '\n';
    cout << "Current Player position = " << A.Position() << '\n';
}