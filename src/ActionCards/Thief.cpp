#include "Thief.hpp"

#include "Display.hpp"
#include "Game.hpp"
#include "Player.hpp"

Thief::Thief() : ActionCard("Thief", 4) {}

// Each other player reveals the top 2 cards of his deck. If they revealed Treasures,
// they trash one of them that you choose. You may gain any or all of these trashed cards.
// They discard the other revealed cards (Attack)
void Thief::effect(Player& player, Game& game) {
    for (Player* target : game.getAttackTargets(player)) {
        CardList treasures, others;

        for (int i = 0; i < 2; ++i) {
            std::unique_ptr<Card> card = target->drawCard();
            if (!card) break;
            Display::showMessage(target->getName() + " devoile " + Display::cardLabel(*card));
            if (card->isTreasure()) treasures.push_back(std::move(card));
            else                    others.push_back(std::move(card));
        }

        // The attacker chooses which Treasure is trashed when there are two
        std::unique_ptr<Card> stolen;
        if (treasures.size() == 1) {
            stolen = std::move(treasures[0]);
        } else if (treasures.size() == 2) {
            int choice = Display::askChoice("Ecarter 1 = " + Display::cardLabel(*treasures[0])
                                            + " ou 2 = " + Display::cardLabel(*treasures[1]) + " ? ", 1, 2);
            stolen = std::move(treasures[choice - 1]);
            others.push_back(std::move(treasures[2 - choice])); // the other Treasure is simply discarded
        }

        for (std::unique_ptr<Card>& c : others) target->discardCard(std::move(c));

        if (stolen) {
            if (Display::askChoice("Recuperer " + Display::cardLabel(*stolen) + " pour vous ? (1 = oui, 0 = non) : ", 0, 1) == 1) {
                Display::showMessage(player.getName() + " recupere " + Display::cardLabel(*stolen));
                player.gain(std::move(stolen));
            } else {
                game.trashCard(std::move(stolen));
            }
        }
    }
}