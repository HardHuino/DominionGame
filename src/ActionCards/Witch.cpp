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
            Display::showMessage("La pile Curse est vide.");
            break;
        }
        Display::showMessage(target->getName() + " recoit " + Display::cardLabel(*curse));
        target->gain(std::move(curse));
    }
}
