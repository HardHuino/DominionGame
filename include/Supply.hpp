#ifndef SUPPLY_HPP
#define SUPPLY_HPP
#include <map>
#include <string>
#include "CardPile.hpp"
using namespace std;
class Supply{
    private:
    map<string, CardPile> piles;

    public:
    void initializeSupply(int numPlayers);
    CardPile* getPile(const string& name);
    const map<string, CardPile>& getPiles() const;
    bool checkGameEnd() const;
};
#endif