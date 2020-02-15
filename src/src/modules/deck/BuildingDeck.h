#ifndef BuildingDeck_h
#define BuildingDeck_h

#include <stdio.h>
#include <vector>
#include "BuildingTile.h"
#include "BuildingDeck.h"

using namespace std;


class BuildingDeck {
private:
    vector<BuildingTile*> *_deck;
        
public:
    BuildingDeck();
    BuildingDeck(const BuildingDeck &deck);
    ~BuildingDeck();
    
    vector<BuildingTile*>* getDeck();
    BuildingTile* drawBuilding();
    unsigned long getSize();
    void add(BuildingTile &tile);

};

    

#endif /* BuildingDeck_h */
