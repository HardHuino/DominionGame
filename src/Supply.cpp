#include "Supply.hpp"
using namespace std;
//------TO BE IMPLEMENTED
void Supply::initializeSupply(int nbOfPlayers){ //Setsup the Game depending on the number of players
    nbOfPlayers=nbOfPlayers;
    //TreasureCards
    piles.insert({"Copper", *new CardPile(new TreasureCard("Copper",0,1),10)});
    piles.insert({"Silver", *new CardPile(new TreasureCard("Silver",3,2),10)});
    piles.insert({"Gold", *new CardPile(new TreasureCard("Gold",6,3),10)});
    //VictoryCards
    piles.insert({"Curse", *new CardPile(new VictoryCard("Curse",0,-1),10)});
    piles.insert({"Estate", *new CardPile(new VictoryCard("Estate",1,1),10)});
    piles.insert({"Duchee", *new CardPile(new VictoryCard("Duchee",4,3),10)});
    piles.insert({"Province", *new CardPile(new VictoryCard("Province",8,6),6)});
}

CardPile* Supply::getPile(const string& name){
    for (auto& i : piles){ //Searches through all of the pile (the map containing names and their associated CardPile)
        if(i.first==name){ //If name matches
            return &i.second; //Returns the pointer to the CardPile
        }
    }
    throw "Name not found in Piles"; //Throws an error if the name doesn't match
}

bool Supply::checkGameEnd(){ //Counts number of empty piles to check if game ends
    int nbEmptyPiles=0;
    for (auto& i : piles){ //Runs through all the piles
        if(i.second.getQuantity()<=0){ //Checks if that pile is empty
            //-------TO BE IMPLEMENTED
            if(i.first==""){ //If the pile is empty and it's the one pile that ends the game immediately
                return true; 
            }
            else{ //Otherwise just adds one to the number of empty piles
                nbEmptyPiles+=1;
            }
        }
    }
    if (nbEmptyPiles>=3){ //Checks if there are at least 3 empty piles
        return true;
    }
    return false;
}