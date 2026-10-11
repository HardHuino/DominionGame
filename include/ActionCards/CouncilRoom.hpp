#ifndef COUNCIL_ROOM_HPP
#define COUNCIL_ROOM_HPP

#include "ActionCard.hpp"

class CouncilRoom : public ActionCard {
public:
    CouncilRoom();
    void effect(Player& player, Game& game) override;
};

#endif // COUNCIL_ROOM_HPP