#ifndef THIEF_HPP
#define THIEF_HPP

#include "ActionCard.hpp"

class Thief : public ActionCard {
public:
    Thief();
    void effect(Player& player, Game& game) override;
};

#endif // THIEF_HPP