#include "Spy.hpp"

#include "Display.hpp"
#include "Game.hpp"
#include "Player.hpp"

Spy::Spy() : ActionCard("Spy", 4) {}

// +1 Card, +1 Action. Each player (including you) reveals the top card of his deck
// and either discards it or puts it back, your choice (Attack)
void Spy::effect(Player& player, Game& game) {
    player.draw(1);
    player.addActions(1);

    // The attacker is always concerned, the others only if they are not protected (Moat)
    std::vector<Player*> concerned;
    concerned.push_back(&player);
    for (Player* target : game.getAttackTargets(player)) concerned.push_back(target);

    for (Player* victim : concerned) {
        std::unique_ptr<Card> top = victim->drawCard();
        if (!top) {
            Display::showMessage(victim->getName() + " has no more cards to reveal.");
            continue;
        }
        Display::showMessage(victim->getName() + " reveals " + Display::cardLabel(*top));
        if (Display::askChoice(player.getName() + " : 1 = discard this card, 0 = put it back on the deck : ", 0, 1) == 1)
            victim->discardCard(std::move(top));
        else
            victim->putOnDeck(std::move(top));
    }
}
