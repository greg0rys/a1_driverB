#include "DLL.h"

#include <utility>




DLL::DLL(const DLL &aCopy)

{
    *this = aCopy;
}




DLL::~DLL()
{

}




void DLL::destroyList(DLL::node *& top)
{
    if(!top || isEmpty(top))
        return;

    destroyList(top->next);
    delete top;
}





void DLL::countChain(DLL::node *top, int &counter)
{
    if(!top || isEmpty(top))
        return;

    countChain(top->next, ++counter);

}


bool DLL::isEmpty(node * aList)
{
    return aList == nullptr;
}


void DLL::copyChain(DLL::node *& destList, DLL::node * sourceList)
{


    if(!sourceList)
        return;

    destList = new node(*sourceList->data);
    destList->prev = sourceList->prev;

    copyChain(destList->next, sourceList->next);
}

// the players DLL will need to handle updating its own tail
void DLL::insert(DLL::node*& start, const Bone &bone)
{
    if(!start)
    {
        start = new node(bone);
        start->next = nullptr;
        start->prev = nullptr;

    }

    if(start->next)
        insert(start->next, bone);

    if(!start->next)
    {
        start->next = new node(bone);
        start->next->prev = start;
        start->next->next = nullptr;
        return;
    }

}


void DLL::remove(DLL::node *&target)
{
    node * temp = target->next;
    delete target;
    target = temp;
}


void DLL::displayList(DLL::node * top)
{
    if(!top)
        return;

    static int formatter = 1;

    cout << "[ " << top->data->getSideA()
         << "|" << top->data->getSideB() << " ]";

    // use a formatter counter to keep bones in rows of 5
    if(formatter % 5 == 0)
        cout << endl << endl;
    formatter++;

    displayList(top->next);

}



/**
 * playerList implements
 */

playersDLL::playersDLL(): DLL(),head(nullptr),tail(nullptr),handCount(0)
{
}

// what will happen is the base class will call its copy constructor
// to copy the dynamic list the playersDll is

// then we can just use the playersDLL copy constructor to handle the
// elements that pretain to the playersDLL
playersDLL::playersDLL(const playersDLL &playersHand): DLL(),
                                                       head(nullptr),
                                                       tail(nullptr),
                                                       handCount(0)
{
    *this = playersHand;
}


playersDLL& playersDLL::operator=(const playersDLL &aPlayersHand)
{
    if(this == &aPlayersHand)
        return *this;
    if(!aPlayersHand.head)
    {
        head = tail = nullptr;
        handCount = aPlayersHand.handCount;
        return *this;
    }

    if(head)
        destroy();
    head = nullptr;
    copyChain(head, aPlayersHand.head);
    tail = aPlayersHand.tail;
    handCount = aPlayersHand.handCount;

    return *this;

}

playersDLL::~playersDLL()
{
    destroyList(head);
    head = tail = nullptr;

}


void playersDLL::destroy()
{
    destroyList(head);
    tail = nullptr;
}



void playersDLL::display()
{
    int points = 0;
    getPoints(points);
    /* have client program check for empty before calling this*/
    DLL::displayList(head);

    cout << "\n\t Most recent draw: ";  tail->data->printSides();
         cout << " Current Points: " << points
         <<" Total Bones: " << handCount << endl;
}




void playersDLL::getPoints(int &pointTotal)
{
    getPoints(head,pointTotal);
}


void playersDLL::getPoints(DLL::node * top, int &points)
{
    if(!top)
        return;
    points += top->data->getBoneTotal();
    getPoints(top->next, points);
}


void playersDLL::addBone(const Bone &aBone)
{
    DLL::insert(head, aBone);
    tail = getEndOfHand(); // reset the tail pointer each insert
    handCount++;
}


DLL::node* playersDLL::getEndOfHand()
{

    node * curr = head;

    if(!curr)
        return curr;

    while(curr && curr->next)
        curr = curr->next;

    return curr;
}





void playersDLL::getCount(int &val)
{
    val = handCount;
}



ostream &operator<<(ostream &out, playersDLL &playersHand)
{
    playersHand.display();
    out << "********** "  << "\t********** " << endl;
    return out;

}



/**
 * yardsDLL implementations
 */

yardsDLL::yardsDLL(): DLL(),head(nullptr), boneCount(0)
{

}



void yardsDLL::createYard(const Bone &aBone)
{
    DLL::insert(head,  aBone);
    boneCount++;
}




yardsDLL::yardsDLL(const yardsDLL &aYard):DLL(aYard),
                                          head(nullptr) ,
                                          boneCount(0)
{
    *this = aYard;
}


yardsDLL& yardsDLL::operator=(const yardsDLL &aYard)
{
    if(this == &aYard)
        return *this;
    if(!aYard.head)
    {
        head = nullptr;
        boneCount = aYard.boneCount;
        return *this;
    }

    if(head)
        destroy();

    head = nullptr;
    copyChain(head, aYard.head);
    boneCount = aYard.boneCount;

    return *this;
}


yardsDLL::~yardsDLL()
{
    destroyList(head);
    head = nullptr;
}


void yardsDLL::destroy()
{
    destroyList(head);
}


void yardsDLL::drawHand(playersDLL & playersHand)
{
    int count = 0;
    drawFirstHand(head, playersHand, count);
}


void yardsDLL::drawFirstHand(DLL::node*& yard,playersDLL & aPlayer,
                             int &count)
{
    if(!yard)
        return;

    if(count == 7)
        return;
    aPlayer.addBone(*yard->data);
    drawFirstHand(yard->next, aPlayer, ++count);
    DLL::remove(yard);

}


bool yardsDLL::draw(playersDLL & playersHand)
{
    if(isEmpty(head))
        return false;


    drawBone(playersHand, head);
    return true;
}

void yardsDLL::drawBone(playersDLL& aPlayer, DLL::node *&boneYard)
{

    aPlayer.addBone(*boneYard->data);
    DLL::remove(boneYard);

}


int& yardsDLL::totalBones()
{
    return boneCount;
}




