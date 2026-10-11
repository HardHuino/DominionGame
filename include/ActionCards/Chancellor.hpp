#ifndef CHANCELLOR_HPP
#define CHANCELLOR_HPP

#include "ActionCard.hpp"

class Chancellor : public ActionCard {
public:
    Chancellor();
    void effect(Player& player, Game& game) override;
};

#endif // CHANCELLOR_HPP