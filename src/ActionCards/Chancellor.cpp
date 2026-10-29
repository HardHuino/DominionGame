#include "Chancellor.hpp"

#include "Display.hpp"
#include "Player.hpp"

Chancellor::Chancellor() : ActionCard("Chancellor", 3) {}

// +2 Coins. You may immediately put your deck into your discard pile
void Chancellor::effect(Player& player, Game&) {
    player.addCoins(2);
    if (Display::askChoice("Mettre toute votre pioche dans la defausse ? (1 = oui, 0 = non) : ", 0, 1) == 1) {
        player.discardDeck();
        Display::showMessage(player.getName() + " met sa pioche dans sa defausse.");
    }
}