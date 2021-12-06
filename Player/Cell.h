#pragma once
#include "Dice.h"
#include "Player.h"
#include <string>

#include <sstream>
#define COEFFICIENT 1.2
using namespace std;


class Cell {
public:
    //virtual bool Mortgage() = 0;
    //virtual int buildHouse() = 0;
    //virtual int buildHotel() = 0;
    //virtual int buyLand() = 0;
    Cell(){}
    virtual string toString() const = 0;
    virtual ~Cell() {};
    //virtual int rent();
};

class Card: public Cell {
private:
    string luckyCard[10];
    string chancesCard[10];
    string currentCard;

public:
    Card();
    void drawCard (string& info, int& amnt, int& type);
    string toString() const {return currentCard;};
    ~Card() {};
};


class NormalLand: public Cell {
private:
    int _buyPrice;
    int _rentPrice;
    bool _isMortgage;
    string _information;
    int _numberOfHouse;
    int _numberOfHotel;
    short _Owner;
    int _housePrice;
public:
    NormalLand();
    NormalLand(string information);
    int buildHouse();
    int buildHotel();
    bool Mortgage();
    int buyLand(Player* player);
    int rent();
    int sellHouse();
    string toString() const {return _information;}
    ~NormalLand() {}
};