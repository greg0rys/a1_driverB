#include "Player.h"
#include <iostream>
#include <valarray>

using namespace std;

class playerList
{
	private:
		struct node
		{
			Player * data;
			node * next;
			node * prev;

			node()
			{
				data = nullptr;
				next = prev = nullptr;
			}

			explicit node(const Player &aPlayer)
			{
				data = new Player(aPlayer);
				next = prev = nullptr;
			}

			~node()
			{
				if(data)
					delete data;
				data = nullptr;
				next = prev = nullptr;
			}
		};

		node * front;
		node * back;
		int	   numPlayers;
		void displayQueue(node *);
		void Dequeue(Player &);
		void EnQueue(const Player &, node *&);
		Player * findLead(node *);
		void emptyQueue(node *&);
		void copyChain(node *&, node *);
		Player * search(node *, int &);

	public:
		playerList();
		playerList(const playerList &);
		playerList& operator=(const playerList &);
		~playerList();
		void destroy(){emptyQueue(front);}
		void peekFront(Player &);
		void pop(Player &);
		void push(const Player &);
		int& getNumPlayers(){return numPlayers;}
		bool getLeadPlayer(Player &);
		bool isEmpty();

};
