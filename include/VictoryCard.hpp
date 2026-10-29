#ifndef VICTORY_CARD_HPP
#define VICTORY_CARD_HPP

#include "Card.hpp"

#include <string>

class VictoryCard : public Card {
private:
    int victoryPoints;
    bool isGarden;
public:
    VictoryCard(const std::string& name, int cost, int victoryPoints, bool isGarden);

    bool isVictory() const override;

    int getVictoryPoints() const;

    bool getIsGarden();
};

#endif // VICTORY_CARD_HPP