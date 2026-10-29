#include "Moat.hpp"
#include "Player.hpp"

Moat::Moat() : ActionCard("Moat", 4) {}

// +2 Cards, When another player plays an attack card, you may first reveal this from your hand to be unaffected by it
void Moat::effect(Player& player, Game&) {
    player.draw(2);
}

bool Moat::blocksAttack() const {return true;}