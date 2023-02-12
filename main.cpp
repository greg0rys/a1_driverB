#include <unistd.h>
#include "main.h"


void printStats(ChickenYard * yard, Player * player1, Player * player2)
{
    static int roundCounter = 1;
    int p1Score = 0, p2Score = 0;
    player1->getPoints(p1Score);
    player2->getPoints(p2Score);
    cout << " ROUND: " << roundCounter++ << endl;
    cout << "\tTotal Bones: " << yard->getCount() << endl;
    cout << "\tScores: \t" << "Player 1: " << p1Score
         << "\t Player 2: " << p2Score << endl;

	cout << endl;
	cout << " ********** Players info ********** " << endl;
    cout <<  *player1 << endl;
	cout <<  *player2 << endl;
	cout << endl;

	cout << " ********** NEXT ROUND ********** " << endl << endl;
}


void gameStart()
{
    auto * yard = new ChickenYard();
    auto * player1 = new Player();
    auto * player2 = new Player();
    yard->getHand(player1);
    Bone temp;
    player1->addToHand(temp);
    player1->displayHand();



}

void gamePlay(ChickenYard *& yard, Player *& p1, Player *& p2)
{
	while(yard->getCount() != 0)
	{
		sleep(1);
		yard->draw(p1);
		yard->draw(p2);
		printStats(yard,p1,p2);
	}

	cout << endl;
	gameEnd(yard, p1, p2);
}


void gameEnd(ChickenYard *& yard, Player *& p1, Player *& p2)
{
	int p1score = 0, p2score = 0;
	int p1No = 0, p2No = 0;

	p1->getPoints(p1score);
	p2->getPoints(p2score);

	p1->getPlayerNo(p1No);
	p2->getPlayerNo(p2No);

	int winningScore = (p1score < p2score ? p1score : p2score);


	cout << "    \t\t\tFinal Stats:    " << endl;
	cout << "Player " << p1No << "\n\t Final Score: " << p1score
		 << "\n Player " << p2No << "\n\t Final Score: " << p2score
		 << endl << endl;
	cout << "The winner is Player " << (p1score < p2score ? p1No : p2No)
		 << " with the winning score of: " << winningScore << endl;

	cout << "Thanks for playing! " << endl;

	if(yard)
		delete yard;
	if(p1)
		delete p1;
	if(p2)
		delete p2;
}
	

int main()
{
   gameStart();

    return 0;
}





