#include "Cell.h"
#include "Dice.h"
#include "IGame.h"
#include "Util.h"
#include <string>
#include <sstream>

using std::string; using std::stringstream;

IGame* Cell::iGame = nullptr;

Cell::Cell (string infomation) {
    _rawInfo = Util::parse(infomation, " @ ", 0);
    ID = std::stoi (_rawInfo[0]);
    _typeName = _rawInfo[1];
    _name = _rawInfo[2];
    _description = _rawInfo[3];
}

Card::Card() {
    luckyCard[0] = "Tien @ Vuot den do, phat 200 dong @ -200";
    luckyCard[1] = "@ Vuot den do, phat 200 dong @ -200";
    luckyCard[2] = "@ Vuot den do, phat 200 dong @ -200";
    luckyCard[3] = "@ Vuot den do, phat 200 dong @ -200";
    luckyCard[4] = "@ Vuot den do, phat 200 dong @ -200";
    luckyCard[5] = "@ Vuot den do, phat 200 dong @ -200";
    luckyCard[6] = "@ Vuot den do, phat 200 dong @ -200";
    luckyCard[7] = "@ Vuot den do, phat 200 dong @ -200";
    luckyCard[8] = "@ Vuot den do, phat 200 dong @ -200";
    luckyCard[9] = "@ Vuot den do, phat 200 dong @ -200";
    chancesCard[0] = "Vi tri @ Dang truoc co tai nan giao thong, lui 2 buoc @ -2";
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

void Card::drawCard () {

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
    currentCard = card;
}

void Card::activateCell(int idPlayer) {
    drawCard();
    vector<string> temp = Util::parse(currentCard, " @ ", 0);
    if (temp[0] == "Tien")iGame -> transferMoney(idPlayer, 0, stoi (temp[2]));
    else iGame -> movePlayer(idPlayer, stoi (temp[2]));
    iGame -> notifyChange("player", idPlayer);
}

vector<string> Card::toString() {}

/* 
    RealEstate implement
*/

RealEstate::RealEstate() {
    _buyPrice = 0;
    _rentPrice = 0;
    _isMortgage = 0;
    _owner = -1;
    _mortgagePrice = 0;
}

RealEstate::RealEstate(string information):Cell (information) {
    //@ thong tin @ gia mua @ gia thue
    
    _owner = -1;
    _buyPrice = std::stoi(_rawInfo[4]);
    _rentPrice = std::stoi (_rawInfo[5]);
    _mortgagePrice = std::stoi (_rawInfo[8]);
    _isMortgage = false;
    _owner = -1;
}

void RealEstate::activateCell(int idPlayer)
{
    if (_owner == 0) return;
    if (_isMortgage) return;
    if (_owner != idPlayer)
    {
        int price;
        this->rent(price);
        iGame->transferMoney(idPlayer, _owner, price);
    }
}

void RealEstate::mortgage(int &money) {
    _isMortgage = true;
    money = _mortgagePrice;
    iGame -> notifyChange("cell", ID);
}

void RealEstate::buyLand(int idPlayer, int &price) {
    _owner = idPlayer;
    price = _buyPrice;
    iGame -> notifyChange("cell", ID);
}

vector<string> RealEstate::toString() {
    vector<string> v(13);
    v[0] = std::to_string(ID);
    v[1] = _typeName;
    v[2] = _name;
    v[3] = _description;
    v[4] = std::to_string(_buyPrice);
    v[5] = _rawInfo[5];
    v[6] = " ";
    v[7] = " ";
    v[8] = std::to_string(_mortgagePrice);
    v[9] = std::to_string (_owner);
    v[10] = " ";
    v[11] = std::to_string(_rentPrice);
    _isMortgage ?v[12] = "true": v[12] = "false";
    return v;
}

/*
    NormalLand implement
*/

void NormalLand::sellHouse(int &money) {
    _numberOfHouse--;
    _rentPrice /= _COEFFICIENT;
    money = _buyPrice / 2;
    iGame -> notifyChange("cell", ID);
}

void NormalLand::build(int &price) {
    if (_numberOfHouse < 4 && _numberOfHotel == 0) {
        _numberOfHouse++;
        _rentPrice *= _COEFFICIENT;
    }
    else {
        //xuat ra dong "Da co du 4 nha, can nang cap len khach san"
        //neu nguoi choi dong y nang cap thi reset so nha, doi gia thue, tang so khach san
        _numberOfHouse = 0;
        _numberOfHotel = 1;
    }
    
    price = _housePrice;
    iGame -> notifyChange("cell", ID);
}

//information doc tu file luc initialize
NormalLand::NormalLand(string information): RealEstate(information){
    // "@ chu tren the @ gia mua dat @ gia thue @ gia nha"
    _housePrice = std::stoi(_rawInfo[7]);
    _COEFFICIENT = std::stof (_rawInfo[6]);
    _numberOfHouse = 0;
    _numberOfHotel = 0;
}

vector<string> NormalLand::toString() {
    vector<string> v(13);
    v[0] = std::to_string(ID);
    v[1] = _typeName;
    v[2] = _name;
    v[3] = _description;
    v[4] = std::to_string(_buyPrice);
    v[5] = _rawInfo[5];
    v[6] = std::to_string(_COEFFICIENT);
    v[7] = std::to_string(_housePrice);
    v[8] = std::to_string(_mortgagePrice);
    v[9] = std::to_string (_owner);
    v[10] = std::to_string (_numberOfHouse);
    v[11] = std::to_string(_rentPrice);
    _isMortgage ?v[12] = "true": v[12] = "false";
    return v;
}


/*

    Railroad implement

*/

void Railroad::rent(int &money) {
    money = _rentPrice * (int)pow(2, playerOwnerNum[_owner] - 1);
    _rentPrice = money;
    iGame -> notifyChange("cell", ID);
}

void Railroad::buyLand (int idPlayer, int& price) {
    _owner = idPlayer;
    price = _buyPrice;
    playerOwnerNum[idPlayer]++;
    iGame -> notifyChange("player", idPlayer);
}

/*

    Factory implement

*/

//money is the amount that players have to spend to rent this area when they step on.
//this function will change attribute _rentPrice
void Factory::rent(int &money) {
    int dice1, dice2;
    iGame->getDice(dice1, dice2);
    if (isSameOwner) money = 10 * (dice1 + dice2) ; else money = 4 * (dice1 + dice2); //FUNCTION GET DICE OF GAME CLASS
    _rentPrice = money;
    iGame -> notifyChange("cell", ID);
}



/*
    Go class implementation
*/
void Go::activateCell(int idPlayer) {
    iGame -> transferMoney(0, idPlayer, START_MONEY_AMOUNT);
}

vector<string> Go::toString() {
    vector<string> v(13);
    v[0] = std::to_string(ID);
    v[1] = _typeName;
    v[2] = _name;
    v[3] = _description;
    v[4] = " ";
    v[5] = _rawInfo[5];
    v[6] = " ";
    v[7] = " ";
    v[8] = " ";
    v[9] = " ";
    v[10] = " ";
    v[11] = " ";
    v[12] = " ";
    return v;
}

/*

    PayTax class implementation

*/


void PayTax::activateCell(int idPlayer) {
    iGame -> transferMoney(idPlayer, 0, TAX);
}

vector <string>PayTax::toString() {
    vector<string> v(13);
    v[0] = std::to_string(ID);
    v[1] = _typeName;
    v[2] = _name;
    v[3] = _description;
    v[4] =" ";
    v[5] = _rawInfo[5];
    v[6] = " ";
    v[7] = " ";
    v[8] = " ";
    v[9] = " ";
    v[10] = " ";
    v[11] = " ";
    v[12] = " ";
    return v;
}


/*

    GoToJail class implementation

*/

void GoToJail::activateCell(int idPlayer) {
    bool state = true;
    iGame -> changeJailedState(idPlayer, state);
    iGame -> movePlayer(idPlayer, (40 - (ID - 10)) % 40);
}

vector<string> GoToJail::toString() {
    vector<string> v(13);
    v[0] = std::to_string(ID);
    v[1] = _typeName;
    v[2] = _name;
    v[3] = _description;
    v[4] =" ";
    v[5] = _rawInfo[5];
    v[6] = " ";
    v[7] = " ";
    v[8] = " ";
    v[9] = " ";
    v[10] = " ";
    v[11] = " ";
    v[12] = " ";
    return v;
}
