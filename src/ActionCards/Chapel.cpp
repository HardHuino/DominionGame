#include "Chapel.hpp"

#include "Display.hpp"
#include "Game.hpp"
#include "Player.hpp"

Chapel::Chapel() : ActionCard("Chapel", 2) {}

// Trash up to 4 cards from your hand
void Chapel::effect(Player& player, Game& game) {
    for (int trashedCount = 0; trashedCount < 4; ++trashedCount) {
        int index = chooseFromHand(player, "Carte a ecarter (" + std::to_string(trashedCount) + "/4)", Choice::May);
        if (index < 0) break; // the player is done (or the hand is empty)

        std::unique_ptr<Card> card = player.removeFromHand(index);
        Display::showMessage(player.getName() + " ecarte " + Display::cardLabel(*card));
        game.trashCard(std::move(card));
    }
}