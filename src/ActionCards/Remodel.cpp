#include "Remodel.hpp"
#include "Player.hpp"
#include "Game.hpp"
#include "Display.hpp"

Remodel::Remodel() : ActionCard("Remodel", 4) {}

//Trash a card from your hand. Gain a card costing up to 2 more than it.
void Remodel::effect(Player& player, Game& game) {
    CardPile* chosenPile;
    while(true){
        int index = chooseFromHand(player, "Which card do you want to trash (you will be able to choose a card worth 2 more than it from the supply) : ", Choice::Must);
        std::unique_ptr<Card> trashedCard = player.removeFromHand(index);
        int cost= trashedCard->getCost()+2;
        chosenPile = chooseFromSupply(game, "Choose your new card worth up to "+std::to_string(cost)+" : ", [cost](const Card& c){ return c.getCost() <= cost;});
        if(chosenPile){break;}
        Display::showMessage("The chosen card is invalid choose another");
    }
    player.gain(chosenPile->takeCard());
    Display::showMessage(player.getName()+" recoit " +Display::cardLabel(chosenPile->getModel()));
}