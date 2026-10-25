#include "ActionCard.hpp"

ActionCard::ActionCard(const std::string& name, int cost)
    : Card(name, cost) {}

bool ActionCard::isAction() const {
    return true;
}