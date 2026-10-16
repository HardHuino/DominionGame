#ifndef WOODCUTTER_HPP
#define WOODCUTTER_HPP

#include "ActionCard.hpp"

class Woodcutter : public ActionCard {
public:
    Woodcutter();
    void effect(Player& player, Game& game) override;
};

#endif // WOODCUTTER_HPP