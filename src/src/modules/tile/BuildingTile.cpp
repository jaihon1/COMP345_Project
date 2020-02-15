#include "BuildingTile.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

BuildingTile::BuildingTile(BuildingColorType type, BuildingStatus status) {
    cout << "Creating Building Tile with Main: " << this << endl;
	_buildingColorType = type;
    _buildingStatus = status;
    _buildingNum = generateBuildingNumber();
}

BuildingTile::~BuildingTile() {

}

BuildingTile::BuildingTile(BuildingColorType t, int n, BuildingStatus s) {
    _buildingColorType = t;
    _buildingNum = n;
    _buildingStatus = s;
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
