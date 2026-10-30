#ifndef SUPPLY_HPP
#define SUPPLY_HPP
#include <map>
#include <string>
#include <vector>
#include "CardPile.hpp"
using namespace std;
class Supply{
private:
    map<string, CardPile> piles;

    template <class T, class... Args>
    void addPile(int quantity, Args... args); // Helper function to add a pile of cards to the supply

    void addKingdomPile(const std::string& name); // Adds the pile of the kingdom card called "name" (throws std::invalid_argument if unknown)

public:
    // Description of one of the 25 kingdom cards that can be put in the game (used by the kingdom selection menu)
    struct KingdomCardInfo {
        std::string name;
        int cost;
        std::string description;
    };

    // All the kingdom cards (Action cards + Garden) that can be chosen, in alphabetical order
    static std::vector<KingdomCardInfo> getKingdomCatalog();

    // Treasures, Victory cards, Curses + the kingdom cards listed in kingdomNames (10 names expected)
    void initializeSupply(int numPlayers, const std::vector<std::string>& kingdomNames);

    void makeFastMode(bool fastMode);

    std::unique_ptr<Card> takeCard(const std::string& name); // nullptr if not found or empty

    bool checkGameEnd() const;

    static std::unique_ptr<Card> makeKingdomCard(const std::string& name); // nullptr si inconnue

    // Getters
    CardPile* getPile(const string& name); // nullptr if not found
    const map<string, CardPile>& getPiles() const;

};
#endif