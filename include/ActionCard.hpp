#ifndef ACTION_CARD_HPP
#define ACTION_CARD_HPP

#include "Card.hpp"

#include <functional>
#include <string>
#include <vector>

class Player;
class Game;
class CardPile;

class ActionCard : public Card {
public:
    // Predicate used to restrict a choice (e.g. "treasure cards only")
    typedef std::function<bool(const Card&)> CardFilter;

    ActionCard(const std::string& name, int cost);

    bool isAction() const override;

    virtual void effect(Player& player, Game& game) = 0;

    // Reaction: true if revealing this card from the hand cancels an attack (for Moat)
    virtual bool blocksAttack() const;

protected:

    // Mirrors the wording of the cards, using an enum instead of, for example, a bool in the functions below allow for more lisibility :
    //   Must : "Trash a Treasure card from your hand"      -> the player has to choose one if he can
    //   May  : "You may trash a Treasure from your hand"   -> the player can decline (answer 0)
    enum class Choice { Must, May };

    // asks the player to pick a card from his hand
    // returns the index of the card in the hand, -1 if he passes(May)/no card is allowed
    static int chooseFromHand(Player& player, const std::string& prompt, Choice choice, const CardFilter& filter = CardFilter());
    
    // lists the non-empty supply piles accepted by the filter and asks the player to pick one
    // returns nullptr if no pile is eligible
    static CardPile* chooseFromSupply(Game& game, const std::string& prompt, const CardFilter& filter);

};

#endif // ACTION_CARD_HPP