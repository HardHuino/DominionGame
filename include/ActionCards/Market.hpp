#ifndef MARKET_HPP
#define MARKET_HPP

#include "ActionCard.hpp"

class Market : public ActionCard {
public:
    Market();
    void effect(Player& player, Game& game) override;
};

#endif // MARKET_HPP