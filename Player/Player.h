#include <string>
#include <sstream>

using namespace std;

class Player
{

// not sure what to put here yet

private:
    // Player current money (should be float number)
    double money;

    // a boolean state to check whethe the Player is inJail or not
    bool jailed; // sorry for weird name ;(

    // the Player current position on the Board
    int position;
    
    // the Player username
    string name;

    // string avatar use to store a path to .jpeg file that's represent Player 
    string avatar;

public:

    double Money();
    bool isInJail();

public:

    // return the Player's current money
    double getMoney();

    // return the Player's current position on Board
    int getPosition();

    // Increase (or decrease) Player's current money
    void earnMoney(const float&);

    // set the Player's current money
    void setMoney(const float&);

public:

    // Init the Player class
    Player();

    // Deconstruct the Player class
    ~Player();
};
