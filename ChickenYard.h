#pragma once
#include "DLL.h"
#include "Player.h"

#include <algorithm>
#include <cstdlib>
#include <random>
#include <array>

using namespace std;

class ChickenYard {

private:

    const static int INIT_SIZE = 52;
    const static int PLAYERS_SIZE = 7;
    typedef std::array<Bone, INIT_SIZE> bArray;

    bArray     yardArray;
    yardsDLL * boneYard;
    int        boneCount;
    bool       shuffled;

    void printYardArr();
    std::array<Bone, INIT_SIZE> makeArray() const;

public:

    ChickenYard();
    ChickenYard(const ChickenYard &);
    ~ChickenYard();
    ChickenYard &operator=(const ChickenYard &);


    bool isEmpty() const;
    void generateYard();
    void shuffleBones();
    int getCount();
    bool draw(Player *&);
    void getHand(Player *&);

};
