#include "Mine.hpp"

#include "CardPile.hpp"
#include "Display.hpp"
#include "Game.hpp"
#include "Player.hpp"

Mine::Mine() : ActionCard("Mine", 5) {}

// You may trash a Treasure from your hand. Gain a Treasure to your hand costing up to 3 Coins more than it.
void Mine::effect(Player& player, Game& game) {
    int index = chooseFromHand(player, "Treasure to trash", Choice::May,
                               [](const Card& c) { return c.isTreasure(); });
    if (index < 0) return; // no Treasure in hand : nothing happens

    std::unique_ptr<Card> trashed = player.removeFromHand(index);
    const int maxCost = trashed->getCost() + 3;
    Display::showMessage(player.getName() + " trashes " + Display::cardLabel(*trashed));
    game.trashCard(std::move(trashed));

    CardPile* pile = chooseFromSupply(game, "Receive a Treasure card costing up to " + std::to_string(maxCost) + " (in your hand) :",
                                      [maxCost](const Card& c) { return c.isTreasure() && c.getCost() <= maxCost; });
    if (!pile) return;
    Display::showMessage(player.getName() + " receives " + Display::cardLabel(pile->getModel()) + " in hand");
    player.addToHand(pile->takeCard());
}
