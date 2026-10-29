#include "VictoryCard.hpp"

VictoryCard::VictoryCard(const std::string& name, int cost, int victoryPoints)
    : Card(name, cost), victoryPoints(victoryPoints) {}

bool VictoryCard::isVictory() const {
    return true;
}

int VictoryCard::getVictoryPoints() const {
    return victoryPoints;
}