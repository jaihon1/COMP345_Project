#include "BuildingTile.hpp"
#include <cstdlib>

//<<<<<<< Updated upstream
//randomized
// int random = rand() % 6 + 1; //generate a random number from 1 to 6 
//=======

BuildingTile::BuildingTile()
{
	//
}

BuildingTile::BuildingTile(BuildingColorType *type, BuildingStatus *status) : _buildingColorType(type), _buildingStatus(status), _buildingNum(generateBuildingNumber())
{
	//*_buildingColorType = type;
	//*_buildingStatus = status;
	//_buildingNum = generateBuildingNumber();
}

BuildingTile::BuildingTile(BuildingColorType t, int n, BuildingStatus s)
{
	*_buildingColorType = t; 
	*_buildingNum = n;
	*_buildingStatus = s; 
}

BuildingTile::~BuildingTile() {
	//do I need to code? 
	//if the member variables dont go on the stack, make them dynamic objects and delete every 
	//random to delete 
	//delete _int

	delete _buildingColorType; 
	_buildingColorType = NULL; 
	delete _buildingStatus;
	_buildingStatus = NULL; 

	//delete _buildingNum; 
	//_buildingNum = NULL; 



}

BuildingColorType BuildingTile::getBuildingColorType() {
	return *_buildingColorType;
}

BuildingStatus BuildingTile::getSide() {
	return *_buildingStatus;
}

int BuildingTile::getBuildingNum() {
	return *_buildingNum;
}

int *BuildingTile::generateBuildingNumber() {
	int rando = rand() % 6 + 1; //generate a random number from 1 to 6
	int* random = &rando; //generate a random number from 1 to 6
	return random;
}

void BuildingTile::setBuildingNum(int num) {
	*_buildingNum = num;
}

void BuildingTile::flip() {
	if (getSide() == BuildingStatus::Normal) {
		setBuildingNum(-1);
	}
	//cannot flip back

	
}
