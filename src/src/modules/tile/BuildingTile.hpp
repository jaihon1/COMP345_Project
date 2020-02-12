#pragma once
#include "Tile.hpp"


enum class BuildingColorType {
	GreenSheep,
	GreyRock,
	RedLumber, 
	YellowHay
};


enum class WhichSide {
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

class BuildingTile :
	//public Tile
{
private: 
	BuildingColorType BuildingType; 
	int BuildingNum; 
	WhichSide Buildingstatus; 

public:

	BuildingTile(); 

	BuildingTile(BuildingColorType t, WhichSide s, int n);
	
	~BuildingTile(); 

	BuildingColorType getBuildingColorType() { return BuildingType;  }

	WhichSide getSide() { return BuildingStatus;  }

	int getBuildingNum() { return BuildingNum;  }

	void Flip(); 

};

