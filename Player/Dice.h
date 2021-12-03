#include <iostream>

using namespace std;

class Dice{
public:
    static int Rand() {
        return rand();
    }
    static int Rand(int n){
        
        return rand() % n;
    }
    static int Rand(int low, int high){
        return (rand() % (high - low + 1)) + low;
    }
};