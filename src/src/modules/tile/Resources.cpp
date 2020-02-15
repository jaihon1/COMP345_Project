#include <cstdlib>
#include "Resources.h"
#include "Dictionary.h"
#include <iostream>

using namespace std;

HarvestTile::HarvestTile(ResourceName topLeftRes, ResourceName topRightRes, ResourceName bottomLeftRes, ResourceName bottomRightRes)
{
	cout << "Creating HarvestTile with Main: " << this << endl;
	resourceArr = new ResourceName[4] {topLeftRes, topRightRes, bottomLeftRes, bottomRightRes};
}

HarvestTile::HarvestTile(const HarvestTile &harvestTile) {
    cout << "Creating HarvestTile with copy: " << this << endl;
    resourceArr = harvestTile.resourceArr;
}

HarvestTile::~HarvestTile() {
    cout << "Deleting HarvestTile with address: " << this << endl;
	delete[] resourceArr;
    resourceArr = nullptr;
    cout << "DONE" << endl;
}

void HarvestTile::RotateLeft()
{
	ResourceName temp = resourceArr[topLeft];

	resourceArr[topLeft] = resourceArr[topRight];
	resourceArr[topRight] = resourceArr[bottomRight];
	resourceArr[bottomRight] = resourceArr[bottomLeft];
	resourceArr[bottomLeft] = temp;
	
}

void HarvestTile::RotateRight()
{
	ResourceName temp = resourceArr[topLeft];

	resourceArr[topLeft] = resourceArr[bottomLeft];
	resourceArr[bottomLeft] = resourceArr[bottomRight];
	resourceArr[bottomRight] = resourceArr[topRight];
	resourceArr[topRight] = temp;

}

ResourceName HarvestTile::getResource(ResourceLocation inLocation)
{
	return resourceArr[inLocation];
}

//<<<<<<< Updated upstream
//randomized
// int random = rand() % 6 + 1; //generate a random number from 1 to 6 
//=======

BuildingTile::BuildingTile(BuildingColorType type, BuildingStatus status) {
	_buildingColorType = type;
	_buildingStatus = status;
	_buildingNum = generateBuildingNumber();
}

BuildingTile::BuildingTile(BuildingColorType t, int n, BuildingStatus s)
{
	_buildingColorType = t;
	_buildingNum = n;
	_buildingStatus = s;
}

