#pragma once

#include <string>
#include <sstream>

class IGame;

using std::string;

#define COEFFICIENT 1.2
#define HOTELCOEFFICIENT 1.5

class Cell {

    public:
        virtual string toString() = 0;
        virtual void activateCell(int idPlayer) = 0;

        virtual ~Cell() {};
};

class Card: public Cell {

    private:
        IGame *iGame;
        string luckyCard[10];
        string chancesCard[10];
        string currentCard;

    public:
        Card();

        void drawCard (string& info, int amnt, int type);

        string toString() { return currentCard; }
        void activateCell(int idPlayer) {};
        
        ~Card() {}
};

class RealEstate: public Cell {

    protected:
        IGame *iGame;
        int _buyPrice;
        int _rentPrice;
        bool _isMortgage;
        short _owner;
        string _information;
        
    public:
        RealEstate();
        RealEstate(string information);

        void mortgage(int &money);
        
        string toString() { return _information; }
        void activateCell(int idPlayer);

        virtual void buyLand(int idPlayer, int &price);
        virtual void rent(int &price) {};

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

        void build(int &price);
        void sellHouse(int &money);

        void rent(int &price) {};
        
        ~NormalLand() {}
};

class Factory: public RealEstate {

    private:
        bool isSameOwner = false;

    public:
        Factory() : RealEstate() {};
        Factory(string information) : RealEstate(information) {};
        
        void rent(int &money);
};

class Railroad: public RealEstate {

    private:
        static int playerOwnerNum[4]; //nguoi choi co id i so huu so manh dat playerOwnerNum[i] 

    public:
        Railroad() : RealEstate() {};
        Railroad(string information) : RealEstate(information) {};

        void rent(int &money);
};

class Go : public Cell {};
class PayTax : public Cell {};
class GoToJail : public Cell {};
class JailCell : public Cell {};