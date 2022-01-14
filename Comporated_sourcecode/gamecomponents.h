#ifndef GAMECOMPONENTS_H
#define GAMECOMPONENTS_H

#include <string>
#include <IGame.h>

using std::string;

class IGame;

class GlobalGameStatus
{
private:
    IGame* igame;
    int idTurnPlayer;
    bool repeatTurn;
public:
    GlobalGameStatus(IGame* igame) { GlobalGameStatus::igame = igame; idTurnPlayer = 0; }

    int getTurnPlayer() { return idTurnPlayer; }
    void setTurnPlayer(int idPlayer) { idTurnPlayer = idPlayer; igame->notifyChange("gameStatus"); }
    void setRepeatTurn(bool repeatTurn = false) { GlobalGameStatus::repeatTurn = repeatTurn; igame->notifyChange("gameStatus"); }
    string toString() { return std::to_string(idTurnPlayer) + '_' + std::to_string(repeatTurn ? 1 : 0); }
};

class NotifyCommand;

class Notify
{
private:
    string textNotify; //Information show what happened in game
    vector <string> listQuery; //List of choices for a given textNotify
    string ans; //Choice player have chose in the listQuery
    bool waitResponde;

public:
    void setNotify(const string textNoity, const vector <string> &listQuery, bool waitResponde)
    {
        Notify::textNotify = textNoity;
        Notify::listQuery = listQuery;
        Notify::waitResponde = waitResponde;
    };
    string getAns() { return ans; }

    friend NotifyCommand;
};

#endif // GAMECOMPONENTS_H
