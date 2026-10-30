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

static std::string toLower(std::string s) { // Converts a string to lowercase
    for (std::size_t i = 0; i < s.size(); ++i)
        s[i] = static_cast<char>(std::tolower(static_cast<unsigned char>(s[i])));
    return s;
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
        { "Devoilez des cartes jusqu'a 2 Tresors : prenez-les en main, defaussez le reste.", 10, &makeCard<Adventurer> },
        { "Recevez un Silver sur votre pioche. Les adversaires remettent une carte Victoire sur leur pioche. (Attaque)", 10, &makeCard<Bureaucrat> },
        { "+1 Action. Defaussez N cartes, piochez N cartes.", 10, &makeCard<Cellar> },
        { "+2 Pieces. Vous pouvez mettre votre pioche dans la defausse.", 10, &makeCard<Chancellor> },
        { "Ecartez jusqu'a 4 cartes de votre main.", 10, &makeCard<Chapel> },
        { "+4 Cartes, +1 Achat. Chaque adversaire pioche 1 carte.", 10, &makeCard<CouncilRoom> },
        { "Ecartez cette carte. Recevez une carte coutant jusqu'a 5.", 10, &makeCard<Feast> },
        { "+2 Actions, +1 Achat, +2 Pieces.", 10, &makeCard<Festival> },
        { "1 point de victoire par groupe de 10 cartes dans votre deck.", 12, &makeGarden },
        { "+2 Cartes, +1 Action.", 10, &makeCard<Laboratory> },
        { "Piochez jusqu'a avoir 7 cartes en main (vous pouvez mettre de cote les Actions piochees).", 10, &makeCard<Library> },
        { "+1 Carte, +1 Action, +1 Achat, +1 Piece.", 10, &makeCard<Market> },
        { "+2 Pieces. Les adversaires se defaussent jusqu'a 3 cartes en main. (Attaque)", 10, &makeCard<Militia> },
        { "Ecartez un Tresor de votre main : recevez en main un Tresor coutant jusqu'a 3 de plus.", 10, &makeCard<Mine> },
        { "+2 Cartes. Vous protege des attaques (reaction).", 10, &makeCard<Moat> },
        { "Ecartez un Copper de votre main : +3 Pieces.", 10, &makeCard<MoneyLender> },
        { "Ecartez une carte de votre main : recevez une carte coutant jusqu'a 2 de plus.", 10, &makeCard<Remodel> },
        { "+3 Cartes.", 10, &makeCard<Smithy> },
        { "+1 Carte, +1 Action. Chaque joueur devoile sa premiere carte, vous decidez de la defausser ou non. (Attaque)", 10, &makeCard<Spy> },
        { "Les adversaires devoilent 2 cartes et ecartent un Tresor de votre choix, que vous pouvez recuperer. (Attaque)", 10, &makeCard<Thief> },
        { "Jouez une carte Action de votre main deux fois.", 10, &makeCard<ThroneRoom> },
        { "+1 Carte, +2 Actions.", 10, &makeCard<Village> },
        { "+2 Cartes. Chaque adversaire recoit une Curse. (Attaque)", 10, &makeCard<Witch> },
        { "+1 Achat, +2 Pieces.", 10, &makeCard<Woodcutter> },
        { "Recevez une carte coutant jusqu'a 4.", 10, &makeCard<Workshop> }
    };
    return entries;
}

// Trouve l'entrée dont la carte s'appelle `name` (insensible à la casse), sinon nullptr
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
    throw std::invalid_argument("Carte royaume inconnue : " + name);
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