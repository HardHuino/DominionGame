#include "CardPile.hpp"
CardPile::CardPile(Card* card, int quantity): card(card), quantity(quantity) {}

CardPile::~CardPile() {
    delete card; 
}

Card* CardPile::getCard() const {return this->card;}

int CardPile::getQuantity() const {return this->quantity;}

bool CardPile::isEmpty(){
    if(quantity<=0){return true;}
    else{return false;}
}

Card* CardPile::removeCard(){
    quantity=quantity-1;
    return this->card;
} //Could be just a Card instead of Card* possibly