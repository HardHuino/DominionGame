#include "Feast.hpp"
#include "Player.hpp"
#include "Game.hpp"
#include "Display.hpp"

Feast::Feast() : ActionCard("Feast", 4) {}

// Gain a card costing up to 5 Coins
void Feast::effect(Player& player, Game& game) {
    CardPile* pile;
    while (true) {
        pile = chooseFromSupply(game, "Receive a card costing up to 5 Coins : ", [](const Card& c) { return c.getCost() <= 5; });
        if (pile) break; //<--If the chosen card is valid
        Display::showMessage("The chosen card is invalid, choose another"); 
    }
    player.gain(pile->takeCard());
    Display::showMessage(player.getName() + " recoit " + Display::cardLabel(pile->getModel()));
    std::unique_ptr<Card> self = player.removeFromPlayed(this);
    game.trashCard(std::move(self));
    Display::showMessage("Feast has been trashed.");
}