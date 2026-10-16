#ifndef CARDPILE_HPP
#define CARDPILE_HPP
#include "Card.hpp"
using namespace std;
class CardPile{
    private:
    Card* card;
    int quantity;

    public:
    //Constructor
    CardPile(Card* card, int quantity);
    // Destructeur
    virtual ~CardPile();

    // Getters
    Card* getCard() const;
    int getQuantity() const;

    bool isEmpty();
    Card* removeCard(); //Could be just a Card instead of Card* possibly
};
#endif