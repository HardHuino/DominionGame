#ifndef VILLAGE_HPP
#define VILLAGE_HPP

#include "ActionCard.hpp"

class Village : public ActionCard {
public:
    Village();
    void effect(Player& player, Game& game) override;
};

#endif // VILLAGE_HPP