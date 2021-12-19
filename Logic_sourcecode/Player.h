#pragma once

#include <string>
#include <sstream>

using std::string;

class Player
{
    public:
        static int InstanceCount;

    private:
        // Player current money (should be float number)
        float _money;

        // a boolean state to check whethe the Player is inJail or not
        bool _jailed; // sorry for weird name ;(

        // the Player current position on the Board
        int _position;

        // the Player username
        string _name;

        // string avatar use to store a path to .jpeg file that's represent Player
        string _avatar;

        // the Player id range from 0 to 3
        int _id;

    public:
        // return the Player's current money
        float Money();

        // return the Player's current position on Board
        int Position();

        // return the Player's current Name
        string Name();

        // return the Player's Avatar path
        string Avatar();

        // check whether the Player is in Jail or not
        bool isInJail();

        int ID()
        {
            return _id;
        }

    public:
        void changeInJail();
        
        // Increase (or decrease) Player's current money
        void changeMoney(const float &);

        // set the Player's current money
        void setMoney(const float &);

        void setPosition(const int &);

        // set Player Name
        void setName(string &);

        // set Plauer Avatar
        void setAvatar(string &);

        void setID(int &value)
        {
            _id = value;
        }

    public:
        string toString();

    public:
        // Init the Player class
        Player();

        // Init the Player class with giving information (money, jailedState, position, name, avatar)
        Player(int, bool, int, string, string);

        // Deconstruct the Player class
        ~Player();
};
