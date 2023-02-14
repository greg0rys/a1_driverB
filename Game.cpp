#include "Game.h"

Game::Game():
            players(nullptr),
            tiedPlayers(nullptr),
            boneYard(nullptr),
            hasBones(false),
            isTied(false),
            firstPlace(nullptr),
            numPlayers(0)

{}

Game::Game(const Game &aGame):boneYard(nullptr),
                              hasBones(false),
                              isTied(false),
                              firstPlace(nullptr),
                              numPlayers(0)
{
    *this = aGame;
}


Game& Game::operator=(const Game &aGame)
{
    if(this == &aGame)
        return *this;

    if(!aGame.boneYard)
    {
        boneYard = nullptr;
        players = aGame.players;
        hasBones = aGame.hasBones;
        if(!aGame.firstPlace)
        {
            firstPlace = nullptr;
        }
        else
        {
            firstPlace = new leadPlayer(aGame.firstPlace->playerNum,
                                        aGame.firstPlace->score);
        }
        isTied = aGame.isTied;
        numPlayers = aGame.numPlayers;
        return *this;
    }

    if(boneYard)
        delete boneYard;
    boneYard = nullptr;
    boneYard = new ChickenYard(*aGame.boneYard);
    players = aGame.players;
    hasBones = aGame.hasBones;
    if(!aGame.firstPlace)
    {
        firstPlace = nullptr;
    }
    else
    {
        firstPlace = new leadPlayer(aGame.firstPlace->playerNum,
                                    aGame.firstPlace->score);
    }
    isTied = aGame.isTied;
    numPlayers = aGame.numPlayers;

    

    return *this;
}


Game::~Game()
{
    if(boneYard)
        delete boneYard;
}


void Game::gameStart()
{
    cout << "How many players will be playing today? ";
    int totalPlayers = getInteger();
    int playerNums = 1;
    numPlayers = totalPlayers;

    cout << endl << "Generating Bone Yard " << endl;
    boneYard = new ChickenYard();

    cout << "\n\n* Adding " << totalPlayers << " players to the game.\n "
    << endl;
    createPlayersContainer(totalPlayers, playerNums);

    int before = boneYard->getCount();
    int after = 0;
    cout << "* Filling Players hands " << endl << endl;
    fillPlayersHands();

    after = boneYard->getCount();
    cout << " ** Success! Here's the hands **" << endl << endl;
    cout << "* Updating Scores " << endl << endl;

    cout << "Total bones before fill: " << before << "\tafter: " << after;
    cout << endl;
    cout << "Total players: " << players->getNumPlayers() << endl;






}


void Game::createPlayersContainer(int &playerCount,
                                  int &pNum)
{
    if(!players)
        players = new playerQueue();
    players->getNumPlayers();

    if(pNum <= numPlayers)
    {
        Player newPlayer;
        newPlayer.setPlayerNo(pNum);
        players->push(newPlayer);
        createPlayersContainer(--playerCount, ++pNum);

    }
    else
    {
        return;
    }



}



void Game::fillPlayersHands()
{
    for(auto x = 1; x <= numPlayers; x++)
    {
        Player * temp = players->getPlayer(x);
        boneYard->getHand(*temp);

    }

}








void Game::displayPlayersHands()
{
    players->display();

}







//void Game::handleTie(int &targetVal)
//{
//    int pNum, pPoints = 0;
//
//    if(isTied)
//    {
//        clearTie();
//    }
//
//    for(auto temp : players)
//    {
//        temp.getPlayerNo(pNum);
//        temp.getPoints(pPoints);
//        if(pPoints == targetVal)
//            tiedPlayers.push_back(temp);
//    }
//}
//
//
//void Game::clearTie()
//{
//    if(!isTied)
//        return;
//    // delete the vector of tied players each time so its accurate
//    for(auto start = tiedPlayers.begin(); start != tiedPlayers.end();)
//    {
//        start  = tiedPlayers.erase(start);
//        start++;
//    }
//}

