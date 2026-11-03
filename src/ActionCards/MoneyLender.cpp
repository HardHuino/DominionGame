#include "MoneyLender.hpp"

#include "Display.hpp"
#include "Game.hpp"
#include "Player.hpp"

MoneyLender::MoneyLender() : ActionCard("Moneylender", 4) {}

// You may trash a Copper from your hand for +3 Coins
void MoneyLender::effect(Player& player, Game& game) {

    int index = chooseFromHand(player, "Copper to trash", Choice::May, [](const Card& c) { return c.isTreasure() && c.getCost() == 0; });

    if (index >= 0) {
        std::unique_ptr<Card> copper = player.removeFromHand(static_cast<int>(index));
        Display::showMessage(player.getName() + " trashes " + Display::cardLabel(*copper) + " and gains 3 coins");
        game.trashCard(std::move(copper));
        player.addCoins(3);
    } else {
        Display::showMessage(player.getName() + " has no Copper in hand : nothing happens.");
    }
}
