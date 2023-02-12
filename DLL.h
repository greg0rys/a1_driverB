#pragma once
#include "Bone.h"
#include <iostream>
#include <cstring>
#include <cctype>
#include <fstream>
#include <array>

using namespace std;

class DLL
{

protected:
    struct node
    {
        node *next, *prev;
        Bone *data;



        node()
        {
            next = prev = nullptr;
            data = nullptr;
        }



        explicit node(const Bone &aBone)
        {
            if (data)
                delete data;
            data = new Bone(aBone);
            prev = next = nullptr;
        }



        ~node()
        {
            if (data)
                delete data;
            next = prev = nullptr;
            data = nullptr;
        }



        void setData(const Bone &aBone)
        {
            if (data)
                delete data;
            data = new Bone(aBone);
        }
    };
    node *getHead();

    void setHead(const Bone &); // don't create nodes using the new operator
    // that
    // use this method.
    node *getTail();

    void setTail(node *);


    void insert(const Bone &);
    void remove(DLL::node *&);

    virtual void displayList(node *);

    void destroyList(node *&);


    void copyChain(node *&, node *);

    void countChain(node *, int &);

    node*& getList();

public:
    DLL();

    DLL(const DLL &);

    DLL &operator=(const DLL &);

   virtual ~DLL();
    // doesn't need to be virtual because
    // all derived classes will use the destroy method in the same way
    void destroy();
    // when you have a pure virtual function all derived classes MUST
    // implement their own version of the pure virtual function as a vitural
    // function. or it will not compile.
    virtual void display() = 0;

    void getCount(int &);

    bool isEmpty();

};


class playersDLL : public DLL
{

private:

	node * head;
	node * tail;
    int handCount;
	const static int START_SIZE 7
    void getPoints(DLL::node *, int &);

    virtual void displayList(DLL::node *);


public:
    playersDLL();

    playersDLL(const playersDLL &);

    playersDLL & operator=(const playersDLL &);

    virtual ~playersDLL();

     void display() override;

    void getPoints(int &);

    // return a ref to the handcount already stored so we don't create more
    int& getHandCount() { return handCount;}

    friend ostream& operator<<(ostream&, playersDLL &);


    void addBone(const Bone &);
    Bone& getEnd();


};

class yardsDLL : public DLL
{

private:
	node * head;
#define YARD_SIZE 52

    yardsDLL(array<Bone, 52> bones);

    typedef std::array<Bone, YARD_SIZE> boneArray;

    int boneCount;
    void displayList();
    void firstFill(DLL::node *&, DLL::node *, boneArray bArray, int &);
    void drawFirstHand(playersDLL &, int &);
    void drawBone(playersDLL &, DLL::node*&);


public:
    yardsDLL();
    yardsDLL(const yardsDLL &);
    virtual ~yardsDLL()
    {

    }
    void createYard(const Bone &);
    void drawHand(playersDLL &);
    bool draw(playersDLL &);
    virtual void display() {
        DLL::displayList(getHead());
    }



};
