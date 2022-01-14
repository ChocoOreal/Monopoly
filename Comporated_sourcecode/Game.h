#pragma once

#include "IGame.h"
#include <vector>
#include <iostream>
#include <string>

class Player;
class Cell;
class GameCommand;
class RunningGameMode;
class CommandHandler;
class GlobalGameStatus;
class Notify;
class RunningGameMode;
class SettingRule;

using std::vector; using std::cout; using std::string;

class Game : public IGame
{
    private:
        vector <Player *> _listPlayer;
        vector <Cell *> _listCell;
        int _dice1, _dice2;
        CommandHandler* invoker;
        GlobalGameStatus* globalGameStatus;
        SettingRule *curSettingRule;

        //The information of data waiting for updating to GUI
        string _typeUpdate; int _idUpdate;

        //This is the query or notification that game need to show for player deciding or knowing
        Notify *_notification;

        //Used to notify game over
        RunningGameMode *runningGameMode;

        void initializePlayer(int, vector< vector<string> > &playerInformation);
        void initializeBoard();
        
    public:
        Game();
        Game(int, vector< vector<string> > playerInformation, RunningGameMode* runningGameMode, SettingRule *curSetting);
        ~Game();

        GlobalGameStatus* getGlobalGameStatus() { return globalGameStatus; }

        //This method must be called after the invoker in this class has been determined, for sync data between GUI and logic source
        //code when starting a game
        void syncData();
        void rollDice();
        void getDice(int &dice1, int &dice2);
        void transferMoney(int idPlayerFrom, int idPlayerTo, int amnt);
        string notify(const string &text, const vector <string> &listQuery = {}, const bool waitResponde = false);
        void movePlayer(int idPlayer, int pos);
        void changeJailedState (int idPlayer, bool jailed);
        void notifyChange(const string &type, int id = 0);
        void getNotifyChange(string &type, int &id);
        string askStringName(const string &type, int id);
        void declareBankruptPlayer(int idPlayerBankrupt);
        int querySettingRule(const string &queryOp);
        void endGame();

        friend GameCommand;
        friend RunningGameMode;
};
