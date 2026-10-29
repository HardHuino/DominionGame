#include "Cellar.hpp"
#include "Player.hpp"

Cellar::Cellar() : ActionCard("Cellar", 2) {}

// +1 Actions. Discard any number of cards. +1 Card per card discarded
void Cellar::effect(Player& player, Game&) {
    player.addActions(1);

    int discarded = 0;
    while (true) {
        int index = chooseFromHand(player, "Carte a defausser", Choice::May);
        if (index < 0) break; // the player is done (or the hand is empty)
        player.discardFromHand(index);
        ++discarded;
    }
    player.draw(discarded);
}
