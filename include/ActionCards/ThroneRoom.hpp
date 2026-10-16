#ifndef THRONE_ROOM_HPP
#define THRONE_ROOM_HPP

#include "ActionCard.hpp"

class ThroneRoom : public ActionCard {
public:
    ThroneRoom();
    void effect(Player& player, Game& game) override;
};

#endif // THRONE_ROOM_HPP