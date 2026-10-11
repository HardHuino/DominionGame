#ifndef SPY_HPP
#define SPY_HPP

#include "ActionCard.hpp"

class Spy : public ActionCard {
public:
    Spy();
    void effect(Player& player, Game& game) override;
};

#endif // SPY_HPP