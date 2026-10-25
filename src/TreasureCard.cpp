#include "TreasureCard.hpp"

TreasureCard::TreasureCard(const std::string& name, int cost, int value)
    : Card(name, cost), value(value) {}

bool TreasureCard::isTreasure() const {
    return true;
}

int TreasureCard::getValue() const {
    return value;
}