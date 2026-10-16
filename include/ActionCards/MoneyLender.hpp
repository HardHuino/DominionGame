#ifndef MONEY_LENDER_HPP
#define MONEY_LENDER_HPP

#include "ActionCard.hpp"

class MoneyLender : public ActionCard {
public:
    MoneyLender();
    void effect(Player& player, Game& game) override;
};

#endif // MONEY_LENDER_HPP