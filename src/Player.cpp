#include "Player.hpp"

#include "ActionCard.hpp"
#include "Game.hpp"
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
        deck.push_back(std::unique_ptr<Card>(new VictoryCard("Estate", 2, 1, false)));
    std::shuffle(deck.begin(), deck.end(), rng());

    // Draw the initial hand of 5 cards
    draw(5);
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

void Player::executeTurn(Game& game){
    Supply& supply = game.getSupply();
    actions = 1; purchases = 1; coins = 0;
    Display::showTurnHeader(*this);
    Display::showHand(*this);

    // ---- Action Phase : TODO (jouer une carte Action tant que actions > 0)
    while (actions > 0 && hasActionInHand()) {
        Display::showStatus(*this);
        int choice = Display::askChoice("Carte Action a jouer (0 pour passer) : ", 0, static_cast<int>(hand.size()));
        if (choice == 0) break;
        if (!hand[choice - 1]->isAction()) {
            Display::showMessage("Ce n'est pas une carte Action.");
            continue;
        }
        playActionCard(choice - 1, game);
        Display::showHand(*this); // the hand changed
    }

    // ---- Purchase Phase
    // for(auto card : hand){ //Money calculation
    //     if(card->isTreasure()){
    //         coins+=static_cast<TreasureCard*>(card)->getValue(); //workaround to get value of a TreasureCard, since hand is a vector of Card* and not TreasureCard* NEED TO BE FIXED
    //     }
    // } // FIXED : using playTreasures() function instead of the above code to calculate coins
    playTreasures(); // all the treasures of the hand are played automatically

    while(purchases>0){ //Allows player to purchase cards
        Display::showStatus(*this);
        Display::showSupply(supply, coins); //Shows the Supply of cards
        std::cout<<"You have "<<purchases<<" purchases left. What do you want to buy? (Type in the name, or press Enter to end your turn)"<<endl<<"-->";
        string name;
        name = Display::askLine(""); //Asks the user which card they want to buy.
        if (name.empty()) break; // the player stops buying
        if(!buyCard(supply, name)) { //Attempts to buy the card
            std::cout<<"Failed to buy the card."<<endl; //Otherwise
        }
    }
    //Draws a new hand
    /*
    /for(int i=0; i<5; i++){
        draw(5);
    }
    */

    // ---- Ajustment Phase
    cleanUp();
}

void Player::playActionCard(int cardIndex, Game& game) {
    if (actions <= 0) return;
    if (cardIndex < 0 || cardIndex >= static_cast<int>(hand.size())) return;
    if (!hand[cardIndex]->isAction()) return;

    std::unique_ptr<Card> card = removeFromHand(cardIndex);
    ActionCard* action = static_cast<ActionCard*>(card.get()); // safe : isAction() was checked
    playedCards.push_back(std::move(card)); // the card is in play BEFORE its effect (e.g. Feast trashes itself from there)
    --actions;

    Display::showMessage(name + " joue " + Display::cardLabel(*action));
    action->effect(*this, game);
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

int Player::countVictoryPoints() const {
    int totalVP = 0;
    /*
    for (const auto& card : hand) {
        if (card->isVictory()) totalVP += static_cast<VictoryCard*>(card.get())->getVictoryPoints();
    }
    for (const auto& card : deck) {
        if (card->isVictory()) totalVP += static_cast<VictoryCard*>(card.get())->getVictoryPoints();
    }
    for (const auto& card : discard) {
        if (card->isVictory()) totalVP += static_cast<VictoryCard*>(card.get())->getVictoryPoints();
    }
    */
    // 1st attempt at garden
    int nbGardens = 0; //For scoring with gardens
    for (const auto& card : deck) {
        if (card->isVictory()){
            if (static_cast<VictoryCard*>(card.get())->getIsGarden()) nbGardens++;
            else totalVP += static_cast<VictoryCard*>(card.get())->getVictoryPoints();
        }
    }
    totalVP += floor(nbGardens*0.1*deck.size());
    return totalVP; // TODO : add support for special cards that give victory points based on other conditions (e.g., Gardens, Duke, etc.)
}

void Player::resetDeck(){
    for (std::unique_ptr<Card>& c : hand) deck.push_back(std::move(c));
    for (std::unique_ptr<Card>& c : discard) deck.push_back(std::move(c));
    hand.clear();
    discard.clear();
}

std::unique_ptr<Card> Player::drawCard() { // needed to be separated from draw function because some card need to be seen before going anywhere
    if (deck.empty() && !discard.empty()) {
        // empty deck -> Shuffle the discard pile into the deck
        std::shuffle(discard.begin(), discard.end(), rng());
        deck.swap(discard);
    }
    if (deck.empty()) return nullptr; // no card left anywhere
    std::unique_ptr<Card> card = std::move(deck.back()); // the top of the deck is the back of the vector
    deck.pop_back();
    return card;
}

void Player::draw(int numCards){
    for(int i=0; i<numCards; i++){
        std::unique_ptr<Card> card = drawCard();
        if (!card) break; // nothing left to draw
        hand.push_back(std::move(card)); // std::move allow to cannibalize the unique_ptr from the deck to the hand
    }
}

std::unique_ptr<Card> Player::removeFromHand(int index) {
    if (index < 0 || index >= static_cast<int>(hand.size())) return nullptr;
    std::unique_ptr<Card> card = std::move(hand[index]);
    hand.erase(hand.begin() + index);
    return card;
}

std::unique_ptr<Card> Player::removeFromPlayed(const Card* card) {
    for (std::size_t i = 0; i < playedCards.size(); i++) {
        if (playedCards[i].get() == card) {
            std::unique_ptr<Card> found = std::move(playedCards[i]);
            playedCards.erase(playedCards.begin() + i);
            return found;
        }
    }
    return nullptr;
}

// May or may not be used
void Player::addToHand(std::unique_ptr<Card> card)   { if (card) hand.push_back(std::move(card)); }
void Player::addToPlayed(std::unique_ptr<Card> card) { if (card) playedCards.push_back(std::move(card)); }
void Player::putOnDeck(std::unique_ptr<Card> card)   { if (card) deck.push_back(std::move(card)); }
void Player::discardCard(std::unique_ptr<Card> card) { if (card) discard.push_back(std::move(card)); }

void Player::discardFromHand(int index) {
    discardCard(removeFromHand(index));
}

void Player::discardDeck() {
    for (std::unique_ptr<Card>& c : deck) discard.push_back(std::move(c));
    deck.clear();
}

bool Player::hasActionInHand() const {
    for (const std::unique_ptr<Card>& c : hand)
        if (c->isAction()) return true;
    return false;
}

int Player::indexCardInHand(std::unique_ptr<Card> card) const{
    for (std::size_t i=0; i<hand.size(); i++){
        if (hand.at(i)->getName()==card->getName()){return i;}
    }
    return -1;
}

void Player::addActions(int numActions) { actions += numActions; }
void Player::addPurchases(int numPurchases) { purchases += numPurchases; }
void Player::addCoins(int numCoins) { coins += numCoins; }

// Getters

std::string Player::getName() const { return name; }
const CardList& Player::getHand() const { return hand; }
int Player::getActions() const { return actions; }
int Player::getPurchases() const { return purchases; }
int Player::getCoins() const { return coins; }
int Player::getDeckSize() const { return static_cast<int>(deck.size()); }
int Player::getDiscardSize() const { return static_cast<int>(discard.size()); }
