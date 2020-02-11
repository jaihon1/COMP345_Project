#include "HarvestTile.h"
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
