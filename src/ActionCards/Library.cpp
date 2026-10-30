#include "Library.hpp"
#include "Player.hpp"
#include "Card.hpp"
#include "ActionCard.hpp"
#include "Display.hpp"


Library::Library() : ActionCard("Library", 5) {}

// Draw until hand of 7, if action card drawn can discard immediatly and keep drawing
void Library::effect(Player& player, Game&) {
    while(player.getHand().size()<7){
        std::unique_ptr<Card> drawnCard = player.drawCard();
        if(drawnCard->isAction()){
            int discardCard = Display::askChoice("You have drawn an action card, do you want to keep it or discard it? (keep: 0, discard: 1) : ", 0, 1);
            if(discardCard == 1){//Trashes drawn card
                player.discardCard(std::move(drawnCard));
                Display::showMessage("Action Card discared");
            }
            else{//adds it back to the player's hand
                player.addToHand(std::move(drawnCard));
                Display::showMessage("Action Card kept");
            }
        }
        else{
            player.addToHand(std::move(drawnCard));
        }
    }
}