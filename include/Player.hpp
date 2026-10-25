#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Supply.hpp"
#include <vector>
#include <string>
#include <algorithm> // VERIFIER SI ALGORITHM EXISTE

typedef std::vector<std::unique_ptr<Card> > CardList; // Type alias for a vector of unique pointers to Card objects

class Card;

class Player {
private:
    std::string name;
    int actions, purchases,coins;
    CardList hand, deck, discard, playedCards;

    void playTreasures(); // plays all treasure cards in the player's hand, adding their value to the player's coins
    void cleanUp(); // moves all cards from the player's hand and played cards to the discard pile, then draws a new hand of 5 cards

public:
    // Constructeur
    Player(const std::string& name, Supply& supply); // Initializes a player with a given name with 7 copper TAKEN from the supply and 3 estates CREATED (not taken from the supply), and shuffles the deck

    // // Destructeur
    // virtual ~Player();

    void executeTurn(Supply& supply);
    void draw(int numCards);
    void playActionCard(int cardIndex);
    bool buyCard(Supply& supply, const std::string& cardName); // supply -> discard, returns true if the purchase was successful, false otherwise
    void gain(std::unique_ptr<Card> card); // any sources -> discard, adds a card to the player's discard pile
    int countVictoryPoints() const;

    // Getters
    std::string getName() const;
    int getActions() const;
    int getPurchases() const;
    int getCoins() const;
    const CardList& getHand() const;
    int getDeckSize() const;
    int getDiscardSize() const;
};

#endif // PLAYER_HPP