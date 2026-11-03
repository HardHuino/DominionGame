#include "Bureaucrat.hpp"
#include "Display.hpp"
#include "Game.hpp"
#include "Player.hpp"

Bureaucrat::Bureaucrat() : ActionCard("Bureaucrat", 4) {}

// Card description : Gain a silver onto your deck. Each other player reveals a Victory card from their hand and puts it onto their deck (or reveals a hand with no Victory card)
void Bureaucrat::effect(Player& player, Game& game) {
    std::unique_ptr<Card> silver = game.getSupply().takeCard("Silver");
    if (silver) {
        Display::showMessage(player.getName() + " places " + Display::cardLabel(*silver) + " on their deck");
        player.putOnDeck(std::move(silver));
    } else {
        Display::showMessage("The Silver pile is empty.");
    }

    // Attack : Moat is handled by getAttackTargets
    for (Player* target : game.getAttackTargets(player)) {
        int index = chooseFromHand(*target, target->getName() + " : reveal a Victory card (it will go on your deck)", Choice::Must, [](const Card& c) { return c.isVictory(); });

        if (index < 0) { // no Victory card in hand : the whole hand is revealed
            std::string hand;
            for (const std::unique_ptr<Card>& c : target->getHand())
                hand += " " + Display::cardLabel(*c);
            Display::showMessage(target->getName() + " has no Victory card, their hand :" + (hand.empty() ? " (empty)" : hand));
            continue;
        }

        std::unique_ptr<Card> card = target->removeFromHand(index);
        Display::showMessage(target->getName() + " reveals " + Display::cardLabel(*card) + " and puts it on their deck");
        target->putOnDeck(std::move(card));
    }
}