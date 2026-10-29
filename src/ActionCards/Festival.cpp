#include "Festival.hpp"
#include "Player.hpp"

Festival::Festival() : ActionCard("Festival", 5) {}

// +2 Actions, +1 Buy, +2 Coins
void Festival::effect(Player& player, Game&) {
    player.addActions(2);
    player.addPurchases(1);
    player.addCoins(2);
}