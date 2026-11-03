#include "Supply.hpp"
#include "TreasureCard.hpp"
#include "VictoryCard.hpp"
#include "Adventurer.hpp"
#include "Bureaucrat.hpp"
#include "Cellar.hpp"
#include "Chancellor.hpp"
#include "Chapel.hpp"
#include "CouncilRoom.hpp"
#include "Feast.hpp"
#include "Festival.hpp"
#include "Laboratory.hpp"
#include "Library.hpp"
#include "Market.hpp"
#include "Militia.hpp"
#include "Mine.hpp"
#include "Moat.hpp"
#include "MoneyLender.hpp"
#include "Remodel.hpp"
#include "Smithy.hpp"
#include "Spy.hpp"
#include "Thief.hpp"
#include "ThroneRoom.hpp"
#include "Village.hpp"
#include "Witch.hpp"
#include "Woodcutter.hpp"
#include "Workshop.hpp"

#include <cctype>
#include <stdexcept>
#include <utility>

static std::string toLower(std::string s) { // Converts a string to lowercase (and remove spaces)
    std::string r;
    for (char c : s) if (c != ' ') r += static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    return r;
}

// One entry of the kingdom catalog : how to build the cards of the pile + what the card does (for the selection menu)
struct KingdomEntry {
    std::string description;
    int quantity;
    std::function<std::unique_ptr<Card>()> create;
};

template <class T> // for the vector of kingdomEntries
std::unique_ptr<Card> makeCard() {
    return std::unique_ptr<Card>(new T());
}

std::unique_ptr<Card> makeGarden() { // special victory card
    return std::unique_ptr<Card>(new VictoryCard("Garden", 4, 0, true));
}

// The 25 kingdom cards of the first edition (alphabetical order). Garden is a Victory card but is a kingdom card too.
const std::vector<KingdomEntry>& kingdomEntries() {
    static const std::vector<KingdomEntry> entries = {
        { "Reveal cards until 2 Treasures are revealed : take them into hand, discard the rest.", 10, &makeCard<Adventurer> },
        { "Receive a Silver on your draw pile. Opponents put a Victory card on their draw pile. (Attack)", 10, &makeCard<Bureaucrat> },
        { "+1 Action. Discard N cards, draw N cards.", 10, &makeCard<Cellar> },
        { "+2 Coins. You may put your draw pile into the discard pile.", 10, &makeCard<Chancellor> },
        { "Discard up to 4 cards from your hand.", 10, &makeCard<Chapel> },
        { "+4 Cards, +1 Buy. Each opponent draws 1 card.", 10, &makeCard<CouncilRoom> },
        { "Discard this card. Receive a card costing up to 5.", 10, &makeCard<Feast> },
        { "+2 Actions, +1 Buy, +2 Coins.", 10, &makeCard<Festival> },
        { "1 victory point per group of 10 cards in your deck.", 12, &makeGarden },
        { "+2 Cards, +1 Action.", 10, &makeCard<Laboratory> },
        { "Draw until you have 7 cards in hand (you may set aside the Actions drawn).", 10, &makeCard<Library> },
        { "+1 Card, +1 Action, +1 Buy, +1 Coin.", 10, &makeCard<Market> },
        { "+2 Coins. Opponents discard down to 3 cards in hand. (Attack)", 10, &makeCard<Militia> },
        { "Discard a Treasure from your hand: gain a Treasure costing up to 3 more.", 10, &makeCard<Mine> },
        { "+2 Cards. You are protected from attacks (reaction).", 10, &makeCard<Moat> },
        { "Discard a Copper from your hand: +3 Coins.", 10, &makeCard<MoneyLender> },
        { "Discard a card from your hand: gain a card costing up to 2 more.", 10, &makeCard<Remodel> },
        { "+3 Cards.", 10, &makeCard<Smithy> },
        { "+1 Card, +1 Action. Each player reveals their first card, you choose to discard it or not. (Attack)", 10, &makeCard<Spy> },
        { "Opponents reveal 2 cards and discard a Treasure of your choice, which you may take. (Attack)", 10, &makeCard<Thief> },
        { "Play an Action card from your hand twice.", 10, &makeCard<ThroneRoom> },
        { "+1 Card, +2 Actions.", 10, &makeCard<Village> },
        { "+2 Cards. Each opponent receives a Curse. (Attack)", 10, &makeCard<Witch> },
        { "+1 Buy, +2 Coins.", 10, &makeCard<Woodcutter> },
        { "Receive a card costing up to 4.", 10, &makeCard<Workshop> }
    };
    return entries;
}

