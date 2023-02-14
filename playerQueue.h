#include "Player.h"

#include <iostream>
#include <valarray>

using namespace std;

class playerQueue
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
		void remove(Player &);
		void EnQueue(const Player &, node *&);
		Player * findLead(node *);
		void emptyQueue(node *&);
		void copyChain(node *&, node *);
		Player * search(node *, int &, int &);

	public:
		playerQueue();
		playerQueue(const playerQueue &);
		playerQueue& operator=(const playerQueue &);
		~playerQueue();
		void destroy(){emptyQueue(front);}
		bool peekFront(Player &);
		bool pop(Player &);
		bool push(const Player &);
		int& getNumPlayers(){return numPlayers;}
		bool getLeadPlayer(Player &);
		bool isEmpty();
        Player* getPlayer(int );
        void display()
        {
            displayQueue(front);
        }

};
