#ifndef TREASURE_CARD_HPP
#define TREASURE_CARD_HPP

#include "Card.hpp"

#include <string>

class TreasureCard : public Card {
private:
    int value;
public:
    TreasureCard(const std::string& name, int cost, int value);

    bool isTreasure() const override;

    int getValue() const;
};

#endif // TREASURE_CARD_HPP