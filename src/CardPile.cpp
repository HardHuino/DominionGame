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
    if(quantity>0){
        quantity=quantity-1;
        return this->card;
    }
    else{
        //Throw an error? cause it shouldn't be allowed. TO BE IMPLIMENTED !!!
    }
} //Could be just a Card instead of Card* possibly