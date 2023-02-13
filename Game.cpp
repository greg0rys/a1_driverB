#include "Game.h"

Game::Game():boneYard(nullptr)
            ,hasBones(false)
            , isTied(false)
            ,leadPlayer(0)
            , leadPoints(0)
            , numPlayers(0)

{}

Game::Game(const Game &aGame):boneYard(nullptr),
                              hasBones(false),
                              isTied(false),
                              leadPlayer(0),
                              leadPoints(0),
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
        leadPlayer = aGame.leadPlayer;
        isTied = aGame.isTied;
        numPlayers = aGame.numPlayers;
        leadPoints = aGame.leadPoints;

        return *this;
    }

    if(boneYard)
        delete boneYard;
    boneYard = nullptr;
    boneYard = new ChickenYard(*aGame.boneYard);
    players = aGame.players;
    hasBones = aGame.hasBones;
    leadPlayer = aGame.leadPlayer;
    isTied = aGame.isTied;
    numPlayers = aGame.numPlayers;
    leadPoints = aGame.leadPoints;


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
    numPlayers = totalPlayers;

    cout << endl << "Generating Bone Yard " << endl;
    boneYard = new ChickenYard();

    cout << "\n\n* Adding " << totalPlayers << " players to the game.\n "
    << endl;
    createPlayersContainer(totalPlayers);

    int before = boneYard->getCount();
    int after = 0;
    cout << "* Filling Players hands " << endl << endl;
    fillPlayersHands();

    after = boneYard->getCount();
    cout << " ** Success! Here's the hands **" << endl << endl;
    cout << "* Updating Scores " << endl << endl;
    updateScores();
    displayPlayersHands();

    cout << "Total bones before fill: " << before << "\tafter: " << after;
    cout << endl;

    getRoundResults();




}


void Game::createPlayersContainer(int &numPlayers)
{
    int no = 1;
    if(numPlayers == 0)
    {
        return;
    }
    Player newPlayer;
    newPlayer.setPlayerNo(no++);
    players.push_back(newPlayer);
    createPlayersContainer(--numPlayers);

}



void Game::fillPlayersHands()
{
    for(Player & p: players)
    {
        boneYard->getHand(p);
    }

}


void Game::updateScores()
{

    int pPoints = 0;
    int num = 0;
    players[0].getPoints(leadPoints);
    cout << "current lead " << leadPoints << endl;


    for(auto & player : players)
    {
        pPoints = 0;
        player.getPoints(pPoints);
        player.getPlayerNo(num);

        if(leadPoints > pPoints)
        {
            leadPoints = pPoints;
            leadPlayer = num;

        }

    }


}





void Game::displayPlayersHands()
{
    for(Player & p: players)
    {
        p.displayHand();
    }

}


void Game::getRoundResults()
{
    int playerNum, points = 0;
    Bone * recentBone = nullptr;

    for(auto x = players.begin(); x != players.end(); x++)
    {
        x->getPlayerNo(playerNum);
        x->getPoints(points);
        recentBone = &x->getLastDraw();

        cout << "*** Player Num: " << playerNum << " *** \n\t";
        cout << "Currently has: " << points << " point(s) "
             << "Most recent bone draw: "; recentBone->printSides();
             cout << "*** End of Player: " << playerNum << " results  ***";
             cout << endl;
             points = 0;
    }

    cout << endl << endl;
    cout << "****** CURRENT WINNER ******\n";
    cout << "Player " << leadPlayer << " has the winning score of: "
         << leadPoints << endl;
    cout << "****** END OF GAME STATS ******\n\n";

}






void Game::handleTie(int &targetVal)
{
    int pNum, pPoints = 0;

    if(isTied)
    {
        clearTie();
    }

    for(auto temp : players)
    {
        temp.getPlayerNo(pNum);
        temp.getPoints(pPoints);
        if(pPoints == targetVal)
            tiedPlayers.push_back(temp);
    }
}


void Game::clearTie()
{
    if(!isTied)
        return;
    // delete the vector of tied players each time so its accurate
    for(auto start = tiedPlayers.begin(); start != tiedPlayers.end();)
    {
        start  = tiedPlayers.erase(start);
        start++;
    }
}

