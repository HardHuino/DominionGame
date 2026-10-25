#include "Card.hpp"

Card::Card(const std::string& name, int cost)
    : name(name), cost(cost) {}



// Getters

std::string Card::getName() const { return name; }

int Card::getCost() const { return cost; }