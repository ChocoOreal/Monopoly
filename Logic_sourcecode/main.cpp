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
int Railroad::playerOwnerNum[4] = {0};



int main()
{
    // RunningGameMode *application = new RunningGameMode(4);  
    // CommandHandler *doCommand = application->getCommandHandler();

    // //All the command from 2 to 6 can not be used since the list of cells is not initialised

    // doCommand->doCommand(0);
    
    // delete application;

    // return 0;
    
    RunningGameMode g(4);

    Railroad r ("3 @ normalland @ land @ this is a land for building house and hotel @ 5000 @ 1000 @ 1.8 @ 300 @ 230");
    int p;
    r.buyLand(3, p);

    return 0;
}