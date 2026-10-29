#include "CouncilRoom.hpp"

#include "Game.hpp"
#include "Player.hpp"

CouncilRoom::CouncilRoom() : ActionCard("Council Room", 5) {}

// +4 Cards, +1 Buy. Each other player draws a card (not an Attack : Moat does not apply)
void CouncilRoom::effect(Player& player, Game& game) {
    player.draw(4);
    player.addPurchases(1);
    for (Player& other : game.getPlayers())
        if (&other != &player) other.draw(1);
}