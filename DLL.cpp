#include "DLL.h"

#include <utility>

DLL::DLL():head(nullptr),tail(nullptr),listSize(0)
{}


DLL::DLL(const DLL &aCopy):head(nullptr),tail(nullptr),listSize(0)

{
    *this = aCopy;
}

 DLL& DLL::operator=(const DLL &aCopy)
{
    if(this == &aCopy)
        return *this;

    if(isEmpty())
    {
        head = tail = nullptr;
        listSize = aCopy.listSize;
        return *this;
    }

    if(head)
        destroy();

    copyChain(head, aCopy.head);
    tail = getTail();
    listSize = aCopy.listSize;

    return *this;
}


DLL::~DLL()
{
    if(isEmpty())
    {
        head = tail = nullptr;
        return;
    }

    destroy();
    head = tail = nullptr;
}


void DLL::destroy()
{
    destroyList(head);
}


void DLL::destroyList(DLL::node *& top)
{
    if(!top || isEmpty())
        return;

    destroyList(top->next);
    delete top;
}


void DLL::getCount(int &counter)
{
    if(isEmpty())
    {
        counter = 0;
        return;
    }

    countChain(head, counter);
}



void DLL::countChain(DLL::node *top, int &counter)
{
    if(!top || isEmpty())
        return;

    countChain(top->next, ++counter);

}


bool DLL::isEmpty()
{
    return head;
}


void DLL::copyChain(DLL::node *& destList, DLL::node * sourceList)
{


    if(!sourceList)
        return;

    destList = new node(*sourceList->data);
    destList->prev = sourceList->prev;

    copyChain(destList->next, sourceList->next);
}


DLL::node* DLL::getHead()
{
    return head;
}


void DLL::setHead(const Bone &aBone)
{
    if(!head)
    {
        head = new node();
        *(head->data) = aBone;
        head->next = nullptr;
        head->prev = nullptr;
        tail = head;
    }

    node * temp = nullptr;
    temp = new node();
    *(temp->data) = aBone;
    head->prev = temp;
    temp->next = head;
    head = temp;

}


DLL::node* DLL::getTail()
{
    auto * curr = head;

    while(curr && curr->next)
        curr = curr->next;

    // special check to make sure that the tail pointer is actually
    // pointing at the last item - if their totals differ set tail to curr
    // which at this point is the end of the list.
    if(curr->data->getBoneTotal() != tail->data->getBoneTotal())
        tail = curr;

    return tail;

}


void DLL::setTail(DLL::node * newTail)
{
    tail = newTail;
}


void DLL::insert(const Bone &aBone)
{
    if(!head)
    {
        head = new node(aBone);
        head->prev = nullptr;
        head->next = nullptr;
    }
    node * curr = head;
    node * temp = nullptr;

    while(curr && curr->next)
        curr = curr->next;

    temp = new node(aBone);
    temp->prev = curr;
    curr->next = temp;
    tail = temp;

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

void DLL::display()
{
    displayList(head);
}



/**
 * playerList implements
 */

playersDLL::playersDLL(): DLL(),handCount(0),recentDraw(nullptr)
{
}

// what will happen is the base class will call its copy constructor
// to copy the dynamic list the playersDll is

// then we can just use the playersDLL copy constructor to handle the
// elements that pretain to the playersDLL
playersDLL::playersDLL(const playersDLL &playersHand): DLL(),
                                                       recentDraw(nullptr),
                                                       handCount(0)
{
    *this = playersHand;
}


playersDLL& playersDLL::operator=(const playersDLL &aPlayersHand)
{
    if(this == &aPlayersHand)
        return *this;

    int copiesHand = 0;

    if(aPlayersHand.recentDraw)
    {
        if(recentDraw)
            delete recentDraw;
        recentDraw = nullptr;
        recentDraw = new Bone(*aPlayersHand.recentDraw);
    }
    else
    {
        recentDraw = nullptr;
    }

    getCount(copiesHand);
    handCount = copiesHand;

    return *this;

}

playersDLL::~playersDLL()
{
    if(recentDraw)
        delete recentDraw;

    recentDraw = nullptr;
    handCount = 0;

}



void playersDLL::display()
{
    int points = 0;
    getPoints(points);
    /* have client program check for empty before calling this*/
    DLL::displayList(getHead());

    cout << "\n\t Most recent draw: " << recentDraw
         << " Current Points: " << points << endl;
}


void playersDLL::displayList(DLL::node * start)
{
    static int formatter = 1;

    if(!start || isEmpty())
        return;
    start->data->printSides();

    if(formatter % 5 == 0)
        cout << endl;
    formatter++;
    displayList(start->next);

}



void playersDLL::getPoints(int &pointTotal)
{
    getPoints(getHead(),pointTotal);
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
    DLL::insert(aBone);
}


Bone& playersDLL::getEnd()
{
    return *getTail()->data;
}



ostream &operator<<(ostream &out, playersDLL &playersHand)
{
    playersHand.display();
    out << "********** " << endl;
    return out;

}



/**
 * yardsDLL implementations
 */

yardsDLL::yardsDLL(): DLL(),boneCount(0)
{

}



void yardsDLL::createYard(const Bone &aBone)
{
    DLL::insert(aBone);
    boneCount++;
}




yardsDLL::yardsDLL(const yardsDLL &aYard):DLL(aYard),boneCount(aYard.boneCount)
{
    *this = aYard;
}





void yardsDLL::drawHand(playersDLL & playersHand)
{
    int count = 0;
    drawFirstHand(playersHand, count);
}


void yardsDLL::drawFirstHand(playersDLL & aPlayer, int & count)
{
    cout << "drawing first hand";
    if(!isEmpty())
        return;

    if(count == 7)
        return;

    node * yardCurrent = getHead();
    Bone & currentBone = *getHead()->data;

    aPlayer.addBone(currentBone);
    remove(yardCurrent);
    drawFirstHand(aPlayer, ++count);
}


bool yardsDLL::draw(playersDLL & playersHand)
{
    // gaurd from drawing on an empty pointer.
    if(isEmpty())
        return false;
    node * yardCurrent = nullptr;
    yardCurrent = getHead();

    drawBone(playersHand, yardCurrent);
    return true;
}

void yardsDLL::drawBone(playersDLL& aPlayer, DLL::node *&boneYard)
{

    aPlayer.addBone(*boneYard->data);
    remove(boneYard);

}




