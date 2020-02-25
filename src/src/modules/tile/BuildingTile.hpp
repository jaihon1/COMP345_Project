#pragma once
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


enum class BuildingColorType {
	GreenSheep,
	GreyRock,
	RedLumber, 
	YellowHay,
	None //initial value for the initialization of the empty VGMap - matches VGSlotStatus::Empty
};


enum class BuildingStatus {
	Normal, 
	Flipped 
};


class BuildingTile
{
private:

	BuildingColorType* _buildingColorType;
	int* _buildingNum;
	BuildingStatus* _buildingStatus;
	 
public:
	
	BuildingTile();
	BuildingTile(BuildingColorType* type, BuildingStatus* status);
	BuildingTile(BuildingColorType *t, int *n, BuildingStatus *s);
	~BuildingTile();

	BuildingColorType getBuildingColorType();
	BuildingStatus getSide();
	int getBuildingNum();
	void setBuildingNum(int num);

	void setBuildingStatus(BuildingStatus s); 

	int* generateBuildingNumber();
	void flip();

}; 


