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
	BuildingColorType type; 
	int BuildingNum; 
	WhichSide status; 

public:

	BuildingTile(); 

	BuildingTile(BuildingColorType t, WhichSide s, int n);
	
	~BuildingTile(); 

	BuildingColorType getBuildingColorType() { return type;  }

	WhichSide getSide() { return status;  }

	int getBuildingNum() { return BuildingNum;  }

	void Flip(); 

};

