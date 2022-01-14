#include "Cell.h"
#include "Dice.h"
#include "IGame.h"
#include "Util.h"
#include <string>
#include <sstream>

using std::string; using std::stringstream;

IGame* Cell::iGame = nullptr;
string Card::luckyCard[10] = {};
string Card::chancesCard[10] = {};
string Card::currentCard = "";
int Railroad::playerOwnerNum[4] = {};
int JailCell::numberRollDice[4] = {0, 0, 0, 0};

Cell::Cell (const string &infomation) {
    _rawInfo = Util::parse(infomation, " @ ", 0);
    ID = std::stoi (_rawInfo[0]);
    _typeName = _rawInfo[1];
    _name = _rawInfo[2];
    _description = _rawInfo[3];
}

vector<string> Cell::toString()
{
    vector<string> v(13);
    v[0] = std::to_string(ID);
    v[1] = _typeName;
    v[2] = _name;
    v[3] = _description;
    for (size_t i = 4; i < v.size(); i++) v[i] = " ";

    return v;
}

void Cell::bankruptThisCell(int idPlayer, int idCreditor)
{
}

Cell::~Cell()
{
    Cell::iGame = nullptr;
}

/* Card implementation */

Card::Card(const string &information) : Cell(information) {

    //If this empty, means we need set up it
    if (luckyCard[0] == "")
    {
        luckyCard[0] = "Tien @ Vuot den do, phat 200 dong @ -200";
        luckyCard[1] = "Tien @ Vuot den do, phat 200 dong @ -200";
        luckyCard[2] = "Tien @ Vuot den do, phat 200 dong @ -200";
        luckyCard[3] = "Tien @ Vuot den do, phat 200 dong @ -200";
        luckyCard[4] = "Tien @ Vuot den do, phat 200 dong @ -200";
        luckyCard[5] = "Tien @ Vuot den do, phat 200 dong @ -200";
        luckyCard[6] = "Tien @ Vuot den do, phat 200 dong @ -200";
        luckyCard[7] = "@ Vuot den do, phat 200 dong @ -200";
        luckyCard[8] = "@ Vuot den do, phat 200 dong @ -200";
        luckyCard[9] = "@ Vuot den do, phat 200 dong @ -200";
        chancesCard[0] = "Vi tri @ Dang truoc co tai nan giao thong, lui 2 buoc @ -2";
        chancesCard[1] = "Vi tri @ Dang truoc co tai nan giao thong, lui 2 buoc @ -2";
        chancesCard[2] = "Vi tri @ Dang truoc co tai nan giao thong, lui 2 buoc @ -2";
        chancesCard[3] = "Vi tri @ Dang truoc co tai nan giao thong, lui 2 buoc @ -2";
        chancesCard[4] = "Vi tri @ Dang truoc co tai nan giao thong, lui 2 buoc @ -2";
        chancesCard[5] = "Vi tri @ Dang truoc co tai nan giao thong, lui 2 buoc @ -2";
        chancesCard[6] = "Vi tri @ Dang truoc co tai nan giao thong, lui 2 buoc @ -2";
        chancesCard[7] = "@ Dang truoc co tai nan giao thong, lui 2 buoc @ -2";
        chancesCard[8] = "@ Dang truoc co tai nan giao thong, lui 2 buoc @ -2";
        chancesCard[9] = "@ Dang truoc co tai nan giao thong, lui 2 buoc @ -2";
        currentCard = "";
    }
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
    
    if (temp[0] == "Tien") iGame -> transferMoney(idPlayer, -1, stoi (temp[2]));
    else iGame -> movePlayer(idPlayer, stoi (temp[2]));

    Cell::iGame->notify(temp[1], {}, true);
}

vector<string> Card::toString()
{
    vector<string> v(13);

    v[0] = std::to_string(ID); v[1] = _typeName; v[2] = _name; v[3] = _description;
    v[4] = " ";
    v[5] = " ";
    v[6] = " ";
    v[7] = " ";
    v[8] = " ";
    v[9] = " ";
    v[10] = " ";
    v[11] = " ";
    v[12] = " ";

    return v;
}

Card::~Card()
{
    Card::luckyCard[10] = {};
    Card::chancesCard[10] = {};
    Card::currentCard = "";
}

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

RealEstate::RealEstate(const string &information):Cell (information) {
    _owner = -1;
    _buyPrice = std::stoi(_rawInfo[4]);
    _rentPrice = std::stoi (_rawInfo[5]);
    _mortgagePrice = std::stoi (_rawInfo[8]);
    _isMortgage = false;
    _owner = -1;
}

void RealEstate::activateCell(int idPlayer)
{
    if (_owner == -1) return;
    if (_isMortgage) return;
    if (_owner != idPlayer)
    {
        int price(0);
        this->rent(price);
        iGame->transferMoney(idPlayer, _owner, price);
    }
}

void RealEstate::mortgage(int &money) {
    _isMortgage = true;
    money = _mortgagePrice;
    iGame -> notifyChange("cell", ID);
}

void RealEstate::redeem(int &money)
{
    _isMortgage = false;
    money = _mortgagePrice + 10/100 * _mortgagePrice;
    iGame->notifyChange("cell", ID);
}

void RealEstate::buyLand(int idPlayer, int &price) {
    _owner = idPlayer;
    price = _buyPrice;
    iGame -> notifyChange("cell", ID);
}

void RealEstate::bankruptThisCell(int idPlayer, int idCreditor)
{
    if (_owner == idPlayer) _owner = idCreditor;
    iGame->notifyChange("cell", ID);
}

