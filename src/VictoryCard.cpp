#include "VictoryCard.hpp"

VictoryCard::VictoryCard(const std::string& name, int cost, int victoryPoints, bool isGarden)
    : Card(name, cost), victoryPoints(victoryPoints), isGarden(isGarden) {}

bool VictoryCard::isVictory() const {
    return true;
}

int VictoryCard::getVictoryPoints() const {
    return victoryPoints;
}

bool VictoryCard::getIsGarden() const {
    return isGarden;
}