#include "MoneyLender.hpp"

#include "Display.hpp"
#include "Game.hpp"
#include "Player.hpp"

MoneyLender::MoneyLender() : ActionCard("Moneylender", 4) {}

// You may trash a Copper from your hand for +3 Coins
void MoneyLender::effect(Player& player, Game& game) {

    int index = chooseFromHand(player, "Carte a defausser", Choice::May, [](const Card& c) { return c.isTreasure() && c.getCost() == 0; });

    if (index >= 0) {
        std::unique_ptr<Card> copper = player.removeFromHand(static_cast<int>(index));
        Display::showMessage(player.getName() + " ecarte " + Display::cardLabel(*copper) + " et gagne 3 pieces");
        game.trashCard(std::move(copper));
        player.addCoins(3);
    }
    Display::showMessage(player.getName() + " n'a pas de Copper en main : rien ne se passe.");

}
