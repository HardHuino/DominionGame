#include "Player.hpp"

#include "TreasureCard.hpp"
#include "VictoryCard.hpp"
#include "Display.hpp" 
#include "Random.hpp"

#include <algorithm>
#include <stdexcept>
#include <utility>
#include <iostream>

Player::Player(const std::string& name, Supply& supply) : name(name), actions(1), purchases(1), coins(0) {
    // Initialize the player's deck with 7 Copper cards and 3 Estate cards
    for (int i = 0; i < 7; ++i) { // Copper are taken from the Supply, so we need to check if there are enough Copper cards available
    std::unique_ptr<Card> card = supply.takeCard("Copper");
    if (!card) throw std::runtime_error("Supply insuffisant pour le deck de depart");
    deck.push_back(std::move(card));
    }
    for (int i = 0; i < 3; ++i) // Estate are NOT taken from the Supply, so we can create them directly
        deck.push_back(std::unique_ptr<Card>(new VictoryCard("Estate", 2, 1)));
    std::shuffle(deck.begin(), deck.end(), rng());
    // Draw the initial hand of 5 cards
    //draw(5);
}

// Player::~Player() {
//     // Clean up dynamically allocated cards
//     for (std::unique_ptr<Card>& card : hand) delete card.get();
//     for (std::unique_ptr<Card>& card : deck) delete card.get();
//     for (std::unique_ptr<Card>& card : discard) delete card.get();
//     for (std::unique_ptr<Card>& card : playedCards) delete card.get();
// }

void Player::playTreasures() {
    CardList remaining;
    for (std::unique_ptr<Card>& c : hand) {
        if (c->isTreasure()) {
            coins += static_cast<TreasureCard*>(c.get())->getValue();
            playedCards.push_back(std::move(c));
        } else {
            remaining.push_back(std::move(c));
        }
    }
    hand.swap(remaining);
}

void Player::cleanUp() {
    for (std::unique_ptr<Card>& c : hand) discard.push_back(std::move(c));
    for (std::unique_ptr<Card>& c : playedCards) discard.push_back(std::move(c));
    hand.clear();
    playedCards.clear();
    draw(5);
}

void Player::executeTurn(Supply& supply){
    actions = 1; purchases = 1; coins = 0;
    Display::showTurnHeader(*this);
    Display::showHand(*this);

    // ---- Action Phase : TODO (jouer une carte Action tant que actions > 0)

    // ---- Purchase Phase
    // for(auto card : hand){ //Money calculation
    //     if(card->isTreasure()){
    //         coins+=static_cast<TreasureCard*>(card)->getValue(); //workaround to get value of a TreasureCard, since hand is a vector of Card* and not TreasureCard* NEED TO BE FIXED
    //     }
    // } // FIXED : using playTreasures() function instead of the above code to calculate coins
    playTreasures();

    while(purchases>0){ //Allows player to purchase cards
        Display::showStatus(*this);
        Display::showSupply(supply, coins); //Shows the Supply of cards
        std::cout<<"You have "<<purchases<<" purchases left. What do you want to buy? (Type in the name)"<<endl<<"-->";
        string name;
        std::cin>>name; //Asks the user which card they want to buy.
        if(!buyCard(supply, name)) { //Attempts to buy the card
            std::cout<<"That pile is empty"<<endl; //Otherwise
        }
    
        // ---- Ajustment Phase (end of turn)
        cleanUp();
    }
    //Draws a new hand
    /*
    /for(int i=0; i<5; i++){
        draw(5);
    }
    */
}

void Player::draw(int numCards){
    for(int i=0; i<numCards; i++){
        if (deck.empty() && !discard.empty()) {
            // empty deck -> Shuffle the discard pile into the deck
            std::shuffle(discard.begin(), discard.end(), rng());
            deck.swap(discard);
        }
        if(deck.size()>0){
            hand.push_back(std::move(deck.back())); // std::move allow to cannibalize the unique_ptr from the deck to the hand
            deck.pop_back();
        }
    }
}

bool Player::buyCard(Supply& supply, const std::string& cardName) {
    CardPile* pile = supply.getPile(cardName);
    if (!pile) {
        std::cout << "The pile for " << cardName << " does not exist." << std::endl;
        return false;
    }

    if (pile->isEmpty()) {
        std::cout << "The pile for " << cardName << " is empty." << std::endl;
        return false;
    }

    if (purchases <= 0) {
        std::cout << "You have no purchases left." << std::endl;
        return false;
    }

    if (coins < pile->getModel().getCost()) {
        std::cout << "You do not have enough coins to buy " << cardName << "." << std::endl;
        return false;
    }

    coins -= pile->getModel().getCost();
    --purchases;
    gain(pile->takeCard());                          // card is taken from the supply and added to the player's discard pile
    return true;
}

void Player::gain(std::unique_ptr<Card> card) { // useful for later with special action cards
    if (card) discard.push_back(std::move(card));
}

// Getters

std::string Player::getName() const { return name; }
const CardList& Player::getHand() const { return hand; }
int Player::getActions() const { return actions; }
int Player::getPurchases() const { return purchases; }
int Player::getCoins() const { return coins; }
int Player::getDeckSize() const { return static_cast<int>(deck.size()); }
int Player::getDiscardSize() const { return static_cast<int>(discard.size()); }
