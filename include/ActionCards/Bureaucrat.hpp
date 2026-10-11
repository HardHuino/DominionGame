#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include "ActionCard.hpp"

class Bureaucrat : public ActionCard {
public:
    Bureaucrat();
    void effect(Player& player, Game& game) override;
};

#endif // BUREAUCRAT_HPP