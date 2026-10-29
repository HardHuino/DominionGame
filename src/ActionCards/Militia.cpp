#include "Militia.hpp"

#include "Display.hpp"
#include "Game.hpp"
#include "Player.hpp"

Militia::Militia() : ActionCard("Militia", 4) {}

// +2 Coins. Each other player discards down to 3 cards in hand (Attack)
void Militia::effect(Player& player, Game& game) {
    player.addCoins(2);

    for (Player* target : getAttackTargets(player, game)) {
        while (target->getHand().size() > 3) {
            int index = chooseFromHand(*target, target->getName() + " : defaussez une carte (3 cartes maximum en main)", Choice::Must);
            if (index < 0) break;
            target->discardFromHand(index);
        }
    }
}