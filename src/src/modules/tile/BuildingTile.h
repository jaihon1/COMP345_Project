#pragma once
#include "Tile.h"
#include "Dictionary.h"


class BuildingTile : public Tile {
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

