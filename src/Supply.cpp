#include "Supply.hpp"
#include "TreasureCard.hpp"
#include "VictoryCard.hpp"

#include <cctype>
#include <stdexcept>
#include <utility>

using namespace std;

template <class T, class... Args>
void Supply::addPile(int quantity, Args... args) {
    CardPile pile(std::unique_ptr<Card>(new T(args...)));
    for (int i = 0; i < quantity; ++i)
        pile.addCard(std::unique_ptr<Card>(new T(args...)));
    const std::string name = pile.getName();
    piles.emplace(name, std::move(pile));
}

std::unique_ptr<Card> Supply::takeCard(const std::string& name) {
    CardPile* pile = getPile(name);
    return pile ? pile->takeCard() : nullptr;
}

void Supply::initializeSupply(int numPlayers){ //Setsup the Game depending on the number of players
    const int victory = (numPlayers == 2) ? 8 : 12;

    // Treasure cards
    addPile<TreasureCard>(60, std::string("Copper"), 0, 1);
    addPile<TreasureCard>(40, std::string("Silver"), 3, 2);
    addPile<TreasureCard>(30, std::string("Gold"),   6, 3);

    // Victory cards
    addPile<VictoryCard>(victory, std::string("Estate"),   2,  1);
    addPile<VictoryCard>(victory, std::string("Duchy"),    5,  3);
    addPile<VictoryCard>(victory, std::string("Province"), 8,  6);
    addPile<VictoryCard>(30, std::string("Curse"),    0, -1);
}

bool Supply::checkGameEnd() const{ //Counts number of empty piles to check if game ends
    int nbEmptyPiles=0;
    for (auto& i : piles){ //Runs through all the piles
        if(i.second.getQuantity()<=0){ //Checks if that pile is empty
            //-------TO BE IMPLEMENTED
            if(i.first==""){ //If the pile is empty and it's the one pile that ends the game immediately
                return true; 
            }
            else{ //Otherwise just adds one to the number of empty piles
                nbEmptyPiles+=1;
            }
        }
    }
    if (nbEmptyPiles>=3){ //Checks if there are at least 3 empty piles
        return true;
    }
    return false;
}

// Getters

CardPile* Supply::getPile(const string& name){
    for (auto& i : piles){ //Searches through all of the pile (the map containing names and their associated CardPile)
        if(i.first==name){ //If name matches
            return &i.second; //Returns the pointer to the CardPile
        }
    }
    throw "Name not found in Piles"; //Throws an error if the name doesn't match
}

const std::map<std::string, CardPile>& Supply::getPiles() const{    return piles;   } //Returns the map of piles