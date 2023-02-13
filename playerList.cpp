#include "playerList.h"

playerList::playerList():front(nullptr),back(nullptr),numPlayers(0)
{}

playerList::playerList(const playerList &aList): front(nullptr),
											     back(nullptr),
												 numPlayers(0)
{
	*this = aList;
}

playerList& playerList::operator=(const playerList &aList)
{
	if(this == &aList)
		return *this;
	if(!aList.front)
	{
		front = back = nullptr;
		numPlayers = aList.numPlayers;
		return *this;
	}

	if(front)
		destroy();
	front = new node();
	front = nullptr;
	copyChain(front, aList.front);
	back = aList.back;
	numPlayers = aList.numPlayers;

	return *this;
}

void playerList::copyChain(node *& destList, node * sourceList)
{
	if(!sourceList)
		return;
	destList = new node(*sourceList->data);
	destList->prev = sourceList->prev;
	copyChain(destList->next, sourceList->next);
}

playerList::~playerList()
{
	destroy();
}


void playerList::emptyQueue(node *& head)
{
	if(!head)
		return;
	emptyQueue(head->next);
	delete head;
}

// pass in the back of the list each time to link to back quickly.
void playerList::EnQueue(const Player &aPlayer, node *& q)
{
	if(!front)
	{
		front = new node(aPlayer);
		front->next = nullptr;
		front->prev = nullptr;
		back = front;
		numPlayers++;
	}
	node * temp = nullptr;
	temp = new node(aPlayer);
	temp->prev = q;
	q->next = temp;
	numPlayers++;
}

void playerList::Dequeue(Player & aPlayer)
{
	
	aPlayer = *front->data;
	node * temp = nullptr;
	temp = front->next;
	temp->prev = nullptr;
	delete front;
	front = temp;
	numPlayers--;
}

//  make sure client checks for empties before en/deqeue
void playerList::push(const Player & aPlayer)
{
	EnQueue(aPlayer,back);
}


void playerList::pop(Player &aPlayer)
{
	Dequeue(aPlayer);
}


bool playerList::getLeadPlayer(Player &winningPlayer)
{
	Player * winner = findLead(front);
	if(winner)
		winningPlayer = *winner;

	return winner == nullptr;

}


Player* playerList::findLead(node * head)
{
	valarray<int> scores;
	for(auto x = 0; x < numPlayers; x++)
	{
		int points = 0;
		head->data->getPoints(points);
		scores[x] = points;
	}

	int winningScore = scores.min();
	return search(head, winningScore);
}

