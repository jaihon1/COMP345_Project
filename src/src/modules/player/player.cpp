#include "player.h"

Player::Player(int playerId) {
    cout << "Creating Player with Main: " << this << endl;
    _harvestTiles = new vector<HarvestTile*>;
    _buildingTiles = new vector<BuildingTile*>;
    _id = &playerId;
}

Player::Player(const Player &player) {
    cout << "Creating Player with Copy: " << this << endl;
    _harvestTiles = player._harvestTiles;
    _buildingTiles = player._buildingTiles;
    _id = player._id;
}

Player::~Player() {
    cout << "Deleting Player with address: " << this << endl;
    delete _harvestTiles;
    delete _buildingTiles;

    _harvestTiles = nullptr;
    _buildingTiles = nullptr;
    cout << "DONE" << endl;
}


HarvestTile* Player::addHarvestTile(HarvestTile &tile) {
    
    _harvestTiles -> push_back(&tile);
    
    return &tile;
}

vector<HarvestTile*>* Player::getHarvestTiles() {
    return _harvestTiles;
}

BuildingTile* Player::addBuildingTile(BuildingTile &tile) {
    _buildingTiles -> push_back(&tile);
    return &tile;
}

