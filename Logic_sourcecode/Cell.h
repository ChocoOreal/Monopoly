#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <iostream>

class IGame;
class Util;

using std::string;
using std::vector;

#define COEFFICIENT 1.2
#define HOTELCOEFFICIENT 1.5
#define START_MONEY_AMOUNT 200
#define TAX 200

class Cell {

    protected:
        static IGame *iGame; //This is the property which is used by all other Cell objects
        string _typeName;
        int ID;
        string _name;
        string _description;
        vector<string> _rawInfo;

    public:
        Cell(){}
        Cell (string infomation) ;

        static void setInterfaceGame(IGame* iGame) { Cell::iGame = iGame; } //Set interface for Cell later
        int getID() { return ID; } //Need ID of cell since we need assign Cell pointer to right position in _listCell vector

        virtual vector<string> toString() {};
        virtual void activateCell(int idPlayer) {};

        virtual ~Cell() {};
};

class Card: public Cell {

    private:
        string luckyCard[10];
        string chancesCard[10];
        string currentCard;

    public:
        Card();

        void drawCard ();

        void activateCell(int idPlayer);
        vector <string> toString();

        virtual ~Card() {}
};

class RealEstate: public Cell {

    protected:
        int _buyPrice;
        int _rentPrice; //The rentPrice at current time. This is different from raw _rentPrice which is initialized at the begining
        bool _isMortgage;
        short _owner;
        int _mortgagePrice;

    public:
        RealEstate();
        RealEstate(string information);

        void mortgage(int &money);
        void activateCell(int idPlayer);
        virtual void buyLand(int idPlayer, int &price);


        //when player steps into real estate cells, auto trigger this function
        //var money is a reference so that it can return pay amount if that player is not the owner
        //use tranfer function of class Game to transfer pay amount between
        //the owner and the guest
        virtual void rent(int &money) {};

        //return a vector of strings containing attribute information of cells
        //if the cell doesnt have a certain attribute, that lacking attribute will be stored as " " (space character)
        //attribute which has boolean type will be saved as a string of "true" or "false"
        virtual vector<string> toString();

        virtual ~RealEstate() {}
};

class NormalLand: public RealEstate {

    private:    
        int _numberOfHouse;
        int _numberOfHotel;
        int _housePrice;
        float _COEFFICIENT;

    public:
        NormalLand();
        NormalLand(string information);

        void build(int &price);
        void sellHouse(int &money);
        void rent(int &money) {money = _rentPrice * _COEFFICIENT;}
        
        virtual ~NormalLand() {}
        vector<string> toString();
};

class Factory : public RealEstate
{

    private:
        bool isSameOwner = false;

    public:
        Factory() : RealEstate() {};
        Factory(string information) : RealEstate(information) {};
        ~Factory() {}
        void rent(int &money);
};

class Railroad: public RealEstate {

    private:
        static int playerOwnerNum[4]; //nguoi choi co id i so huu so manh dat playerOwnerNum[i] 

    public:
        Railroad() : RealEstate() {};
        Railroad(string information) : RealEstate(information) {};
        virtual ~Railroad() {}
        void rent(int &money);
        virtual void buyLand(int idPlayer, int &price);

};

class Go : public Cell {

    public:
        Go(): Cell(){}
        Go (string information): Cell (information){}

        virtual ~Go() {}
        // chưa làm gì cả..
        void activateCell(int idPlayer);
        vector<string> toString();
};

class PayTax : public Cell {

    public:
        PayTax() {}
        PayTax(string infomation):Cell (infomation){}
        virtual ~PayTax() {}
        // chưa làm gì cả
        void activateCell (int idPlayer);
        vector<string> toString();
        
} ;

class GoToJail : public Cell {

    public:
        GoToJail(){}
        GoToJail(string information): Cell (information){}
        virtual ~GoToJail() {}
        // chưa làm gì cả
        void activateCell (int idPlayer);
        vector<string> toString();
};

class JailCell : public Cell {
    public:
        /**
         * should add something in here though
         */
        JailCell(): Cell(){}
        JailCell(string information): Cell (information){}
        virtual ~JailCell() {}
        void activateCell (int idPlayer) {}
        vector<string> toString() {}
        
};
