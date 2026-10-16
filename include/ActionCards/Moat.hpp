#ifndef MOAT_HPP
#define MOAT_HPP

#include "ActionCard.hpp"

class Moat : public ActionCard {
public:
    Moat();
    void effect(Player& player, Game& game) override;
};

#endif // MOAT_HPP