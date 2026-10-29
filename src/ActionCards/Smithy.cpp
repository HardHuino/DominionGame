#include "Smithy.hpp"
#include "Player.hpp"

Smithy::Smithy() : ActionCard("Smithy", 4) {}

// +3 Cards
void Smithy::effect(Player& player, Game&) {
    player.draw(3);
}