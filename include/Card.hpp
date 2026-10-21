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

    virtual bool isTreasure() const;
    virtual bool isVictory()  const;
    virtual bool isAction()   const;
    
    std::string getName() const;
    int getCost() const;
};

#endif // CARD_HPP