BuildingTile::~BuildingTile() {
	//do I need to code? 
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

HarvestDeck::HarvestDeck()
{
	harvestDeck = new HarvestTile[60]{
		//IMG-1
		HarvestTile(ResourceName::Wheat, ResourceName::Lumber, ResourceName::Wheat, ResourceName::Sheep),
		HarvestTile(ResourceName::Sheep, ResourceName::Sheep, ResourceName::Sheep, ResourceName::Rock),
		HarvestTile(ResourceName::Lumber, ResourceName::Sheep, ResourceName::Lumber, ResourceName::Sheep),
		HarvestTile(ResourceName::Sheep, ResourceName::Wheat, ResourceName::Sheep, ResourceName::Rock),

		HarvestTile(ResourceName::Sheep, ResourceName::Sheep, ResourceName::Sheep, ResourceName::Wheat),
		HarvestTile(ResourceName::Rock, ResourceName::Wheat, ResourceName::Rock, ResourceName::Lumber),
		HarvestTile(ResourceName::Rock, ResourceName::Sheep, ResourceName::Rock, ResourceName::Wheat),
		HarvestTile(ResourceName::Sheep, ResourceName::Rock, ResourceName::Sheep, ResourceName::Lumber),

		HarvestTile(ResourceName::Sheep, ResourceName::Rock, ResourceName::Sheep, ResourceName::Wheat),
		HarvestTile(ResourceName::Wheat, ResourceName::Rock, ResourceName::Wheat, ResourceName::Sheep),
		HarvestTile(ResourceName::Wheat, ResourceName::Wheat, ResourceName::Wheat, ResourceName::Lumber),
		HarvestTile(ResourceName::Rock, ResourceName::Lumber, ResourceName::Rock, ResourceName::Wheat),

		HarvestTile(ResourceName::Wheat, ResourceName::Wheat, ResourceName::Wheat, ResourceName::Rock),
		HarvestTile(ResourceName::Wheat, ResourceName::Wheat, ResourceName::Wheat, ResourceName::Sheep),
		HarvestTile(ResourceName::Lumber, ResourceName::Lumber, ResourceName::Lumber, ResourceName::Wheat),
		HarvestTile(ResourceName::Lumber, ResourceName::Wheat, ResourceName::Lumber, ResourceName::Wheat),

		HarvestTile(ResourceName::Sheep, ResourceName::Wheat, ResourceName::Sheep, ResourceName::Lumber),
		HarvestTile(ResourceName::Sheep, ResourceName::Wheat, ResourceName::Sheep, ResourceName::Wheat),
		HarvestTile(ResourceName::Rock, ResourceName::Rock, ResourceName::Rock, ResourceName::Lumber),
		HarvestTile(ResourceName::Rock, ResourceName::Wheat, ResourceName::Rock, ResourceName::Sheep),

		//IMG-2
		HarvestTile(ResourceName::Rock, ResourceName::Wheat, ResourceName::Lumber, ResourceName::Rock),
		HarvestTile(ResourceName::Wheat, ResourceName::Rock, ResourceName::Lumber, ResourceName::Lumber),
		HarvestTile(ResourceName::Sheep, ResourceName::Lumber, ResourceName::Sheep, ResourceName::Rock),
		HarvestTile(ResourceName::Sheep, ResourceName::Rock, ResourceName::Sheep, ResourceName::Rock),

		HarvestTile(ResourceName::Wheat, ResourceName::Rock, ResourceName::Lumber, ResourceName::Wheat),
		HarvestTile(ResourceName::Lumber, ResourceName::Sheep, ResourceName::Lumber, ResourceName::Rock),
		HarvestTile(ResourceName::Rock, ResourceName::Rock, ResourceName::Rock, ResourceName::Wheat),
		HarvestTile(ResourceName::Lumber, ResourceName::Rock, ResourceName::Lumber, ResourceName::Sheep),

		HarvestTile(ResourceName::Rock, ResourceName::Lumber, ResourceName::Rock, ResourceName::Sheep),
		HarvestTile(ResourceName::Sheep, ResourceName::Rock, ResourceName::Sheep, ResourceName::Rock),
		HarvestTile(ResourceName::Wheat, ResourceName::Rock, ResourceName::Wheat, ResourceName::Rock),
		HarvestTile(ResourceName::Sheep, ResourceName::Sheep, ResourceName::Sheep, ResourceName::Lumber),

		HarvestTile(ResourceName::Lumber, ResourceName::Sheep, ResourceName::Lumber, ResourceName::Sheep),
		HarvestTile(ResourceName::Lumber, ResourceName::Lumber, ResourceName::Lumber, ResourceName::Sheep),
		HarvestTile(ResourceName::Sheep, ResourceName::Lumber, ResourceName::Sheep, ResourceName::Wheat),
		HarvestTile(ResourceName::Lumber, ResourceName::Rock, ResourceName::Lumber, ResourceName::Rock),

		HarvestTile(ResourceName::Lumber, ResourceName::Sheep, ResourceName::Lumber, ResourceName::Wheat),
		HarvestTile(ResourceName::Wheat, ResourceName::Rock, ResourceName::Wheat, ResourceName::Rock),
		HarvestTile(ResourceName::Lumber, ResourceName::Rock, ResourceName::Lumber, ResourceName::Wheat),
		HarvestTile(ResourceName::Rock, ResourceName::Sheep, ResourceName::Lumber, ResourceName::Rock),

		//IMG-3
		HarvestTile(ResourceName::Rock, ResourceName::Rock, ResourceName::Rock, ResourceName::Sheep),
		HarvestTile(ResourceName::Lumber, ResourceName::Rock, ResourceName::Sheep, ResourceName::Lumber),
		HarvestTile(ResourceName::Wheat, ResourceName::Sheep, ResourceName::Lumber, ResourceName::Wheat),
		HarvestTile(ResourceName::Sheep, ResourceName::Wheat, ResourceName::Lumber, ResourceName::Sheep),

		HarvestTile(ResourceName::Lumber, ResourceName::Rock, ResourceName::Wheat, ResourceName::Lumber),
		HarvestTile(ResourceName::Wheat, ResourceName::Rock, ResourceName::Wheat, ResourceName::Lumber),
		HarvestTile(ResourceName::Lumber, ResourceName::Wheat, ResourceName::Lumber, ResourceName::Wheat),
		HarvestTile(ResourceName::Sheep, ResourceName::Rock, ResourceName::Wheat, ResourceName::Sheep),

		HarvestTile(ResourceName::Rock, ResourceName::Sheep, ResourceName::Rock, ResourceName::Lumber),
		HarvestTile(ResourceName::Sheep, ResourceName::Wheat, ResourceName::Sheep, ResourceName::Wheat),
		HarvestTile(ResourceName::Rock, ResourceName::Wheat, ResourceName::Sheep, ResourceName::Rock),
		HarvestTile(ResourceName::Lumber, ResourceName::Lumber, ResourceName::Lumber, ResourceName::Rock),

		HarvestTile(ResourceName::Wheat, ResourceName::Sheep, ResourceName::Wheat, ResourceName::Lumber),
		HarvestTile(ResourceName::Lumber, ResourceName::Wheat, ResourceName::Lumber, ResourceName::Sheep),
		HarvestTile(ResourceName::Wheat, ResourceName::Rock, ResourceName::Sheep, ResourceName::Wheat),
		HarvestTile(ResourceName::Lumber, ResourceName::Wheat, ResourceName::Sheep, ResourceName::Lumber),

		HarvestTile(ResourceName::Wheat, ResourceName::Sheep, ResourceName::Wheat, ResourceName::Rock),
		HarvestTile(ResourceName::Wheat, ResourceName::Lumber, ResourceName::Wheat, ResourceName::Rock),
		HarvestTile(ResourceName::Sheep, ResourceName::Rock, ResourceName::Lumber, ResourceName::Sheep),
		HarvestTile(ResourceName::Lumber, ResourceName::Rock, ResourceName::Lumber, ResourceName::Rock)
	};
}
