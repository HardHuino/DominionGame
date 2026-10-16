#ifndef ADVENTURER_HPP
#define ADVENTURER_HPP

#include "ActionCard.hpp"

class Adventurer : public ActionCard {
public:
    Adventurer();
    void effect(Player& player, Game& game) override;
};

#endif // ADVENTURER_HPP