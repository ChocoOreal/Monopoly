#include "Player.h"
#include "Dice.h"
#include "Game.h"
#include "Cell.h"
#include "Command.h"
#include "CommandHandler.h"
#include "RunningGameMode.h"
#include <iostream>

using namespace std;
/*
int main(){
    int cnt[11] = {0};
    for(int i = 0; i < 1e5; ++i){
        cnt[Dice::Rand(1, 10)]++;
    }
    for(int i = 1; i <= 10; ++i){
        cout << cnt[i] << ' ';
    }
}*/

int Player::InstanceCount = 0;
int Railroad::playerOwnerNum[4] = {};

/*
int main () {
    int ID = 1;
    Player A(1000, false, 3, "Player A", "");
    A.setID(ID);
    cout << A.toString() << '\n';

    getchar();

    Card c;
    string info;
    int amount;
    int type;
    c.drawCard(info, amount, type);
    cout << info << '\n';

    getchar();

    Factory ft("Nha may dien @ 300 @ 200");

    getchar();

    if (type == 1) A.changeMoney(amount); else A.setPosition( A.Position() + amount );
    cout << A.toString() << '\n';
}
*/

int main()
{
    RunningGameMode *application = new RunningGameMode(4);  
    CommandHandler *doCommand = application->getCommandHandler();

    //All the command from 2 to 6 can not be used since the list of cells is not initialised

    doCommand->doCommand(0);
    
    //delete application;
    delete doCommand;

    return 0;
}