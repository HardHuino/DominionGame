#ifndef SMITHY_HPP
#define SMITHY_HPP

#include "ActionCard.hpp"

class Smithy : public ActionCard {
public:
    Smithy();
    void effect(Player& player, Game& game) override;
};

#endif // SMITHY_HPP