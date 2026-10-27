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

static std::string toLower(std::string s) { // Converts a string to lowercase
    for (std::size_t i = 0; i < s.size(); ++i)
        s[i] = static_cast<char>(std::tolower(static_cast<unsigned char>(s[i])));
    return s;
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
        if(i.second.isEmpty()){ //Checks if that pile is empty
            nbEmptyPiles++; //Increments the number of empty piles
        }
    }
    return piles.at("Province").isEmpty() || nbEmptyPiles >= 3;
}

// Getters

CardPile* Supply::getPile(const string& name){
    const std::string wanted = toLower(name);
    for (auto& p : piles) { //Searches through all of the pile (the map containing names and their associated CardPile)
        if (toLower(p.first) == wanted){ //If name matches
            return &p.second; //Returns the pointer to the CardPile
        }
    }
    return nullptr; //return nullptr if the name doesn't match
}

const std::map<std::string, CardPile>& Supply::getPiles() const{    return piles;   } //Returns the map of piles