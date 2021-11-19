#include "Player.h"


// Player Initializer with given money, jailed state, position, name and avatar
Player::Player(int newMoney, bool newJailed, int newPosition, string newName, string newAvatar){
    money = newMoney;
    jailed = newJailed;
    position = newPosition;
    name = newName;
    avatar = newAvatar;
}

// Player Initializer.
Player::Player(){
    money = 0;
    jailed = false;
    position = 0;
    name = "";
    avatar = "";
}


// Player Deconstructor
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


string Player::Name(){
    return name;
}

string Player::Avatar(){
    return avatar;
}


bool Player::isInJail(){
    return jailed;
}



// Increase (or decrease) Player's current money
void Player::earnMoney(const float& value){
    money += value;
}



// setter methods

// set the Player's current money
void Player::setMoney(const float& value){
    money = value;
}

// change the Jailed state for the player
void Player::changeInJail(){
    jailed ^= true; 
}

void Player::setName(string& newName){
    name = newName;
}

void Player::setAvatar(string& newAvatar){
    avatar = newAvatar;
}




