#include "Market.hpp"
#include "Player.hpp"

Market::Market() : ActionCard("Market", 5) {}

// +1 Card, +1 Action, +1 Buy, +1 Coins
void Market::effect(Player& player, Game&) {
    player.draw(1);
    player.addActions(1);
    player.addPurchases(1);
    player.addCoins(1);
}