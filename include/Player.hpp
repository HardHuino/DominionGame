#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include <string>

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
public:
    // Constructeur
    Player(const std::string& name);

    // Destructeur
    virtual ~Player() = default;

    void executeTurn();
    void draw(int numCards);
    void playActionCard(int cardIndex);
    void buyCard(Card* card);
    int countVictoryPoints() const;
};

#endif // PLAYER_HPP