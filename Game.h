#pragma once
#include <vector>
#include <iostream>
#include <random>
#include "playerQueue.h"
#include <valarray>
#include "ChickenYard.h"



using namespace std;




class Game
{
private:
    struct leadPlayer
    {
        int playerNum;
        int score;

        leadPlayer()
        {
            playerNum = 0;
            score = 0;
        }

        leadPlayer(const int & pNum, const int & pscore)
        {
            playerNum = pNum;
            score = pscore;
        }

        ~leadPlayer()
        {
            playerNum = score = 0;
        }
    };
    playerQueue * players;
    playerQueue * tiedPlayers;
    ChickenYard * boneYard;
    bool hasBones;
    bool isTied;
    leadPlayer * firstPlace;
    int numPlayers;


    void createPlayersContainer(int &, int &);
    void fillPlayersHands();
    static int getInteger()
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
