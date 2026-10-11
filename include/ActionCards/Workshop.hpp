#ifndef WORKSHOP_HPP
#define WORKSHOP_HPP

#include "ActionCard.hpp"

class Workshop : public ActionCard {
public:
    Workshop();
    void effect(Player& player, Game& game) override;
};

#endif // WORKSHOP_HPP