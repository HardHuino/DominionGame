#ifndef GAME_HPP
#define GAME_HPP

#include "Player.hpp"
#include "Supply.hpp"

#include <vector>
#include <iostream>
#include <string>

class Card;

class Game {
private:
    std::vector<Player> players;
    Supply supply;
    std::vector<std::unique_ptr<Card> > trash; // cards removed from the game ("Rebut")
    int activePlayerIndex;
public:
    // Constructeur
    Game();

    // Destructeur
    virtual ~Game() = default;

    void startGame();
    void playTurn();

    void trashCard(std::unique_ptr<Card> card);

    const Supply& getSupply() const;
    Supply& getSupply();
    std::vector<Player>& getPlayers();
    const std::vector<std::unique_ptr<Card> >& getTrash() const;
};

#endif // GAME_HPP