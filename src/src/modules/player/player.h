#ifndef player_hpp
#define player_hpp

#include <iostream>
#include <stdio.h>
#include <vector>
#include "HarvestTile.h"
#include "BuildingTile.h"

using namespace std;

class Player {
private:
    // Own one Village Board
    
    // Owns Harverst Tiles
    vector<HarvestTile*> *_harvestTiles;
    
    // Owns Building Tiles
    vector<BuildingTile*> *_buildingTiles;
    
    // Owns/Give up Ressource Markers
    
    // Owns resources Gathering and Building Scoring facilities
    
    
public:
    Player();
    Player(const Player &player);
    ~Player();
    
    
    // Must be changed to return a Village Board type
    int getVillageBoard();
    int setVillageBoard(int villageBoard);

    // Manage Harvest Tiles
    vector<HarvestTile*>* getHarvestTiles();
    HarvestTile* addHarvestTile(HarvestTile &tile);
    HarvestTile* removeHarvestTile(HarvestTile &tile);
    HarvestTile* placeHarvestTile(HarvestTile &tile);
    HarvestTile* drawHarvestTile(int harvestDeck); // Will need the Deck to be implemented
    
    // Manage Building Tiles
    vector<BuildingTile> getBuildings();
    BuildingTile* addBuildingTile(BuildingTile &tile);
    BuildingTile* removeBuildingTile(BuildingTile &tile);
    BuildingTile* drawBuilding(int buildingDeck); // Will need the Deck to be implemented
    
    // Methods for the driver
    void ressourceTracker();
    void buildVillage();
    void calculateResources();
    
    
};

#endif /* player_hpp */
