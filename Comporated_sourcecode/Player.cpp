#include "Player.h"
#include "IGame.h"
#include <iostream>

int Player::InstanceCount = 0;
int Player::NumberLeftPlayer = 0;

using std::string; using std::to_string;

string convertAvatarName(const string &nameAvatar)
{
    if (nameAvatar == "Xe cút kít") return "Image/barrow.png";
    else if (nameAvatar == "Larmborgini") return "Image/car.png";
    else if (nameAvatar == "Thịt cầy di động") return "Image/dog.png";
    else if (nameAvatar == "Rồng trắng mắt xanh") return "Image/dragon.png";

    return "";
}

// Player Initializer with given _money, _jailed state, _position, _name and _avatar
Player::Player(IGame* igame, const string &newName, const string &newAvatar)
{
    _igame = igame;
    if ( igame->querySettingRule("startOp") == 0 ) _money = 1000;
        else if ( igame->querySettingRule("startOp") == 1 ) _money = 1500;
        else _money = 2000;
    _jailed = false;
    _position = 1;
    _name = newName;
    _avatar = convertAvatarName(newAvatar);
    _id = Player::InstanceCount;
    _gameOver = false;
    _debtTo = -1;
    Player::InstanceCount++;
    Player::NumberLeftPlayer++;
}

// Player Initializer.
Player::Player()
{
    _igame = nullptr;
    _money = 2000;
    _jailed = false;
    _position = 1;
    _name = "";
    _avatar = "";
    _id = Player::InstanceCount;
    _gameOver = false;
    _debtTo = -1;
    Player::InstanceCount++;
    Player::NumberLeftPlayer++;
}

// Player Deconstructor
Player::~Player()
{
    Player::InstanceCount = 0;
    Player::NumberLeftPlayer = 0;
}

// getter :>

// return the Player's current _money
float Player::Money()
{
    return _money;
}

// return the Player's current _position on Board
int Player::Position()
{
    return _position;
}

string Player::Name()
{
    return _name;
}

string Player::Avatar()
{
    return _avatar;
}

bool Player::IsGameOver()
{
    return _gameOver;
}

bool Player::isInJail()
{
    return _jailed;
}

int Player::debtTo()
{
    return _debtTo;
}

// Increase (or decrease) Player's current _money
void Player::changeMoney(const float &value)
{
    _money += value;
    _igame->notifyChange("player", _id);
}

void Player::setPosition(const int &pos)
{
    _position = pos;
    _igame->notifyChange("player", _id);
}

// setter methods

// set the Player's current _money
void Player::setMoney(const float &value)
{
    _money = value;
}

// change the Jailed state for the player
void Player::changeInJail()
{
    if (_jailed == false) setPosition(11);
    _jailed ^= true;
    _igame->notifyChange("player", _id);
}

void Player::setName(string &newName)
{
    _name = newName;
    _igame->notifyChange("player", _id);
}

void Player::setAvatar(string &newAvatar)
{
    _avatar = newAvatar;
    _igame->notifyChange("player", _id);
}

void Player::setGameOver()
{
    _gameOver = true;
}

void Player::setDebtTo(int idPlayer)
{
    _debtTo = idPlayer;
}

string Player::toString()
{
    return to_string(_id) + '_' + _name + '_' + to_string(_position) + '_' + _avatar + '_' + to_string(_money) + '_' +
            (_jailed ? "true" : "false");
}
