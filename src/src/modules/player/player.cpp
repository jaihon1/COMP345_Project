#include "player.h"
#include <algorithm>

Player::Player() {
    cout << "Creating Player with Main: " << this << endl;
    _harvestTiles = new vector<HarvestTile*>;
    _buildingTiles = new vector<BuildingTile*>;
}

Player::Player(const Player &player) {
    cout << "Creating Player with Copy: " << this << endl;
    _harvestTiles = player._harvestTiles;
    _buildingTiles = player._buildingTiles;
}

Player::~Player() {
    if (_harvestTiles) {
        cout << "Deleting _harvestTiles of Player with address: " << this << endl;
        delete _harvestTiles;
        _harvestTiles = nullptr;
        cout << "DONE" << endl;
    }

    if (_buildingTiles) {
        cout << "Deleting _buildingTiles of Player with address: " << this << endl;
        delete _buildingTiles;
        _buildingTiles = nullptr;
        cout << "DONE" << endl;
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

BuildingTile* Player::addBuildingTile(BuildingTile &tile) {
    _buildingTiles -> push_back(&tile);
    return &tile;
}

