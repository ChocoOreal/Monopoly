#include "Cell.h"

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

//chua xong
void Card::drawCard (string& info, int& amnt, int& type) {
    //@ chu tren the @ gia tri cua the (duong hoac am)\n
    type = Dice::Rand(1, 2);
    int i = Dice::Rand(1, 6);//random
    string seperator = " @ ";
    int startPos = 2;
    int foundPos = 0;
    int count = 0;
    string card;
    if (type == 1) {
        card = luckyCard[i];
    }
    else {
        card = chancesCard[i];
    }
    foundPos = card.find(seperator, startPos);
    count = foundPos - startPos;
    info = card.substr(startPos, count);
    currentCard = info;
    startPos = foundPos + seperator.size();
    count = card.length() - startPos;
    string amnt_temp = card.substr(startPos, count);
    stringstream ss (amnt_temp);
    ss >> amnt;
}



/* 
    RealEstate implement
*/

int RealEstate::buyLand(Player* player) {
    _owner = player -> ID();
    
    return _buyPrice;
}

int RealEstate::rent(short& receiver) {
    receiver = _owner;
    return _rentPrice;//so tien phai tru cua thang dang dung, so tien cong cho thang owner
}

bool RealEstate::Mortgage() {
    if (_isMortgage) return false;
    _isMortgage = true;
    return true;

}

RealEstate::RealEstate(){
    _buyPrice = 0;
    _rentPrice = 0;
    _isMortgage = 0;
    _information = "";
    _owner = -1;
}

/*
    NormalLand implement
*/

int NormalLand::sellHouse() {
    _numberOfHouse--;
    _rentPrice /= COEFFICIENT;
    return _housePrice;
}


//chua xong
int NormalLand::buildHouse() {
    _numberOfHouse++;
    _rentPrice *= COEFFICIENT;
    return _housePrice;
}

//chua xong
int NormalLand::buildHotel() {
    _numberOfHotel++;
    _numberOfHouse = 0;
    _rentPrice *= COEFFICIENT;
    return _housePrice;
}
bool NormalLand::Mortgage() {
    if (_numberOfHotel + _numberOfHouse > 0 || _isMortgage == true) {
        return false;
    }
    else {
        _isMortgage = false;
        return true;
    }
}

//information doc tu file luc initialize
NormalLand::NormalLand(string information) {
    // "@ chu tren the @ gia mua dat @ gia thue @ gia nha"
    string separator = " @ ";
    string info;
    string value;
    string buy_price;
    string rent_price;
    string house_price;
    int foundPos = 0;
    int startPos = 0;
    foundPos = information.find(separator, startPos);
    int count = foundPos - startPos;
    _information = information.substr(startPos, count);
    
    startPos = foundPos + separator.length();
    foundPos = information.find(separator, startPos);
    count = foundPos - startPos;
    buy_price = information.substr(startPos, count);
    stringstream bp (buy_price);
    bp >> _buyPrice;
    startPos = foundPos + separator.length();
    foundPos = information.find(separator, startPos);
    count = foundPos - startPos;
    rent_price = information.substr(startPos, count);
    stringstream rp (rent_price);
    rp >> _rentPrice;
    startPos = foundPos + separator.length();
    count = information.length() - startPos;
    house_price = information.substr(startPos, count);
    stringstream hp (house_price);
    hp >> _housePrice;
    
    _isMortgage = false;
    _numberOfHotel = 0;
    _numberOfHouse = 0;
    _owner = -1;
    _information.substr(2);
    
    
}

/*

    Railroad implement

*/


int Railroad::rent(short& receiver) {
    
    receiver = _owner;
    if (receiver == -1) return 0;
    return _rentPrice * playerOwnerNum[_owner];
}

/*

    Factory implement

*/
//this is the true rent price, not real rent price (does not include value of dice in resulting value)
int Factory::rent(short& receiver) {
    receiver = _owner;
    if (receiver == -1) return 0;
    return _rentPrice;
}
RealEstate::RealEstate(string information) {
    //@ thong tin @ gia mua @ gia thue
    string separator = " @ ";
    string info;
    string value;
    string buy_price;
    string rent_price;
    int foundPos = 0;
    int startPos = 0;
    foundPos = information.find(separator, startPos);
    int count = foundPos - startPos;
    _information = information.substr(startPos, count);
    
    startPos = foundPos + separator.length();
    foundPos = information.find(separator, startPos);
    count = foundPos - startPos;
    buy_price = information.substr(startPos, count);
    stringstream bp (buy_price);
    bp >> _buyPrice;
    startPos = foundPos + separator.length();
    count = information.length() - startPos;
    rent_price = information.substr(startPos, count);
    stringstream rp (rent_price);
    rp >> _rentPrice;
    _isMortgage = false;
    
    _owner = -1;
    _information.substr(2);
}