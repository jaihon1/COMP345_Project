#include "BuildingDeck.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

BuildingDeck::BuildingDeck() {
    cout << "Creating BuildingDeck with Main: " << this << endl;
    _deck = new vector<BuildingTile*>;
    
    // Initialize deck with what is specified in assignment1!!
    BuildingColorType greenSheep = BuildingColorType::GreenSheep;
    BuildingColorType greyRock = BuildingColorType::GreyRock;
    BuildingColorType redLumber = BuildingColorType::RedLumber;
    BuildingColorType yellowHay = BuildingColorType::YellowHay;
    
    BuildingStatus normal = BuildingStatus::Normal;
    
    BuildingTile buildingTile1(greenSheep, normal);
    BuildingTile buildingTile2(greyRock, normal);
    BuildingTile buildingTile3(redLumber, normal);
    BuildingTile buildingTile4(yellowHay, normal);
    
    cout << "Adding tile: " << &buildingTile1 << endl;
    _deck -> push_back(&buildingTile1);
    cout << "Adding tile: " << &buildingTile2 << endl;
    _deck -> push_back(&buildingTile2);
    cout << "Adding tile: " << &buildingTile3 << endl;
    _deck -> push_back(&buildingTile3);
    cout << "Adding tile: " << &buildingTile4 << endl;
    _deck -> push_back(&buildingTile4);

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

