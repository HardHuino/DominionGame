#include "Village.hpp"
#include "Player.hpp"

Village::Village() : ActionCard("Village", 3) {}

//+1 Card, +2 Actions
void Village::effect(Player& player, Game&) {
    player.draw(1);
    player.addActions(2);
}