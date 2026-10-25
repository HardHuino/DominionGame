#ifndef CARD_HPP
#define CARD_HPP

#include <string>

class Card {
private:
    std::string name;
    int cost;
public:
    // Constructeur
    Card(const std::string& name, int cost);

    // Destructeur
    virtual ~Card() = default;

    virtual bool isTreasure() const { return false; }
    virtual bool isVictory()  const { return false; }
    virtual bool isAction()   const { return false; }
    
    std::string getName() const;
    int getCost() const;
};

#endif // CARD_HPP