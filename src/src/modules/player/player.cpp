#include "player.h"

Player::Player(int playerId) {
    _harvestTiles = new vector<HarvestTile>;
    _buildingTiles = new vector<BuildingTile>;
    _id = &playerId;
}

Player::~Player() {
    delete _harvestTiles;
    delete _buildingTiles;
    
    _harvestTiles = nullptr;
    _buildingTiles = nullptr;
}


HarvestTile Player::addHarvesTile(HarvestTile tile) {
    _harvestTiles -> push_back(tile);
    return tile;
}

BuildingTile Player::addBuildingTile(BuildingTile tile) {
    _buildingTiles -> push_back(tile);
    return tile;
}

