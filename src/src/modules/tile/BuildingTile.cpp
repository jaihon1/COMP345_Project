#include "BuildingTile.h"
#include <stdlib.h>

BuildingTile::BuildingTile(BuildingColorType type, BuildingStatus status) {
	_buildingColorType = type;
    _buildingStatus = status;
    _buildingNum = generateBuildingNumber();
}

BuildingTile::~BuildingTile() {

}

BuildingColorType BuildingTile::getBuildingColorType() {
    return _buildingColorType;
}

BuildingStatus BuildingTile::getSide() {
    return _buildingStatus;
}

int BuildingTile::getBuildingNum() {
    return _buildingNum;
}

int BuildingTile::generateBuildingNumber() {
    int random = rand() % 6 + 1; //generate a random number from 1 to 6
    return random;
}

void BuildingTile::setBuildingNum(int num) {
    _buildingNum = num;
}

void BuildingTile::flip() {
	if (getSide() == BuildingStatus::Normal) {
		setBuildingNum(-1); 
	}
	//cannot flip back
}
