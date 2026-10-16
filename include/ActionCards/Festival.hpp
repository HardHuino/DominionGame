#ifndef FESTIVAL_HPP
#define FESTIVAL_HPP

#include "ActionCard.hpp"

class Festival : public ActionCard {
public:
    Festival();
    void effect(Player& player, Game& game) override;
};

#endif // FESTIVAL_HPP