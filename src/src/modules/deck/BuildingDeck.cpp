#include "BuildingDeck.h"

BuildingDeck::BuildingDeck() {
    
}

BuildingDeck::BuildingDeck(const BuildingDeck &deck) {
    
}

BuildingDeck::~BuildingDeck() {
    
}

vector<BuildingTile*>* BuildingDeck::getDeck() {
    return _deck;
}

void BuildingDeck::add(BuildingTile &tile) {
    _deck -> push_back(&tile);
}

unsigned long BuildingDeck::getSize() {
    return _deck -> size();
}

