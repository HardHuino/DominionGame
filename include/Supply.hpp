#ifndef SUPPLY_HPP
#define SUPPLY_HPP
#include <map>
#include <string>
#include "CardPile.hpp"
using namespace std;
class Supply{
private:
    map<string, CardPile> piles;

    template <class T, class... Args>
    void addPile(int quantity, Args... args); // Helper function to add a pile of cards to the supply

public:
    void initializeSupply(int numPlayers);

    std::unique_ptr<Card> takeCard(const std::string& name); // nullptr if not found or empty

    bool checkGameEnd() const;

    // Getters
    CardPile* getPile(const string& name); // nullptr if not found
    const map<string, CardPile>& getPiles() const;

};
#endif