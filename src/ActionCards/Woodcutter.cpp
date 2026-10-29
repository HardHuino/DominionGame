#include "Woodcutter.hpp"
#include "Player.hpp"

Woodcutter::Woodcutter() : ActionCard("Woodcutter", 3) {}

//+1 Buy, +2 Coins
void Woodcutter::effect(Player& player, Game&) {
    player.addPurchases(1);
    player.addCoins(2);
}