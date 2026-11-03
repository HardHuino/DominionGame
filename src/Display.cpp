#include "Display.hpp"

#include "Card.hpp"
#include "Player.hpp"
#include "Supply.hpp"
#include "CardPile.hpp"
#include "TreasureCard.hpp"
#include "VictoryCard.hpp"
#include <iostream>
#include <limits>
#include <cstdlib>

// ANSI color codes
static const char* RESET  = "\033[0m";
static const char* YELLOW = "\033[33m";
static const char* GREEN  = "\033[32m";
static const char* BLUE   = "\033[34m";
static const char* GREY   = "\033[90m";

std::string Display::cardLabel(const Card& card) {
    const char* color = RESET;
    if (card.isTreasure())     color = YELLOW;
    else if (card.isVictory()) color = GREEN;
    else if (card.isAction())  color = BLUE;
    return std::string(color) + card.getName() + RESET
         + " (" + std::to_string(card.getCost()) + ")";
}

void Display::showTurnHeader(const Player& player) {
    std::cout << "\n========== Turn of " << player.getName() << " ==========\n";
}

// Short effect text displayed next to a card in the hand
static std::string cardEffect(const Card& card) {
    if (card.isTreasure())
        return "+" + std::to_string(static_cast<const TreasureCard&>(card).getValue()) + " Coin(s)";
    if (card.isVictory()) {
        const VictoryCard& v = static_cast<const VictoryCard&>(card);
        if (v.getIsGarden()) return "1 Victory Point per 10 cards in your deck";
        return std::to_string(v.getVictoryPoints()) + " VP";
    }
    static const std::vector<Supply::KingdomCardInfo> catalog = Supply::getKingdomCatalog();
    for (std::size_t i = 0; i < catalog.size(); ++i)
        if (catalog[i].name == card.getName()) return catalog[i].description;
    return "";
}

void Display::showHand(const Player& player) {
    std::cout << "Hand of " << player.getName() << " :\n";
    const CardList& hand = player.getHand();
    for (std::size_t i = 0; i < hand.size(); ++i) {
        std::cout << "  [" << i + 1 << "] " << cardLabel(*hand[i]);
        const std::string effect = cardEffect(*hand[i]);
        if (!effect.empty()) std::cout << GREY << "  - " << effect << RESET;
        std::cout << "\n";
    }
}

void Display::showStatus(const Player& player) {
    std::cout << "\nActions: " << player.getActions()
              << " | Purchases: " << player.getPurchases()
              << " | Coins: " << player.getCoins()
              << " | Deck: " << player.getDeckSize()
              << " | Discard: " << player.getDiscardSize() << "\n";
}

void Display::showSupply(const Supply& supply, int coins) {
    std::cout << "\nSupply (you have " << coins << " coins) :\n";
    const std::map<std::string, CardPile>& piles = supply.getPiles();
    for (const auto& pair : piles) {
        const Card& c = pair.second.getModel();
        bool buyable = pair.second.getQuantity() > 0 && c.getCost() <= coins;
        const std::string effect = cardEffect(c);
        std::cout << (buyable ? "" : GREY) // dim the text if the card is not buyable
                  << "  [" << pair.first << "] " << cardLabel(c)
                  << " x" << pair.second.getQuantity() << RESET;
        if (!effect.empty()) std::cout << GREY << "  - " << effect << RESET;
        std::cout << "\n";
                  
    }
}

void Display::showMessage(const std::string& text) {
    std::cout << text << "\n";
}

void Display::showWinner(const std::vector<Player>& players) {
    std::cout << "\n========== END OF GAME ==========\n";
    int best = players.empty() ? 0 : players[0].countVictoryPoints();
    for (const Player& p : players) {
        int vp = p.countVictoryPoints();
        std::cout << "  " << p.getName() << " : " << vp << " victory points\n";
        if (vp > best) best = vp;
    }
    std::cout << "Winner(s):";
    for (const Player& p : players)
        if (p.countVictoryPoints() == best) std::cout << " " << p.getName();
    std::cout << "\n";
}

std::string Display::askLine(const std::string& prompt) {
    std::cout << prompt << std::flush;
    std::string line;
    if (!std::getline(std::cin, line)) {               // Ctrl-D ou fin du fichier d'entree
        std::cout << "\n[End of input : stop]\n";
        std::exit(0);
    }
    std::size_t b = line.find_first_not_of(" \t\r");
    if (b == std::string::npos) return "";
    std::size_t e = line.find_last_not_of(" \t\r");
    return line.substr(b, e - b + 1);
}

int Display::askChoice(const std::string& prompt, int min, int max) {
    while (true) {
        std::string line = askLine(prompt);
        char* end = nullptr;
        long v = std::strtol(line.c_str(), &end, 10);
        if (!line.empty() && *end == '\0' && v >= min && v <= max) return static_cast<int>(v);
        std::cout << "Invalid entry : please enter a number between " << min << " and " << max << ".\n";
    }
}