#ifndef WITCH_HPP
#define WITCH_HPP

#include "ActionCard.hpp"

class Witch : public ActionCard {
public:
    Witch();
    void effect(Player& player, Game& game) override;
};

#endif // WITCH_HPP