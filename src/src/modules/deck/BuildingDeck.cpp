#include "BuildingDeck.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

BuildingDeck::BuildingDeck() {
    cout << "Creating BuildingDeck with Main: " << this << endl;
    
    // Initializing deck size
    int size = 9;
    _sizeMax = &size;
    
    // Initialize deck resources
    BuildingColorType greenSheep = BuildingColorType::GreenSheep;
    BuildingColorType greyRock = BuildingColorType::GreyRock;
    BuildingColorType redLumber = BuildingColorType::RedLumber;
    BuildingColorType yellowHay = BuildingColorType::YellowHay;
    
    BuildingStatus normal = BuildingStatus::Normal;
    
    BuildingTile tiles[9] = {
        BuildingTile(greenSheep, normal),
        BuildingTile(greyRock, normal),
        BuildingTile(redLumber, normal),
        BuildingTile(yellowHay, normal),
        BuildingTile(greenSheep, normal),
        BuildingTile(greenSheep, normal),
        BuildingTile(greyRock, normal),
        BuildingTile(redLumber, normal),
        BuildingTile(yellowHay, normal)
    };
    
    // Initializing _deck vector
    _deck = new vector<BuildingTile*>;
    
    for (int i = 0; i < *_sizeMax; i++) {
        cout << "Adding tile: " << &tiles[i] << endl;
        _deck -> push_back(&tiles[i]);
    }
    
}

BuildingDeck::BuildingDeck(const BuildingDeck &deck) {
    
}

BuildingDeck::~BuildingDeck() {
    if (_deck) {
        cout << "Deleting _deck of BuildingTile with address: " << this << endl;
        delete _deck;
        _deck = nullptr;
        cout << "DONE" << endl;
    }
}

vector<BuildingTile*>* BuildingDeck::getDeck() {
    return _deck;
}

void BuildingDeck::add(BuildingTile &tile) {
    cout << "Adding: " << &tile << endl;
    _deck -> push_back(&tile);
}

void BuildingDeck::remove(BuildingTile &tile) {
    _deck -> erase(std::remove(_deck -> begin(), _deck -> end(), &tile), _deck -> end());
}

BuildingTile* BuildingDeck::draw() {
    if (_deck -> size() > 0) {
        int randomIndex = rand() % _deck -> size();
        BuildingTile *tile = _deck -> at(randomIndex);
        remove(*tile);
        return tile;
    }
    else {
        return nullptr;
    }
}

unsigned long BuildingDeck::getSize() {
    return _deck -> size();
}

