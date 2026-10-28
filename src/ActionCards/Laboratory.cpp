#include "Laboratory.hpp"
#include "Player.hpp"
#include "Game.hpp"
#include <memory>
#include <utility>

void Laboratory::effect(Player& player, Game&) {
    player.draw(2);
    player.addActions(1);
}