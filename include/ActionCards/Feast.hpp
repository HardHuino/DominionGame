#ifndef FEST_HPP
#define FEST_HPP

#include "ActionCard.hpp"

class Feast : public ActionCard {
public:
    Feast();
    void effect(Player& player, Game& game) override;
};

#endif // FEST_HPP