#include "ThroneRoom.hpp"

#include "Display.hpp"
#include "Player.hpp"

ThroneRoom::ThroneRoom() : ActionCard("Throne Room", 4) {}

// You may play an Action card from your hand twice
void ThroneRoom::effect(Player& player, Game& game) {
    int index = chooseFromHand(player, "Carte Action a jouer deux fois", Choice::May, [](const Card& c) { return c.isAction(); });
    if (index < 0) return; // no Action in hand/choose not to use the power of the card : nothing happens

    std::unique_ptr<Card> chosen = player.removeFromHand(index);
    ActionCard* action = static_cast<ActionCard*>(chosen.get()); // safe : the filter only accepts Action cards
    player.addToPlayed(std::move(chosen)); // the card stays in play (the pointer remains valid)

    Display::showMessage(player.getName() + " joue " + Display::cardLabel(*action) + " (1/2)");
    action->effect(player, game);
    Display::showMessage(player.getName() + " joue " + Display::cardLabel(*action) + " (2/2)");
    action->effect(player, game);
}