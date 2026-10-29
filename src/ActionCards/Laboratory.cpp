#include "Laboratory.hpp"
#include "Player.hpp"

Laboratory::Laboratory() : ActionCard("Laboratory", 5) {}

// +2 Cards, +1 Action
void Laboratory::effect(Player& player, Game&) {
    player.draw(2);
    player.addActions(1);
}