#pragma once
#include <iostream>
#include <stdio.h>
#include <vector>
#include "../board/VGMaps.h"
#include "../tile/Resources.h"
#include "../board/GBMaps.h"
using namespace std;

class Player{
private:
    VGMaps *_villageBoard;
    vector<HarvestTile*> *_harvestTiles;
    vector<BuildingTile*> *_buildingTiles;
	HarvestTile* shipmentTile;
	Scoring* sc;
    
    // Owns/Give up Ressource Markers
    // Owns resources Gathering and Building Scoring facilities

	int *ID;
	int* position;
    
public:

	Player(Scoring* inSc, int indexPosition);
    Player(const Player &player);
    ~Player();
        
    // Manage Harvest Tiles
    vector<HarvestTile*>* getHarvestTiles();
    HarvestTile* addHarvestTile(HarvestTile &tile);
    HarvestTile* removeHarvestTile(HarvestTile &tile);
    int placeHarvestTile(int row, int col, HarvestTile &tile, GBMaps &gameBoard);
	int placeShipmentTile(int row, int col, HarvestTile &tile, GBMaps &gameBoard, int type);
    HarvestTile* drawHarvestTile(HarvestDeck &deck);
    unsigned long getNumberOfHarvestTiles();

	void setShipmentTile(HarvestTile* harvestTile);
    
    // Manage Building Tiles
    vector<BuildingTile*>* getBuildings();
    BuildingTile* addBuildingTile(BuildingTile &tile);
    BuildingTile* removeBuildingTile(BuildingTile &tile);
    int placeBuildingTile(int row, int col, BuildingTile &tile);
    BuildingTile* drawBuilding(BuildingDeck &deck);
    unsigned long getNumberOfBuildingTiles();
	VGMaps* getVGMaps(); 
    
    // Building Pool
    BuildingTile* pickFromBuildingPool(BuildingPool &pool, int index);
    
    // Methods for the driver
    void ressourceTracker();
    void buildVillage();
    void calculateResources();

	//for MainLoop
	int getID(); 
	void setID(int n, int index); 
	VGMaps* getVGBoard();

	HarvestTile * getShipmentTile(); 

	int getScore();
	int getPosition();
};


