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
        Cell (const string &infomation) ;

        static void setInterfaceGame(IGame* iGame) { Cell::iGame = iGame; } //Set interface for Cell later
        int getID() { return ID; } //Need ID of cell since we need assign Cell pointer to right position in _listCell vector
        string getName() { return _name; }

        virtual vector<string> toString();
        virtual void bankruptThisCell(int idPlayer, int idCreditor);

        virtual void activateCell(int idPlayer) = 0;

        virtual ~Cell();
};

class Card: public Cell {

    private:
        static string luckyCard[10];
        static string chancesCard[10];
        static string currentCard;

    public:
        Card(const string &information);

        void drawCard ();

        void activateCell(int idPlayer);
        vector <string> toString();

        ~Card();
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
        RealEstate(const string &information);

        void mortgage(int &money);
        void redeem(int &money);
        void activateCell(int idPlayer);
        void bankruptThisCell(int idPlayer, int idCreditor);
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

        ~RealEstate() {}
};

class NormalLand: public RealEstate {

    private:    
        int _numberOfHouse;
        int _numberOfHotel;
        int _housePrice;
        float _COEFFICIENT;

    public:
        NormalLand();
        NormalLand(const string &information);

        void build(int &price);
        void sellHouse(int &money);
        void rent(int &money) { money = _rentPrice; }
        void bankruptThisCell(int idPlayer, int creditor);
        
        ~NormalLand() {}
        vector<string> toString();
};

class Factory : public RealEstate
{

    private:
        bool isSameOwner = false;

    public:
        Factory() : RealEstate() {};
        Factory(const string &information) : RealEstate(information) {};

        void rent(int &money);
};

class Railroad: public RealEstate {

    private:
        static int playerOwnerNum[4]; //nguoi choi co id i so huu so manh dat playerOwnerNum[i] 

    public:
        Railroad() : RealEstate() {};
        Railroad(const string &information) : RealEstate(information) {};

        void rent(int &money);
        virtual void buyLand(int idPlayer, int &price);

        ~Railroad();

};

class Go : public Cell {

    public:
        Go(){}
        Go (const string &information): Cell (information){}

        void passGoCell(int idPlayer);

        void activateCell(int idPlayer);
        vector<string> toString();
};

class PayTax : public Cell {

    public:
        PayTax(){}
        PayTax(const string &infomation):Cell (infomation){}

        void activateCell (int idPlayer);
        vector<string> toString();     
} ;

class GoToJail : public Cell {

    public:
        GoToJail(){}
        GoToJail(const string &information): Cell (information){}

        void activateCell (int idPlayer);
        vector<string> toString();
};

class JailCell : public Cell {

    private:
        static int numberRollDice[4];

    public:
        JailCell(const string &information) : Cell (information){}

        void activateCell(int idPlayer);
        vector<string> toString();

        ~JailCell();
};

class Park : public Cell
{
    public:
        Park(const string &information) : Cell (information){}

        void activateCell(int idPlayer);
        vector<string> toString();
};
