#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Supply.hpp"
#include <vector>
#include <string>
#include <algorithm> // VERIFIER SI ALGORITHM EXISTE

typedef std::vector<std::unique_ptr<Card> > CardList; // Type alias for a vector of unique pointers to Card objects

class Card;
class Game;

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

    void executeTurn(Game& game);
    void playActionCard(int cardIndex, Game& game); // hand -> played cards, costs 1 action, then resolves the card
    bool buyCard(Supply& supply, const std::string& cardName); // supply -> discard, returns true if the purchase was successful, false otherwise
    void gain(std::unique_ptr<Card> card); // any sources -> discard, adds a card to the player's discard pile
    int countVictoryPoints() const;

    void draw(int numCards);
    void addActions(int numActions);
    void addPurchases(int numPurchases);
    void addCoins(int numCoins);
    void resetDeck();

    // Primitives function used by action cards
    std::unique_ptr<Card> drawCard();                       // deck -> caller (reshuffles the discard if needed), nullptr if no card left at all
    std::unique_ptr<Card> removeFromHand(int index);        // hand -> caller, nullptr if the index is invalid
    std::unique_ptr<Card> removeFromPlayed(const Card* card); // played cards -> caller, nullptr if the card is not there
    void addToHand(std::unique_ptr<Card> card);             // caller -> hand
    void addToPlayed(std::unique_ptr<Card> card);           // caller -> played cards
    void putOnDeck(std::unique_ptr<Card> card);             // caller -> top of the deck
    void discardCard(std::unique_ptr<Card> card);           // caller -> discard pile
    void discardFromHand(int index);                        // hand -> discard pile
    void discardDeck();                                     // whole deck -> discard pile

    // Getters
    std::string getName() const;
    int getActions() const;
    int getPurchases() const;
    int getCoins() const;
    const CardList& getHand() const;
    int getDeckSize() const;
    int getDiscardSize() const;
    bool hasActionInHand() const;
    int indexCardInHand(std::unique_ptr<Card> card) const;
};

#endif // PLAYER_HPP