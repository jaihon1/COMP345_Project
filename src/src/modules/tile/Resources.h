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

};


