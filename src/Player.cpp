#include "Player.hpp"

#include "TreasureCard.hpp"
#include "VictoryCard.hpp"

Player::Player(const std::string& name) : name(name), actions(1), purchases(1), coins(0) {
    // Initialize the player's deck with 7 Copper cards and 3 Estate cards
    for (int i = 0; i < 7; ++i) {
        deck.push_back(new TreasureCard("Copper", 0, 1));
    }
    for (int i = 0; i < 3; ++i) {
        deck.push_back(new VictoryCard("Estate", 2, 1));
    }
    // Shuffle the deck
    //std::shuffle(deck.begin(), deck.end());
    // Draw the initial hand of 5 cards
    //draw(5);
}

Player::~Player() {
    // Clean up dynamically allocated cards
    for (Card* card : hand) delete card;
    for (Card* card : deck) delete card;
    for (Card* card : discard) delete card;
    for (Card* card : playedCards) delete card;
}

std::string Player::getName() const {
    return name;
}

int Player::getActions() const {
    return actions;
}

int Player::getPurchases() const {
    return purchases;
}

int Player::getCoins() const {
    return coins;
}

const std::vector<Card*>& Player::getHand() const {
    return hand;
}

