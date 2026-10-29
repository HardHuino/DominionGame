#include "Workshop.hpp"
#include "Player.hpp"
#include "Game.hpp"
#include "Display.hpp"

Workshop::Workshop() : ActionCard("Workshop", 3) {}

// Gain a card costing up to 4 Coins
void Workshop::effect(Player& player, Game& game) {
    CardPile* pile;
    while (true) {
        pile = chooseFromSupply(game, "Recevez une carte coutant jusqu'a 4 Coins :", [](const Card& c) { return c.getCost() <= 4; });
        if (pile) break;
        Display::showMessage("The chosen card is invalid, choose another");
    }
    player.gain(pile->takeCard());
    Display::showMessage(player.getName() + " recoit " + Display::cardLabel(pile->getModel()));
}