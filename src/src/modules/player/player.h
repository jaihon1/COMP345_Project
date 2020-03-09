
#ifndef player_h
#define player_h

#include <iostream>
#include <stdio.h>
#include <vector>
#include "../board/VGMaps.h"
#include "../tile/Resources.h"
#include "../board/GBMaps.h"

using namespace std;

class Player {
private:
    // Own one Village Board
    VGMaps *_villageBoard;
    
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
        
    // Manage Harvest Tiles
    vector<HarvestTile*>* getHarvestTiles();
    HarvestTile* addHarvestTile(HarvestTile &tile);
    HarvestTile* removeHarvestTile(HarvestTile &tile);
    void placeHarvestTile(int row, int col, HarvestTile &tile, GBMaps &gameBoard);
    HarvestTile* drawHarvestTile(HarvestDeck &deck);
    unsigned long getNumberOfHarvestTiles();
    
    // Manage Building Tiles
    vector<BuildingTile*>* getBuildings();
    BuildingTile* addBuildingTile(BuildingTile &tile);
    BuildingTile* removeBuildingTile(BuildingTile &tile);
    BuildingTile* drawBuilding(BuildingDeck &deck);
    unsigned long getNumberOfBuildingTiles();
    
    // Methods for the driver
    void ressourceTracker();
    void buildVillage();
    void calculateResources();
    
    
};

#endif /* player_h */
