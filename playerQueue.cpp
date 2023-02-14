#include "playerQueue.h"

playerQueue::playerQueue(): front(nullptr), back(nullptr), numPlayers(0)
{}

playerQueue::playerQueue(const playerQueue &aList): front(nullptr),
                                                    back(nullptr),
                                                    numPlayers(0)
{
	*this = aList;
}

playerQueue& playerQueue::operator=(const playerQueue &aList)
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

void playerQueue::copyChain(node *& destList, node * sourceList)
{
	if(!sourceList)
		return;
	destList = new node(*sourceList->data);
	destList->prev = sourceList->prev;
	copyChain(destList->next, sourceList->next);
}

playerQueue::~playerQueue()
{
	destroy();
}


void playerQueue::emptyQueue(node *& head)
{
	if(!head)
		return;
	emptyQueue(head->next);
	delete head;
}

// pass in the back of the list each time to link to back quickly.
void playerQueue::EnQueue(const Player &aPlayer, node *& q)
{
    node * temp = nullptr;
    temp = new node(aPlayer);

	if(!q)
	{
        front = q = temp;
        numPlayers++;
        return;
	}

    temp->prev = q;
    q->next = temp;
    q = temp;
    numPlayers++;

}

void playerQueue::remove(Player &aPlayer)
{
	// have client check for empty;
    node * temp = nullptr;

    aPlayer = *front->data;

	temp = front->next;
	temp->prev = nullptr;
	delete front;
	front = temp;
	numPlayers--;
}

Player* playerQueue::findLead(node * head)
{
	valarray<int> scores;
    int idx = 0;

	for(auto it = begin(scores); idx < numPlayers; idx++)
	{
		int points = 0;
		head->data->getPoints(points);
		*it = points;
	}

	int winningScore = scores.min();
    int matches = 0;
	return search(head, winningScore,matches);
}



Player *playerQueue::search(playerQueue::node * start,
                            int &targetScore,
                            int &matchCount)
{

    if(!start)
        return nullptr;

    Player * leadPlayer = nullptr;

    int currPoints = 0;
    start->data->getPoints(currPoints);

    if(currPoints == targetScore)
        return start->data;

    // check the next one;
    leadPlayer = search(start->next, targetScore, matchCount);
    // if the next one is a match then search the next next
    if(leadPlayer)
    {
        matchCount += 1;
        leadPlayer =  search(start->next->next, targetScore, matchCount);
    }
    else
    {
        // if the lead player is null the first time, then check next next
        leadPlayer = search(start->next->next, targetScore, matchCount);
    }

    return leadPlayer; // finally at the end


}


void playerQueue::displayQueue(playerQueue::node *start)
{
    if(!start)
        return;
    // set the player up to print all its info when <<
    cout << *start->data << endl;
    displayQueue(start->next);
}


bool playerQueue::peekFront(Player &firstPlayer)
{
    firstPlayer = *(front->data);
}


bool playerQueue::pop(Player & removedPlayer)
{
    if(isEmpty())
        return false;
    remove(removedPlayer); // this will copy the removed front to the player
    // ref
    return true;
}


bool playerQueue::push(const Player &aPlayer)
{
    EnQueue(aPlayer, back);
}


bool playerQueue::getLeadPlayer(Player &winningPlayer)
{
    winningPlayer = *findLead(front);
    return true;
}


bool playerQueue::isEmpty()
{
    return front;
}



Player *playerQueue::getPlayer(int num)
{
    int pNo = 0;

    Player * matchingP = nullptr;
    for(auto curr = front; curr; curr = curr->next)
    {
        curr->data->getPlayerNo(pNo);
        matchingP = (pNo == num) ? curr->data : nullptr;
        pNo++;

        if(matchingP)
            return curr->data;

    }

    return matchingP;
}






