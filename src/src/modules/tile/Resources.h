#pragma once

#include <vector>
#include "Dictionary.h"

using namespace std;

class Tile {

};

class BuildingTile
{
private:

	BuildingColorType _buildingColorType;
	int _buildingNum;
	BuildingStatus _buildingStatus;

public:

	BuildingTile();
	BuildingTile(BuildingColorType type, BuildingStatus status);
	BuildingTile(BuildingColorType t, int n, BuildingStatus s);
	~BuildingTile();

	BuildingColorType getBuildingColorType();
	BuildingStatus getSide();
	int getBuildingNum();
	void setBuildingNum(int num);
	int generateBuildingNumber();
	void flip();

};

class HarvestTile :
	public Tile
{
private:
	ResourceName* resourceArr;

public:
	//parameters are the resources intended for the various locations on the tile
	HarvestTile(ResourceName topRightRes, ResourceName topLeftRes, ResourceName bottomLeftRes, ResourceName bottomRightRes);
    HarvestTile(const HarvestTile &harvestTile);
    HarvestTile();

	~HarvestTile();

	void RotateRight();
	
	void RotateLeft();

	ResourceName getResource(ResourceLocation inLocation);

	static const char* ResourceNameToString(ResourceName inResourceName) {
		switch (inResourceName) {
		case ResourceName::Lumber:
			return "Lumber";

		case ResourceName::Rock:
			return "Rock";

		case ResourceName::Sheep:
			return "Sheep";

		case ResourceName::Wheat:
			return "Wheat";
		}

		return "Error from ResourceNameToString";
	}
};

class HarvestDeck{
private:
	HarvestTile** harvestDeck;
	int deckLength = 60;

public:
	HarvestDeck();
	HarvestTile* draw();
    int getSize();

};

class BuildingDeck {
private:
    int *_sizeMax;
    vector<BuildingTile*> *_deck;
        
public:
    BuildingDeck();
    BuildingDeck(const BuildingDeck &deck);
    ~BuildingDeck();
    
    vector<BuildingTile*>* getDeck();
    BuildingTile* draw();
    unsigned long getSize();
    void add(BuildingTile &tile);
    void remove(BuildingTile &tile);

};



