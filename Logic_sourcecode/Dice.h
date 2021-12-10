#pragma once
#include <iostream>
#include <random>

using namespace std;

static random_device rd; // obtain a random number from hardware
static mt19937 gen(rd()); // seed the generator

class Dice{
public:
    static int Rand(int low, int high){
        uniform_int_distribution<> distr(low, high);
        return distr(gen);
    }
};