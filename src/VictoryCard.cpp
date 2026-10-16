#include "VictoryCard.hpp"

VictoryCard::VictoryCard(const std::string& name, int cost, int victoryPoints)
    : Card(name, cost), victoryPoints(victoryPoints) {}

int VictoryCard::getVictoryPoints() const {
    return victoryPoints;
}