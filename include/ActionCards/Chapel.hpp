#ifndef CHAPEL_HPP
#define CHAPEL_HPP

#include "ActionCard.hpp"

class Chapel : public ActionCard {
public:
    Chapel();
    void effect(Player& player, Game& game) override;
};

#endif // CHAPEL_HPP