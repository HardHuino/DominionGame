#ifndef REMODEL_HPP
#define REMODEL_HPP

#include "ActionCard.hpp"

class Remodel : public ActionCard {
public:
    Remodel();
    void effect(Player& player, Game& game) override;
};

#endif // REMODEL_HPP