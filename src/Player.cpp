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

void Player::executeTurn(Supply supply){
    //Play action cards

    // - - - - - Purchases
    for(auto card : hand){ //Money calculation
        if(card.isTreasure()){
            coins+=card.getValue();
        }
    }
    while(purchases>0){ //Allows player to purchase cards
        cout<<supply.getPiles()<<endl; //Shows the Supply of cards
        cout<<"You have "<<purchases<<" purchases left. What do you want to buy? (Type in the name)"<<endl<<"-->";
        string name;
        cin>>name; //Asks the user which card they want to buy.
        if(supply.getPile(name).getQuantity()>0){ //If that CardPile still has cards in it :
            discard.pushback(supply.getPile(name).removeCard()); //Removes the card from the Supply and puts it in the player's discard
            purchases--; //Decreases nb of purchases left
        }
        else{cout<<"That pile is empty"<<endl;} //Otherwise
    }

    //End of turn
    discard.pushback(hand);
    hand.clear();
    discard.pushback(playedCards);
    playedCards.clear();
    //Draws a new hand
    /*
    /for(int i=0; i<5; i++){
        draw(5);
    }
    */
}

Player::draw(int numCards){
    for(int i=0; i<numCards; i++){
        if(deck.size()>0){
            hand.pushback(deck.at(deck.size()-1));
            deck.remove(deck.at(deck.size()-1));
        }
    }
}