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



        node(const Bone &aBone)
        {
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


    void insert(DLL::node *&, const Bone &);
    static void remove(DLL::node *&);

    void destroyList(node *&);

    void copyChain(node *&, node *);

    void countChain(node *, int &);

    static bool isEmpty(node *);

    node*& getList();

public:
    DLL() = default;

    DLL(const DLL &);

   virtual ~DLL();
    // when you have a pure virtual function all derived classes MUST
    // implement their own version of the pure virtual function as a vitural
    // function. or it will not compile.
    virtual void display() = 0;
    // may need to redefine display in base class





};


class playersDLL : public DLL
{

private:

	node * head;
	node * tail;
    int handCount; // store the count so we don't have to recurse each time
	const static int START_SIZE = 7;
    void getPoints(DLL::node *, int &);
    node* getEndOfHand();
    node*& getStartofHand();
    virtual void displayList(node *);


public:
    playersDLL();

    playersDLL(const playersDLL &);

    playersDLL & operator=(const playersDLL &);

    virtual ~playersDLL();
    virtual void destroy();

     void display() override;

    void getPoints(int &);


    void addBone(const Bone &);
    virtual void getCount(int &);
    Bone& getRecentDraw(){
        return *tail->data;
    }


};

class yardsDLL : public DLL
{

private:

#define YARD_SIZE 52
    typedef std::array<Bone, YARD_SIZE> boneArray;
	node * head;
    int boneCount;

    void drawFirstHand(DLL::node *&, playersDLL &, int &);
    void drawBone(playersDLL &, DLL::node*&);
    virtual void displayList(node *);


public:
    yardsDLL();
    yardsDLL(const yardsDLL &);
    yardsDLL& operator=(const yardsDLL &);
    virtual ~yardsDLL();
    virtual void destroy();
    void createYard(const Bone &);
    void drawHand(playersDLL &);
    bool draw(playersDLL &);
    int& totalBones();
    virtual void display() {
       displayList(head);
    }



};
