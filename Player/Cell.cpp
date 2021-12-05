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
    startPos = foundPos + seperator.size();
    count = card.length() - startPos;
    string amnt_temp = card.substr(startPos, count);
    stringstream ss (amnt_temp);
    ss >> amnt;
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
int NormalLand::buyLand(Player* player) {
    _Owner = player -> ID();
    return _buyPrice;
}
int NormalLand::rent() {
    return _rentPrice;
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
    _Owner = -1;
    _information.substr(2);
    
}
string NormalLand::toString() {
    return _information;
}