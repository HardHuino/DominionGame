#ifndef CARDPILE_HPP
#define CARDPILE_HPP

#include "Card.hpp"
#include <memory>
#include <string>
#include <vector>

using namespace std;

class CardPile{
    private:
    std::unique_ptr<Card> model; // model=type of card in the pile
    std::vector<std::unique_ptr<Card> > cards; // Vector of unique pointers to Card objects representing the cards in the pile

    public:
    //Constructor
    explicit CardPile(std::unique_ptr<Card> model);

    void addCard(std::unique_ptr<Card> card); //Adds a card to the pile
    std::unique_ptr<Card> takeCard(); //Takes a card from the pile

    // Getters
    const Card& getModel() const;
    std::string getName() const;
    int getQuantity() const;
    bool isEmpty() const;

    // Setters
    void setQuantity(int quantity);
};

#endif