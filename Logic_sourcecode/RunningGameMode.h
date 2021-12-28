#ifndef RUNNINGGAMEMODE_H
#define RUNNINGGAMEMODE_H

#include <vector>

using std::vector;

//This class is just simulated for Graphical User Interface in coding and testing process. This will be replaced by the real class of GUI when it's appropriate
class GUI;

class CommandHandler;
class Game;

class RunningGameMode
{
    private:
        GUI *mainWindow;
        CommandHandler *invoker;
        Game *game;

    public:
        RunningGameMode();
        RunningGameMode(int numPlayer); //In fact this will be a config class contain setting used in a game
        ~RunningGameMode();

        CommandHandler *getCommandHandler();
        void debugAddIdChose(int idPlayer, int idCell);
};

class GUI
{
    public:
        //The cell and player conduct the command from GUI
        vector <int> listIdChose;

    friend RunningGameMode;
};

#endif