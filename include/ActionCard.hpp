#ifndef ACTION_CARD_HPP
#define ACTION_CARD_HPP

#include "Card.hpp"

#include <string>

class Player;
class Game;

class ActionCard : public Card {
public:
    ActionCard(const std::string& name, int cost);
    virtual void effect(Player& player, Game& game) = 0;
};

#endif // ACTION_CARD_HPP