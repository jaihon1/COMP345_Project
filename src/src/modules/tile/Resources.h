#pragma once
#include "Dictionary.h"

enum class BuildingColorType {
	GreenSheep,
	GreyRock,
	RedLumber,
	YellowHay
};


enum class BuildingStatus {
	Normal,
	Flipped
};


/**
enum class Connection {
	Up,
	Down,
	Right,
	Left
};
**/

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
};

class PondTile :
	public Tile
{
};

class Deck {
public:
	Tile* draw();
};

class HarvestDeck : public Deck {
private:
	HarvestTile* harvestDeck;
public:
	HarvestDeck();
};


