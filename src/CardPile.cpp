#include "CardPile.hpp"

CardPile::CardPile(std::unique_ptr<Card> model) : model(std::move(model)) {}


void CardPile::addCard(std::unique_ptr<Card> card) {
    cards.push_back(std::move(card));
}

std::unique_ptr<Card> CardPile::takeCard() {
    if (cards.empty()) return nullptr;
    std::unique_ptr<Card> card = std::move(cards.back());   // the card leaves the pile, so we use std::move to transfer ownership of the unique_ptr
    cards.pop_back();
    return card;
} // removed the exeption throw, now returns nullptr if the pile is empty

// Getters
const Card& CardPile::getModel() const { return *model; }
std::string CardPile::getName() const { return model->getName(); }
int CardPile::getQuantity() const { return static_cast<int>(cards.size()); }
bool CardPile::isEmpty() const { return cards.empty(); }

// Setters
void CardPile::reduceQuantity(int quantity) {
    if (quantity < 0) quantity = 0;
    if (static_cast<std::size_t>(quantity) >= cards.size()) return; // nothing to remove
    cards.erase(cards.begin() + quantity, cards.end());              // remove card that are above limit
}