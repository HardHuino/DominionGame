#ifndef CARDPILE_HPP
#define CARDPILE_HPP
//#include "Card.hpp"
using namespace std;
class CardPile{
    private:
    int quantity;
    Card* card;
    public:
    int getQuantity();
    bool isEmpty();
    Card* removeCard(); //Could be just a Card instead of Card* possibly
};
#endif