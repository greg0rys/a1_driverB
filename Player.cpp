#include "Player.h"

/*
 * Default constructor
 */
Player::Player(): hand(new playersDLL()), points(0),
                                          handCount(0),
                                          playerNo(0),
                                          firstHand(true)
{

}

/*
 * Copy Constructor
 * TODO: edit copy chain method to copy a double linked list rather than single
 */
Player::Player(const Player &aPlayer): hand(nullptr),
                                       points(0),
                                       handCount(0),
                                       playerNo(0),
                                       firstHand(aPlayer.isFirstHand())
{
    *this = aPlayer;
}


/*
 * Overloaded operator= create deep copies of player objects
 */
Player& Player::operator=(const Player &aPlayer)
{
    if(this == &aPlayer)
        return *this;

    if(!aPlayer.hand)
    {
        hand = nullptr;
        points = aPlayer.points;
        handCount = aPlayer.handCount;
        firstHand = aPlayer.firstHand;
        playerNo = aPlayer.playerNo;
        return *this;
    }

        if(hand)
            delete hand;

        hand = nullptr;
        hand = new playersDLL(*aPlayer.hand);


    handCount = aPlayer.handCount;
    points = aPlayer.points;
    firstHand = aPlayer.firstHand;
    playerNo = aPlayer.playerNo;

    return *this;
}


/*
 * Class Destructor
 */
Player::~Player()
{
    if(hand)
        delete hand;

    hand = nullptr;
}



/*
 * Check to see if this is the first time the players hand has been dealt.
 */
bool Player::isFirstHand() const
{
    return firstHand;
}





/*
 * Create a double linked list by getting bone objects passed to the player's
 * hand from the ChickenYard. The yard manages this by first giving a copy
 * of the bone obj stored in the list and then removing it from the yard
 */



/*
 * Add a bone to the players hand, this will automatically place the new
 * bone at the front of the double linked lst.
 */
void Player::addToHand(const Bone & aBone)
{
   hand->addBone(aBone);
   handCount++;

}


/*
 * Get the last bone in the players hand.
 */


/*
 * Calculate the total number of points the player currently has.
 */
void Player::getPoints(int &score)
{
    hand->getPoints(score);
}




/*
 * Recurse the players hand to display it.
 */
void Player::displayHand()
{
    hand->display();
    cout << endl << endl;
}

/*
 * Recurse the players hand to display it
 */



ostream &operator<<(ostream &out,  Player &aPlayer)
{
    out << endl;
    aPlayer.displayHand();
    return out;
}


void Player::setPlayerNo(const int playerNum)
{
    this->playerNo = playerNum;
}

void Player::getPlayerNo(int & playerNum) const
{
    playerNum = playerNo;
}

playersDLL& Player::getHand()
{
    return *hand;
}



bool operator==(const Player &p1, const Player &p2)
{
    return p1.points == p2.points;
}


