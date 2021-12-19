#pragma once

#include <iostream>
#include <random>

static std::random_device rd; // obtain a random number from hardware
static std::mt19937 gen(rd()); // seed the generator

class Dice{

    public:
        static int Rand(int low, int high) {
            std::uniform_int_distribution<> distr(low, high);
            return distr(gen);
        }
};