#pragma once



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


