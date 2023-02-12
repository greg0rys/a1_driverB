#include "Bone.h"

Bone::Bone():sideA(0),sideB(0)
{
    // generate random number 1-9
    generateNumbers(sideA);
    generateNumbers(sideB);
}

Bone::Bone(const Bone & aBone):sideA(0),sideB(0)
{
    *this = aBone;
}



Bone &Bone::operator=(const Bone & aBone)
{
    if(this == &aBone)
        return *this;
    sideA = aBone.sideA;
    sideB = aBone.sideB;

    return *this;
}

ostream& operator<<(ostream& out, Bone &aBone)
{
     aBone.printSides();
     out << "\t ";

     return out;
}

Bone::~Bone()
{
    sideA = sideB = 0;
}


/*
 * Generate random numbers for each side of the bone
 *
 * by taking the return value of rand() % 9 + 1 we will always get a number 1-9
 */
void Bone::generateNumbers(int & side)
{


    side = (rand() % 9) + 1;
}