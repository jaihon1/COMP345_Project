#include "player.h"
#include <algorithm>

Player::Player() {
//    cout << "Creating Player with Main: " << this << endl;
    _villageBoard = new VGMaps();
    _harvestTiles = new vector<HarvestTile*>;
    _buildingTiles = new vector<BuildingTile*>;
}

Player::Player(const Player &player) {
//    cout << "Creating Player with Copy: " << this << endl;
    _harvestTiles = player._harvestTiles;
    _buildingTiles = player._buildingTiles;
}

Player::~Player() {
    if (_harvestTiles) {
//        cout << "Deleting _harvestTiles of Player with address: " << this << endl;
        delete _harvestTiles;
        _harvestTiles = nullptr;
//        cout << "DONE" << endl;
    }

    if (_buildingTiles) {
//        cout << "Deleting _buildingTiles of Player with address: " << this << endl;
        delete _buildingTiles;
        _buildingTiles = nullptr;
//        cout << "DONE" << endl;
    }
}


HarvestTile* Player::addHarvestTile(HarvestTile &tile) {
    _harvestTiles -> push_back(&tile);
    return &tile;
}

HarvestTile* Player::removeHarvestTile(HarvestTile &tile) {
    _harvestTiles -> erase(std::remove(_harvestTiles -> begin(), _harvestTiles -> end(), &tile), _harvestTiles -> end());
    return &tile;
}

vector<HarvestTile*>* Player::getHarvestTiles() {
    for (int i = 0; i < _harvestTiles->size(); i++) {
        cout << (*_harvestTiles)[i] << endl;
    }
    return _harvestTiles;
}

void Player::placeHarvestTile(int row, int col, HarvestTile &tile, GBMaps &gameBoard) {
    gameBoard.addHarvestTile(row, col, &tile);
    removeHarvestTile(tile);
}

HarvestTile* Player::drawHarvestTile(HarvestDeck &deck) {
    HarvestTile *drawn_card = deck.draw();
    addHarvestTile(*drawn_card);
    return drawn_card;
}

unsigned long Player::getNumberOfHarvestTiles() {
    return _harvestTiles -> size();
}


vector<BuildingTile*>* Player::getBuildings() {
    for (int i = 0; i < _buildingTiles->size(); i++) {
        cout << (*_buildingTiles)[i] << endl;
    }
    return _buildingTiles;
}

BuildingTile* Player::addBuildingTile(BuildingTile &tile) {
    _buildingTiles -> push_back(&tile);
    return &tile;
}

BuildingTile* Player::removeBuildingTile(BuildingTile &tile) {
    _buildingTiles -> erase(std::remove(_buildingTiles -> begin(), _buildingTiles -> end(), &tile), _buildingTiles -> end());
    return &tile;
}

BuildingTile* Player::drawBuilding(BuildingDeck &deck) {
    BuildingTile *drawn_card = deck.draw();
    addBuildingTile(*drawn_card);
    return drawn_card;
}

unsigned long Player::getNumberOfBuildingTiles() {
    return _buildingTiles -> size();
}

void Player::ressourceTracker() {
    cout << "--Player Resources--" << endl;
    cout << "Number of Building Tiles: " << getNumberOfBuildingTiles() << endl;
    cout << "Number of Harvest Tiles: " << getNumberOfHarvestTiles() << endl << endl;
    cout << "Building Tiles: " << endl;
    getBuildings();
    cout << endl << "Harvest Tiles: " << endl;
    getHarvestTiles();
    cout << "-- END --" << endl << endl;
}
