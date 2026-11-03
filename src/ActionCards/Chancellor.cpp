#include "Chancellor.hpp"

#include "Display.hpp"
#include "Player.hpp"

Chancellor::Chancellor() : ActionCard("Chancellor", 3) {}

// +2 Coins. You may immediately put your deck into your discard pile
void Chancellor::effect(Player& player, Game&) {
    player.addCoins(2);
    if (Display::askChoice("Put your whole deck into your discard pile? (1 = yes, 0 = no) : ", 0, 1) == 1) {
        player.discardDeck();
        Display::showMessage(player.getName() + " puts their whole deck into their discard pile.");
    }
}