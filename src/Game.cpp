#include "Game.hpp"
#include <iostream>
using namespace std;
// Constructeur
Game::Game(const std::vector<Player>& players, const Supply& supply):players(players), supply(supply){}

void Game::startGame(){ //------UNFINISHED
    int nbPlayers=0;
    while(!(0<nbPlayers && nbPlayers<5)){ //Asks for the number of players until a valid number of player(1-4) is entered
        cout<<"Choose the number of players (max 4):"<<endl;
        cin>>nbPlayers;
    }
    //Initializes the supply of cards (i.e. piles of cards in the middle of the board)
    supply.initializeSupply(nbPlayers);
    //Creates the players and stores them in the players vector
    for(int i=0; i<nbPlayers; i++){
        string playerName;
        cout<<"What's your name player "<<i+1<<" ?"<<endl;
        cin>>playerName;
        //--------TO BE IMPLEMENTED (creating the player instance and adding it to the vector)
        //players.push_back(new Player(playerName));
    }
}

const Supply& Game::getSupply() const{ //Returns the supply of the game
    return supply;
}