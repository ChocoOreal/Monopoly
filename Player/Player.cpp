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
float Player::Money(){
    return money;
}

// return the Player's current position on Board
int Player::Position(){
    return position;
}

bool Player::isInJail(){
    return jailed;
}

// Increase (or decrease) Player's current money
void Player::earnMoney(const float& value){
    money += value;
}

// set the Player's current money
void Player::setMoney(const float& value){
    money = value;
}