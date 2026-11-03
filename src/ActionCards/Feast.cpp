#include "Feast.hpp"
#include "Player.hpp"
#include "Game.hpp"
#include "Display.hpp"

Feast::Feast() : ActionCard("Feast", 4) {}

// Gain a card costing up to 5 Coins
void Feast::effect(Player& player, Game& game) {
    std::unique_ptr<Card> self = player.removeFromPlayed(this);
    game.trashCard(std::move(self));
    CardPile* pile = chooseFromSupply(game, "Receive a card costing up to 5 Coins : ", [](const Card& c) { return c.getCost() <= 5; });
    if (!pile) return;
    player.gain(pile->takeCard());
    Display::showMessage(player.getName() + " reveals " + Display::cardLabel(pile->getModel()));
    Display::showMessage("Feast has been trashed.");
}