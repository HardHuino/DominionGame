#include "Mine.hpp"

#include "CardPile.hpp"
#include "Display.hpp"
#include "Game.hpp"
#include "Player.hpp"

Mine::Mine() : ActionCard("Mine", 5) {}

// You may trash a Treasure from your hand. Gain a Treasure to your hand costing up to 3 Coins more than it.
void Mine::effect(Player& player, Game& game) {
    int index = chooseFromHand(player, "Carte Tresor a ecarter", Choice::Must,
                               [](const Card& c) { return c.isTreasure(); });
    if (index < 0) return; // no Treasure in hand : nothing happens

    std::unique_ptr<Card> trashed = player.removeFromHand(index);
    const int maxCost = trashed->getCost() + 3;
    Display::showMessage(player.getName() + " ecarte " + Display::cardLabel(*trashed));
    game.trashCard(std::move(trashed));

    CardPile* pile = chooseFromSupply(game, "Recevez une carte Tresor coutant jusqu'a " + std::to_string(maxCost) + " (dans votre main) :",
                                      [maxCost](const Card& c) { return c.isTreasure() && c.getCost() <= maxCost; });
    if (!pile) return;
    Display::showMessage(player.getName() + " recoit " + Display::cardLabel(pile->getModel()) + " en main");
    player.addToHand(pile->takeCard());
}
