#include "ChickenYard.h"
/**
 * ChickenYard.cpp the implementation file for ChickenYard.h
 * @author Greg Shenefelt
 * @version 0.0.4
 */


// default constructor
ChickenYard::ChickenYard()
        : boneYard(new yardsDLL()), boneCount(INIT_SIZE), shuffled(false) {

    yardArray = makeArray();
    boneCount = INIT_SIZE;

    printYardArr();
    shuffleBones();
    shuffled = !shuffled;

    generateYard();
    boneYard->display();
}

/*
 * Create the bone yard as an array initially of 52 bones
 * Return: an std::array container of 52 bone objects.
 */
std::array<Bone,52> ChickenYard::makeArray() const {

    // when generating the list we will need to recurse to link the ptrs
    std::array<Bone, 52> bones;

    for (auto x = 0; x < INIT_SIZE; x++) {
        Bone temp;
        bones[x] = temp;
    }

    return bones;
}

/*
 * Shuffle the array of bones using the std::shuffle method
 * To generate a random index for each object I made use of the
 * std::default_random_engine
 */
void ChickenYard::shuffleBones() {

    auto range = std::default_random_engine{};
    shuffle(yardArray.begin(), yardArray.end(), range);
}

/*
 * Turn the yard from an array of bones to a linked list of bones
 * This method calls the recursive version of itself to complete the task.
 */
void ChickenYard::generateYard()
{
    for(auto x = 0; x < boneCount; x++)
        boneYard->createYard(yardArray[x]);
}

/*
 * Recurse of the std::array structure to create a linked list of all the
 * bones in the boneYard;
 * Params: node *& a pointer reference to the head of the linked list
 *         std::array & a reference to the array of bones.
 *         int & a reference to an int which is used to both access the object
 *         stored at each index of the array and is also used as the
 *         recursive stopping point, so we don't overflow the bounds of the
 *         yardArray
 */


/*
 * Copy constructor to make deep copies of chickenYard objects
 */
ChickenYard::ChickenYard(const ChickenYard &aYard)
        : boneYard(nullptr), boneCount(0), shuffled(false) {
    *this = aYard;
}

/*
 * Overloaded operator= to create deep copies of all chickenYard objects
 * when created via = assignment.
 */
ChickenYard &ChickenYard::operator=(const ChickenYard &aYard) {
    if (this == &aYard)
        return *this;

    if(!aYard.boneYard)
    {
        boneYard = nullptr;
        boneCount = aYard.boneCount;
        shuffled = aYard.shuffled;
        return *this;
    }

    if(boneYard)
        delete boneYard;

    boneYard = new yardsDLL(*aYard.boneYard);
    boneCount = aYard.boneCount;
    shuffled = aYard.shuffled;

    return *this;
}

/*
 * Class destructor
 */
ChickenYard::~ChickenYard() {
    if(boneYard)
        delete boneYard;

    boneYard = nullptr;

}



void ChickenYard::getHand(Player *& aPlayer)
{
    boneYard->drawHand(aPlayer->getHand());
}


bool ChickenYard::draw(Player *& aPlayer)
{
    return boneYard->draw(aPlayer->getHand());

}

// helper functions

// check if the chickenYards linked list is empty
bool ChickenYard::isEmpty() const
{
   return boneYard->totalBones() == 0;
}

// get a total count of all bones in the boneYard linked list.
int ChickenYard::getCount()
{
    return boneYard->totalBones();
}

// print the array of bones to show shuffle.
void ChickenYard::printYardArr() {

    cout << "Here's the bones before shuffle! " << endl;

    for (auto x = 0; x < INIT_SIZE; x++) {
        cout << x + 1 << " [ " << yardArray[x].getSideA()
             << " | " << yardArray[x].getSideB() << " ]\t";
        if(x % 5 == 0)
            cout << endl << endl;
    }

    cout << endl << endl;
    cout << "    \t\t\t***********************************    " << endl;
    cout << "    \t\t\tHere's the bones after the shuffle:    " << endl;
    cout << "    \t\t\t***********************************    " << endl;
}


