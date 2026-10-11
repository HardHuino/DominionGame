#ifndef MILITIA_HPP
#define MILITIA_HPP

#include "ActionCard.hpp"

class Militia : public ActionCard {
public:
    Militia();
    void effect(Player& player, Game& game) override;
};

#endif // MILITIA_HPP