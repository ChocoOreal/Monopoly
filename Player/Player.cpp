#include "Player.h"



Player::Player(){
    money = 0;
    jailed = false;
    position = 0;
    name = "";
    avatar = "";
}

    
Player::~Player(){

}


// return the Player's current money
double Player::getMoney(){
    return money;
}

// return the Player's current position on Board
int Player::getPosition(){
    return position;
}

// Increase (or decrease) Player's current money
void Player::earnMoney(const float& value){
    money += value;
}

// set the Player's current money
void Player::setMoney(const float& value){
    money = value;
}