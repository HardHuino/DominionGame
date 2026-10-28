#ifndef ACTION_CARD_HPP
#define ACTION_CARD_HPP

#include "Card.hpp"

#include <string>
#include <vector>

class Player;
class Game;
class CardPile;

class ActionCard : public Card {
public:
    ActionCard(const std::string& name, int cost);

    bool isAction() const override;

    virtual void effect(Player& player, Game& game) = 0;
};

#endif // ACTION_CARD_HPP