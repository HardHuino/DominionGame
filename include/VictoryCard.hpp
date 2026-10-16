#ifndef VICTORY_CARD_HPP
#define VICTORY_CARD_HPP

#include "Card.hpp"

#include <string>

class VictoryCard : public Card {
private:
    int victoryPoints;
public:
    VictoryCard(const std::string& name, int cost, int victoryPoints);

    int getVictoryPoints() const;
};

#endif // VICTORY_CARD_HPP