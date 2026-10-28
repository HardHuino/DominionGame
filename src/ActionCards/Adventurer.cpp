#include "Adventurer.hpp"

#include "Display.hpp"
#include "Player.hpp"

Adventurer::Adventurer() : ActionCard("Adventurer", 6) {}

void Adventurer::effect(Player& player, Game&) {
    CardList revealed; // non-treasure card kept aside that will be discarded at the end

    int treasuresFound = 0;

    while (treasuresFound<2) {
        std::unique_ptr<Card> card = player.drawCard();
        if (!card) break; // deck and discard empty : stop (shouldn't happen)
        Display::showMessage(player.getName() + " devoile " + Display::cardLabel(*card));
        if (card->isTreasure()) {
            player.addToHand(std::move(card));
            treasuresFound++;
        } else {
            revealed.push_back(std::move(card));
        }
    }

    for (std::unique_ptr<Card>& c : revealed) player.discardCard(std::move(c));
}