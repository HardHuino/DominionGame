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
    int activePlayerIndex;
public:
    // Constructeur
    Game(const std::vector<Player>& players, const Supply& supply);

    // Destructeur
    virtual ~Game() = default;

    void startGame();

    const Supply& getSupply() const;
};

#endif // GAME_HPP