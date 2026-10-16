#ifndef MINE_HPP
#define MINE_HPP

#include "ActionCard.hpp"

class Mine : public ActionCard {
public:
    Mine();
    void effect(Player& player, Game& game) override;
};

#endif // MINE_HPP