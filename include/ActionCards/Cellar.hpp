#ifndef CELLAR_HPP
#define CELLAR_HPP

#include "ActionCard.hpp"

class Cellar : public ActionCard {
public:
    Cellar();
    void effect(Player& player, Game& game) override;
};

#endif // CELLAR_HPP