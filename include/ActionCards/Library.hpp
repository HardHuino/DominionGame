#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include "ActionCard.hpp"

class Library : public ActionCard {
public:
    Library();
    void effect(Player& player, Game& game) override;
};

#endif // LIBRARY_HPP