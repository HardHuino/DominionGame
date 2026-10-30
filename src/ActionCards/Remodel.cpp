#include "Remodel.hpp"
#include "Player.hpp"
#include "Game.hpp"
#include "Display.hpp"

Remodel::Remodel() : ActionCard("Remodel", 4) {}

//Trash a card from your hand. Gain a card costing up to 2 more than it.
void Remodel::effect(Player& player, Game& game) {

    int index = chooseFromHand(player, "Which card do you want to trash (you will be able to choose a card worth 2 more than it from the supply) : ", Choice::Must);
    if (index<0) { // empty hand
        Display::showMessage("Votre main est vide : rien a ecarter.");
        return;
    }

    std::unique_ptr<Card> trashedCard = player.removeFromHand(index);
    int cost= trashedCard->getCost()+2;
    Display::showMessage(player.getName() + " ecarte " + Display::cardLabel(*trashedCard));
    game.trashCard(std::move(trashedCard));

    CardPile* chosenPile = chooseFromSupply(game, "Recevez une carte coutant jusqu'a " + std::to_string(cost) + " :", [cost](const Card& c) { return c.getCost() <= cost; });
    if (!chosenPile) return; // nothing in the supply is cheap enough

    Display::showMessage(player.getName()+" recoit " +Display::cardLabel(chosenPile->getModel()));
    player.gain(chosenPile->takeCard());
}