// Trouve l'entrée dont la carte s'appelle 'name' (insensible à la casse), sinon nullptr
const KingdomEntry* findEntry(const std::string& name) {
    const std::string wanted = toLower(name);
    for (const KingdomEntry& e : kingdomEntries())
        if (toLower(e.create()->getName()) == wanted) return &e;
    return nullptr;
}

std::unique_ptr<Card> Supply::makeKingdomCard(const std::string& name) {
    const KingdomEntry* e = findEntry(name);
    return e ? e->create() : nullptr;
}

using namespace std;

template <class T, class... Args>
void Supply::addPile(int quantity, Args... args) {
    CardPile pile(std::unique_ptr<Card>(new T(args...)));
    for (int i = 0; i < quantity; ++i)
        pile.addCard(std::unique_ptr<Card>(new T(args...)));
    const std::string name = pile.getName();
    piles.emplace(name, std::move(pile));
}

std::vector<Supply::KingdomCardInfo> Supply::getKingdomCatalog() {
    std::vector<KingdomCardInfo> catalog;
    const std::vector<KingdomEntry>& entries = kingdomEntries();
    for (std::size_t i = 0; i < entries.size(); ++i) {
        std::unique_ptr<Card> model = entries[i].create();
        KingdomCardInfo info;
        info.name = model->getName();
        info.cost = model->getCost();
        info.description = entries[i].description;
        catalog.push_back(info);
    }
    return catalog;
}


void Supply::addKingdomPile(const std::string& name) {
    const std::vector<KingdomEntry>& entries = kingdomEntries();
    for (std::size_t i = 0; i < entries.size(); ++i) {
        std::unique_ptr<Card> model = entries[i].create();
        if (toLower(model->getName()) != toLower(name)) continue;

        const std::string pileName = model->getName();
        if (piles.count(pileName)) return; // already in the game (duplicate in the list)
        CardPile pile(std::move(model));
        for (int n = 0; n < entries[i].quantity; ++n)
            pile.addCard(entries[i].create());
        piles.emplace(pileName, std::move(pile));
        return;
    }
    throw std::invalid_argument("Kingdom card unknown : " + name);
}

std::unique_ptr<Card> Supply::takeCard(const std::string& name) {
    CardPile* pile = getPile(name);
    return pile ? pile->takeCard() : nullptr;
}

void Supply::initializeSupply(int numPlayers, const std::vector<std::string>& kingdomNames){ //Setsup the Game depending on the number of players
    const int victory = (numPlayers == 2) ? 8 : 12;
    // Treasure cards
    addPile<TreasureCard>(60, std::string("Copper"), 0, 1);
    addPile<TreasureCard>(40, std::string("Silver"), 3, 2);
    addPile<TreasureCard>(30, std::string("Gold"),   6, 3);

    // Victory cards
    addPile<VictoryCard>(victory, std::string("Estate"),   2,  1, false);
    addPile<VictoryCard>(victory, std::string("Duchy"),    5,  3, false);
    addPile<VictoryCard>(victory, std::string("Province"), 8,  6, false);
    addPile<VictoryCard>(30, std::string("Curse"),    0, -1, false);

    // Kingdom cards (chosen at the beginning of the game)
    for (std::size_t i = 0; i < kingdomNames.size(); ++i)
        addKingdomPile(kingdomNames[i]);
}

void Supply::makeFastMode(bool fastMode){ //Makes the game much faster (no matter which group of cards are in play)
    if(fastMode){ 
        for (auto& i : piles){ //Runs through all the piles
            i.second.reduceQuantity(1); //Sets the quantity of cards in every pile to 1
        }
    }
};

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

CardPile* Supply::getPile(const std::string& name){
    const std::string wanted = toLower(name);
    for (auto& p : piles) { //Searches through all of the pile (the map containing names and their associated CardPile)
        if (toLower(p.first) == wanted){ //If name matches
            return &p.second; //Returns the pointer to the CardPile
        }
    }
    return nullptr; //return nullptr if the name doesn't match
}

const std::map<std::string, CardPile>& Supply::getPiles() const{    return piles;   } //Returns the map of piles