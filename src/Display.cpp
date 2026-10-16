#include "Display.hpp"

#include "Card.hpp"
#include "Player.hpp"
#include "Supply.hpp"
#include "CardPile.hpp"
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

void Display::showHand(const Player& player) {
    std::cout << "Main de " << player.getName() << " :\n";
    const std::vector<Card*>& hand = player.getHand();
    for (std::size_t i = 0; i < hand.size(); ++i)
        std::cout << "  [" << i + 1 << "] " << cardLabel(*hand[i]) << "\n";
}

void Display::showSupply(const Supply& supply, int coins) {
    std::cout << "\nReserve (vous avez " << coins << " pieces) :\n";
    const std::map<std::string, CardPile>& piles = supply.getPiles();
    for (const auto& pair : piles) {
        const Card& c = *pair.second.getCard();
        bool buyable = pair.second.getQuantity() > 0 && c.getCost() <= coins;
        std::cout << (buyable ? "" : GREY)
                  << "  [" << pair.first << "] " << cardLabel(c)
                  << " x" << pair.second.getQuantity() << RESET << "\n";
    }
}