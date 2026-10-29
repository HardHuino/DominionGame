#include "Game.hpp"
#include "Display.hpp"
#include <iostream>
using namespace std;

// Constructeur
Game::Game() : activePlayerIndex(0) {}

void Game::startGame(){
    int nbPlayers=0;
    int fastMode=false;
    // while(!(0<nbPlayers && nbPlayers<5)){ //Asks for the number of players until a valid number of player(1-4) is entered
    //     cout<<"Choose the number of players (max 4):"<<endl;
    //     cin>>nbPlayers;
    // } // remplaced by the Display::askChoice function to avoid code duplication and to have a more user-friendly input handling

    nbPlayers = Display::askChoice("Nombre de joueurs (2-4) : ", 2, 4);
    fastMode = Display::askChoice("Do you want to play in FastMode? (0 for no, 1 for yes) : ", 0, 1); //Using the askChoice since already coded

    // 1. Initializes the supply of cards (i.e. piles of cards in the middle of the board)
    supply.initializeSupply(nbPlayers); 

    // 2. Creates the players and stores them in the players vector
    for(int i=0; i<nbPlayers; i++){
        // string playerName;
        // std::cout<<"What's your name player "<<i+1<<" ?"<<endl; //Potentially to put in DISPLAY -> done
        // std::cin>>playerName;
        
        std::string name = "Joueur " + std::to_string(i + 1); // default name
        std::string typed = Display::askLine("Nom du joueur " + std::to_string(i + 1) + " : ");
        if (!typed.empty()) name = typed;

        //creates the player instance and adds it to the vector
        players.push_back(Player(name, supply));
    }

    supply.makeFastMode(static_cast<bool>(fastMode)); //Casting to bool directly as fastMode should only ever be a value of 0 or 1

    //Main game loop
    activePlayerIndex = 0;
    while (true) {
        players[activePlayerIndex].executeTurn(*this);
        if (supply.checkGameEnd()) break;
        activePlayerIndex = (activePlayerIndex + 1) % static_cast<int>(players.size());
    }
    Display::showWinner(players);
}

void Game::trashCard(std::unique_ptr<Card> card) {
    if (card) trash.push_back(std::move(card)); // the trash keeps the card alive (a played Throne Room may still point to it)
}

const Supply& Game::getSupply() const{  return supply;  } //Returns the supply of the game
Supply& Game::getSupply() { return supply; }
std::vector<Player>& Game::getPlayers(){  return players;  }
const std::vector<std::unique_ptr<Card> >& Game::getTrash() const{  return trash;  }