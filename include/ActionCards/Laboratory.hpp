#ifndef LABORATORY_HPP
#define LABORATORY_HPP

#include "ActionCard.hpp"

class Laboratory : public ActionCard {
public:
    Laboratory();
    void effect(Player& player, Game& game) override;
};

#endif // LABORATORY_HPP