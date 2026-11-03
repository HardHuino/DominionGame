#include "Witch.hpp"

#include "Display.hpp"
#include "Game.hpp"
#include "Player.hpp"

Witch::Witch() : ActionCard("Witch", 5) {}

// +2 Cards. Each other player gains a Curse (Attack)
void Witch::effect(Player& player, Game& game) {
    player.draw(2);

    for (Player* target : game.getAttackTargets(player)) {
        std::unique_ptr<Card> curse = game.getSupply().takeCard("Curse");
        if (!curse) {
            Display::showMessage("The Curse pile is empty.");
            break;
        }
        Display::showMessage(target->getName() + " receives " + Display::cardLabel(*curse));
        target->gain(std::move(curse));
    }
}
