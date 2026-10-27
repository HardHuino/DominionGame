#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <string>
#include <vector>

class Card;
class Player;
class Supply;

class Display {
public:
    static void showTurnHeader(const Player& player);
    static void showHand(const Player& player);
    static void showSupply(const Supply& supply, int coins);
    static void showStatus(const Player& player);      // actions / purchases / coins
    static void showMessage(const std::string& text);
    static void showWinner(const std::vector<Player>& players);

    // safe inputs
    static std::string askLine(const std::string& prompt);
    static int askChoice(const std::string& prompt, int min, int max);

private:
    static std::string cardLabel(const Card& card);    // colored name + cout
};

#endif