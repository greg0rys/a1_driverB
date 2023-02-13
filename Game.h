#pragma once
#include <vector>
#include <iostream>
#include <random>
#include <valarray>
#include "Player.h"
#include "ChickenYard.h"


using std::cout;
using std::endl;
typedef std::vector<Player> pVector;
typedef std::vector<int>    scoreVector;

class Game
{
private:
    pVector players;
    pVector tiedPlayers;
    scoreVector playerScores;
    ChickenYard * boneYard;
    bool hasBones;
    bool isTied;
    int  leadPlayer;
    int leadPoints;
    int numPlayers;
    void createPlayersContainer(int &);
    void fillPlayersHands();
    int getInteger()
    {
        int numberIn;
        cin >> numberIn;

        while(cin.fail())
        {
            cin.clear();
            cin.ignore(101, '\n');
            cerr << "Please enter a whole number as valid input "
                 << "(EX 5 or 1500) " << endl;
            cin >> numberIn;
        }

        cin.ignore(101,'\n');
        return numberIn;
    }

    void handleTie(int & targetVal);
    void clearTie();


public:
    Game();

    Game(const Game &);
    Game& operator=(const Game &);
    ~Game();

    void gameStart();
    void updateScores();
    void displayPlayersHands();
    void getLeadPlayer(int &);
    void setLeadPlayer(int &); // get the player no as a ref from player obj

    void playRound();
    void getRoundResults();



};
