#include "Player.h"


// Player Initializer with given _money, _jailed state, _position, _name and _avatar
Player::Player(int newMoney, bool newJailed, int newPosition, string newName, string newAvatar){
    _money = newMoney;
    _jailed = newJailed;
    _position = newPosition;
    _name = newName;
    _avatar = newAvatar;
}

// Player Initializer.
Player::Player(){
    _money = 0;
    _jailed = false;
    _position = 0;
    _name = "";
    _avatar = "";
}


// Player Deconstructor
Player::~Player(){

}


// getter :>

// return the Player's current _money
float Player::Money(){
    return _money;
}

// return the Player's current _position on Board
int Player::Position(){
    return _position;
}


string Player::Name(){
    return _name;
}

string Player::Avatar(){
    return _avatar;
}


bool Player::isInJail(){
    return _jailed;
}


// Increase (or decrease) Player's current _money
void Player::changeMoney(const float& value){
    _money += value;
}


// setter methods

// set the Player's current _money
void Player::setMoney(const float& value){
    _money = value;
}

// change the Jailed state for the player
void Player::changeInJail(){
    _jailed ^= true; 
}

void Player::setName(string& newName){
    _name = newName;
}

void Player::setAvatar(string& newAvatar){
    _avatar = newAvatar;
}




