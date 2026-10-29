#include "Bureaucrat.hpp"
#include "Display.hpp"
#include "Game.hpp"
#include "Player.hpp"

Bureaucrat::Bureaucrat() : ActionCard("Bureaucrat", 4) {}

// Card description : Gain a silver onto your deck. Each other player reveals a Victory card from their hand and puts it onto their deck (or reveals a hand with no Victory card) 
void Bureaucrat::effect(Player& player, Game& game) {
    std::unique_ptr<Card> silver = game.getSupply().takeCard("Silver");
    if (silver) { // MAYBE MOVE THIS TO EITHER A HELP FUNCTION IN ACTIONCARD OR 
        Display::showMessage(player.getName() + " place " + Display::cardLabel(*silver) + " sur sa pioche");
        player.putOnDeck(std::move(silver));
    } else {
        Display::showMessage("La pile Silver est vide.");
    }

    
}