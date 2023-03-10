#pragma once
#include "DLL.h"
#include "Bone.h"
#include <iostream>
#include <algorithm>
#include <vector>


class Player {
private:


    playersDLL * hand;

    int points, handCount, playerNo;
    const static int HAND_START = 7;
    bool firstHand;


public:
    Player();
    Player(const Player &);
    Player& operator=(const Player &);
    friend bool operator==(const Player &, const Player &);
    friend ostream& operator<<(ostream &out,  Player &);
    ~Player();
    void getPoints(int &);
    bool isFirstHand() const;
    void displayHand();
    void addToHand(const Bone &);
    void getPlayerNo(int &) const;
    void setPlayerNo(const int);
    playersDLL& getHand();
    Bone& getLastDraw()
    {
        return hand->getRecentDraw();
    }
    void setPoints(int &pts)
    {
        points = pts;
    }

};
