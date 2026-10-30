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

    // Asks the players which 10 kingdom cards are in the game (preset, random or one by one)
    std::vector<std::string> chooseKingdom() const;
public:
    // Constructeur
    Game();

    // Destructeur
    virtual ~Game() = default;

    void startGame();

    void trashCard(std::unique_ptr<Card> card);

    // lists the opponents of the attacker that aren't protected by a reaction card (moat)
    std::vector<Player*> getAttackTargets(Player& attacker);

    const Supply& getSupply() const;
    Supply& getSupply();
    std::vector<Player>& getPlayers();
    const std::vector<std::unique_ptr<Card> >& getTrash() const;
};

#endif // GAME_HPP