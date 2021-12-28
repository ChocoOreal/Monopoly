#include "Cell.h"
#include "Dice.h"
#include "IGame.h"
#include "Util.h"
#include <string>
#include <sstream>

using std::string; using std::stringstream;

Card::Card() {
    luckyCard[0] = "@ Vuot den do, phat 200 dong @ -200";
    luckyCard[1] = "@ Vuot den do, phat 200 dong @ -200";
    luckyCard[2] = "@ Vuot den do, phat 200 dong @ -200";
    luckyCard[3] = "@ Vuot den do, phat 200 dong @ -200";
    luckyCard[4] = "@ Vuot den do, phat 200 dong @ -200";
    luckyCard[5] = "@ Vuot den do, phat 200 dong @ -200";
    luckyCard[6] = "@ Vuot den do, phat 200 dong @ -200";
    luckyCard[7] = "@ Vuot den do, phat 200 dong @ -200";
    luckyCard[8] = "@ Vuot den do, phat 200 dong @ -200";
    luckyCard[9] = "@ Vuot den do, phat 200 dong @ -200";
    chancesCard[0] = "@ Dang truoc co tai nan giao thong, lui 2 buoc @ -2";
    chancesCard[1] = "@ Dang truoc co tai nan giao thong, lui 2 buoc @ -2";
    chancesCard[2] = "@ Dang truoc co tai nan giao thong, lui 2 buoc @ -2";
    chancesCard[3] = "@ Dang truoc co tai nan giao thong, lui 2 buoc @ -2";
    chancesCard[4] = "@ Dang truoc co tai nan giao thong, lui 2 buoc @ -2";
    chancesCard[5] = "@ Dang truoc co tai nan giao thong, lui 2 buoc @ -2";
    chancesCard[6] = "@ Dang truoc co tai nan giao thong, lui 2 buoc @ -2";
    chancesCard[7] = "@ Dang truoc co tai nan giao thong, lui 2 buoc @ -2";
    chancesCard[8] = "@ Dang truoc co tai nan giao thong, lui 2 buoc @ -2";
    chancesCard[9] = "@ Dang truoc co tai nan giao thong, lui 2 buoc @ -2";
    currentCard = "";
}

void Card::drawCard (string& info, int& amnt) {

    //@ chu tren the @ gia tri cua the (duong hoac am)\n
    int type = Dice::Rand(1, 2);
    int i = Dice::Rand(1, 6);//random
    
    string card;
    if (type == 1) {
        card = luckyCard[i];
    }
    else {
        card = chancesCard[i];
    }
    vector <string> tokens = Util::parse(card, " @ ", 2);
    stringstream ss (tokens[1]);
    ss >> amnt;
    info = tokens[0];
}

/* 
    RealEstate implement
*/

RealEstate::RealEstate() {
    _buyPrice = 0;
    _rentPrice = 0;
    _isMortgage = 0;
    _information = "";
    _owner = -1;
}

void RealEstate::activateCell(int idPlayer)
{
    if (_owner == 0) return;
    if (_isMortgage) return;
    if (_owner == idPlayer)
    {
        int price;
        this->rent(price);
        iGame->transferMoney(idPlayer, _owner, price);
    }
}

void RealEstate::mortgage(int &money) {
    _isMortgage = true;
    money = _buyPrice / 2;
}

void RealEstate::buyLand(int idPlayer, int &price) {
    _owner = idPlayer;
    price = _buyPrice;
}

/*
    NormalLand implement
*/

void NormalLand::sellHouse(int &money) {
    _numberOfHouse--;
    _rentPrice /= COEFFICIENT;
    money = _buyPrice / 2;
}

void NormalLand::build(int &price) {
    if (_numberOfHouse < 4) {
        _numberOfHouse++;
        _rentPrice *= COEFFICIENT;
    }
    else {
        //xuat ra dong "Da co du 4 nha, can nang cap len khach san"
        //neu nguoi choi dong y nang cap thi reset so nha, doi gia thue, tang so khach san
        _numberOfHouse = 0;
        _numberOfHotel = 1;
        _rentPrice = HOTELCOEFFICIENT;
    }
    
    price = _housePrice;
}

//information doc tu file luc initialize
NormalLand::NormalLand(string information): RealEstate(){
    // "@ chu tren the @ gia mua dat @ gia thue @ gia nha"
    vector<string> tokens = Util::parse(information, " @ ", 2);
    _information = tokens[0];
    stringstream ss1 (tokens[1]);
    ss1 >> _buyPrice;
    stringstream ss2 (tokens[2]);
    ss2 >> _rentPrice;
    stringstream ss3 (tokens[3]);
    ss3 >> _housePrice; 
}

/*

    Railroad implement

*/

void Railroad::rent(int &money) {
    money = _rentPrice * (int)pow(2, playerOwnerNum[_owner] - 1);
}

/*

    Factory implement

*/

//this is the true rent price, not real rent price (does not include value of dice in resulting value)
void Factory::rent(int &money) {
    if (isSameOwner) money = 10 * iGame->getDice() ; else money = 4 * iGame->getDice(); //FUNCTION GET DICE OF GAME CLASS
}

RealEstate::RealEstate(string information) {
    //@ thong tin @ gia mua @ gia thue
    string separator = " @ ";
    vector<string> tokens = Util::parse(information, separator, 2);
    stringstream ss1 (tokens[1]);
    stringstream ss2 (tokens[2]);
    ss1 >> _buyPrice;
    ss2 >> _rentPrice;
    _owner = -1;
    _information = tokens[0];
    _isMortgage = false;
    _owner = -1;
}

/*
    Go class implementation
*/
void Go::activateCell(int idPlayer, int& moneyAmount) {
    moneyAmount = _startMoney;
}


//Sau nay phai sua cho nay
Go::Go() {
    _information = "Thong tin cho o bat dau";
    _startMoney = START_MONEY_AMOUNT;
}


/*

    PayTax class implementation

*/


PayTax::PayTax() {
    _information = "Thong tin cua the"; //can sua sau
    _tax = TAX;
}

void PayTax::activateCell(int idPlayer, int& moneyAmount) {
    moneyAmount = _tax;
}