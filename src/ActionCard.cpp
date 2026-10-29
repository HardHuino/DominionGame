#include "ActionCard.hpp"

#include "CardPile.hpp"
#include "Display.hpp"
#include "Game.hpp"
#include "Player.hpp"
#include "Supply.hpp"


ActionCard::ActionCard(const std::string& name, int cost)
    : Card(name, cost) {}

bool ActionCard::isAction() const {
    return true;
}

bool ActionCard::blocksAttack() const {
    return false;
}

int ActionCard::chooseFromHand(Player& player, const std::string& prompt, Choice choice, const CardFilter& filter) {
    const CardList& hand = player.getHand();

    // Is there at least one card the player is allowed to choose ?
    bool anyEligible = false;
    for (std::size_t i = 0; i < hand.size(); ++i)
        if (!filter || filter(*hand[i])) anyEligible = true;
    if (!anyEligible) return -1;

    while (true) {
        Display::showHand(player);
        const bool may = (choice == Choice::May);
        int answer = Display::askChoice(prompt + (may ? " (0 pour passer) : " : " : "),
                                        may ? 0 : 1, static_cast<int>(hand.size()));
        if (answer == 0) return -1;
        if (!filter || filter(*hand[answer - 1])) return answer - 1;
        Display::showMessage("Cette carte ne convient pas pour cet effet.");
    }
}

CardPile* ActionCard::chooseFromSupply(Game& game, const std::string& prompt, const CardFilter& filter) {
    Supply& supply = game.getSupply();

    std::vector<CardPile*> options;
    for (const auto& entry : supply.getPiles()) {
        CardPile* pile = supply.getPile(entry.first);
        if (pile && !pile->isEmpty() && (!filter || filter(pile->getModel()))) //Rajoute les piles qui existe, qui ne sont pas vide et qui soit il n'y a pas de filtre soit le filtre est accompli par le model de la pile
            options.push_back(pile);
    }
    if (options.empty()) {
        Display::showMessage("Aucune carte de la reserve ne convient.");
        return nullptr;
    }

    Display::showMessage(prompt);
    for (std::size_t i = 0; i < options.size(); ++i)
        Display::showMessage("  [" + std::to_string(i + 1) + "] " + Display::cardLabel(options[i]->getModel())
                             + " x" + std::to_string(options[i]->getQuantity()));
    int choice = Display::askChoice("Votre choix : ", 1, static_cast<int>(options.size()));
    return options[choice - 1];
}
