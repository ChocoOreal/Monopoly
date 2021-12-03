#include "Player.h"
#include "Dice.h"
#include <iostream>


using namespace std;

int main(){
    int cnt[11] = {0};
    for(int i = 0; i < 1e5; ++i){
        cnt[Dice::Rand(1, 10)]++;
    }
    for(int i = 1; i <= 10; ++i){
        cout << cnt[i] << ' ';
    }
}