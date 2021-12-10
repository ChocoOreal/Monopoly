#pragma once
#include "Dice.h"
#include "Player.h"
#include <string>

#include <sstream>
#define COEFFICIENT 1.2
#define HOTELCOEFFICIENT 1.5
using namespace std;

class Cell {
public:
    Cell(){}
    virtual string toString() const = 0;
    virtual ~Cell() {};
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

class RealEstate: public Cell {
protected:
    int _buyPrice;
    int _rentPrice;
    bool _isMortgage;
    string _information;
    short _owner;
public:
    RealEstate();
    RealEstate(string information);
    virtual bool Mortgage(int& amnt);
    int buyLand(Player* player);
    virtual int rent(short& receiver);
    string toString() const {return _information;}
    ~RealEstate() {}
    

};

class NormalLand: public RealEstate {
private:
    
    int _numberOfHouse;
    int _numberOfHotel;
    
    int _housePrice;
public:
    NormalLand();
    NormalLand(string information);
    int build();
    bool Mortgage(int& amnt);
    int sellHouse();
    ~NormalLand() {}
};

class Factory: public RealEstate {

public:
    Factory():RealEstate(){};
    Factory(string information):RealEstate(information){};
    int rent(short& receiver);
};

class Railroad: public RealEstate {
private:
    static int playerOwnerNum[4]; //nguoi choi co id i so huu so manh dat playerOwnerNum[i] 
public:
    Railroad():RealEstate() {}
    Railroad(string information):RealEstate(information){};
    int rent(short& receiver);
};