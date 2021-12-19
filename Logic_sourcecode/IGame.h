#ifndef IGAME_H
#define IGAME_H

#include <string>
#include <vector>

using std::string;
using std::vector;

class IGame
{
    public:
        virtual void rollDice() = 0;
        virtual int getDice() = 0;
        virtual void transferMoney(int idPlayerFrom, int idPlayerTo) = 0;
        virtual void notify(string text, vector <string> listQuery) = 0;
};

#endif