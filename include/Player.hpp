#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include <string>
#include <algorithm> // VERIFIER SI ALGORITHM EXISTE

class Card;

class Player {
private:
    std::string name;
    int actions;
    int purchases;
    int coins;
    std::vector<Card*> hand;
    std::vector<Card*> deck;
    std::vector<Card*> discard;
    std::vector<Card*> playedCards;
public:
    // Constructeur
    Player(const std::string& name);

    // Destructeur
    virtual ~Player();

    // Getters
    std::string getName() const;
    int getActions() const;
    int getPurchases() const;
    int getCoins() const;
    const std::vector<Card*>& getHand() const;

    void executeTurn();
    void draw(int numCards);
    void playActionCard(int cardIndex);
    void buyCard(Card* card);
    int countVictoryPoints() const;
};

#endif // PLAYER_HPP