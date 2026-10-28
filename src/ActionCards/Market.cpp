#include "Market.hpp"
#include "Player.hpp"

void Market::effect(Player& player, Game&) {
    player.draw(1);
    player.addActions(1);
    player.addPurchases(1);
    player.addCoins(1);
}