vector<string> RealEstate::toString() {
    vector<string> v(13);
    v = Cell::toString();

    v[4] = std::to_string(_buyPrice);
    v[5] = _rawInfo[5];
    v[6] = " ";
    v[7] = " ";
    v[8] = std::to_string(_mortgagePrice);
    v[9] = Cell::iGame->askStringName("player", _owner);
    v[10] = " ";
    v[11] = std::to_string(_rentPrice);
    _isMortgage ?v[12] = "true": v[12] = "false";

    return v;
}

/*
    NormalLand implement
*/

void NormalLand::sellHouse(int &money) {
    if (_numberOfHotel != 0)
    {
        _numberOfHotel--;
        _numberOfHouse = 4;
        _rentPrice = std::ceil(_rentPrice / HOTELCOEFFICIENT);
    }
    else
    {
        _numberOfHouse--;
        _rentPrice = std::ceil(_rentPrice / COEFFICIENT);
    }

    money = _buyPrice / 2;
    iGame -> notifyChange("cell", ID);
}

void NormalLand::build(int &price) {
    if (_numberOfHouse < 4) {
        _numberOfHouse++;
        _rentPrice *= COEFFICIENT;
    }
    else {
        _numberOfHouse = 0;
        _numberOfHotel = 1;
        _rentPrice *= HOTELCOEFFICIENT;
    }
    
    price = _housePrice;
    iGame -> notifyChange("cell", ID);
}

//information doc tu file luc initialize
NormalLand::NormalLand(const string &information): RealEstate(information){
    // "@ chu tren the @ gia mua dat @ gia thue @ gia nha"
    _housePrice = std::stoi(_rawInfo[7]);
    _COEFFICIENT = std::stof (_rawInfo[6]);
    _numberOfHouse = 0;
    _numberOfHotel = 0;
}

void NormalLand::bankruptThisCell(int idPlayer, int creditor)
{
    if (_owner != idPlayer) return;

    RealEstate::bankruptThisCell(idPlayer, creditor);

    int tmp(0), totalReceive(0);

    if (_numberOfHotel != 0) sellHouse(tmp);
    tmp += totalReceive;
    while (_numberOfHouse != 0)
    {
        sellHouse(tmp);
        totalReceive += tmp;
    }

    Cell::iGame->transferMoney(-1, creditor, totalReceive);

    iGame->notifyChange("cell", ID);
}

vector<string> NormalLand::toString() {
    vector<string> v(13);
    v = RealEstate::toString();

    v[4] = std::to_string(_buyPrice);
    v[5] = _rawInfo[5];
    v[6] = std::to_string(_COEFFICIENT);
    v[7] = std::to_string(_housePrice);
    v[8] = std::to_string(_mortgagePrice);
    v[9] = Cell::iGame->askStringName("player", _owner);
    v[10] = (_numberOfHotel != 0 ? "5" : std::to_string (_numberOfHouse) );
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
    iGame->notifyChange("cell", ID);
}

Railroad::~Railroad()
{
    Railroad::playerOwnerNum[4] = {};
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

void Go::passGoCell(int idPlayer)
{
    if ( Cell::iGame->querySettingRule("passGoOp") == 0) return;
    else if ( Cell::iGame->querySettingRule("passGoOp") == 1 ) Cell::iGame->transferMoney(-1, idPlayer, 200);
    else Cell::iGame->transferMoney(-1, idPlayer, 400);
}

void Go::activateCell(int idPlayer) {
    if ( Cell::iGame->querySettingRule("inGoOp") == 0) return; else iGame -> transferMoney(0, idPlayer, START_MONEY_AMOUNT);
}

vector<string> Go::toString() {
    return Cell::toString();
}

/*

    PayTax class implementation

*/


void PayTax::activateCell(int idPlayer) {
    iGame -> transferMoney(idPlayer, 0, TAX);
}

vector <string>PayTax::toString() {
    return Cell::toString();
}


/*

    GoToJail class implementation

*/

void GoToJail::activateCell(int idPlayer) {
    bool state = true;
    iGame -> changeJailedState(idPlayer, state);
}

vector<string> GoToJail::toString() {
    return Cell::toString();
}

/* Jail cell implementation */

void JailCell::activateCell(int idPlayer)
{
    if (JailCell::numberRollDice[idPlayer] < 3)
    {
        string ans = Cell::iGame->notify("Chọn cách ra khỏi tù!", {"Trả 50", "Thảy số đôi xúc xắc"}, true);
        if (ans == "Thảy số đôi xúc xắc")
        {
            Cell::iGame->rollDice();
            int dice1, dice2;
            Cell::iGame->getDice(dice1, dice2);
            if (dice1 == dice2) Cell::iGame->movePlayer(idPlayer, dice1 + dice2); else numberRollDice[idPlayer]++;
        }
        else
        {
            Cell::iGame->changeJailedState(idPlayer, false);
            Cell::iGame->transferMoney(idPlayer, -1, 50);
            JailCell::numberRollDice[idPlayer] = 0;
        }
    }
    else
    {
        string ans = Cell::iGame->notify("Chọn cách ra khỏi tù!", {"Trả 50"}, true);
        Cell::iGame->changeJailedState(idPlayer, false);
        Cell::iGame->transferMoney(idPlayer, -1, 50);
        JailCell::numberRollDice[idPlayer] = 0;
    }
}

vector<string> JailCell::toString()
{
    return Cell::toString();
}

JailCell::~JailCell()
{
    for (int i = 0; i < 4; i++) JailCell::numberRollDice[i] = 0;
}

/* Park cell implementation  */

void Park::activateCell(int idPlayer)
{
    if ( Cell::iGame->querySettingRule("parkOp") == 0) return;
    else Cell::iGame->transferMoney(idPlayer, -1, 250);
}

vector<string> Park::toString()
{
    return Cell::toString();
}
