#include "HarvestTile.h"
#include "Dictionary.h"

HarvestTile::HarvestTile(ResourceName topLeftRes, ResourceName topRightRes, ResourceName bottomLeftRes, ResourceName bottomRightRes)
{
	//pointer for each row
	resourceArr = new ResourceName[4]  {topLeftRes, topRightRes, bottomLeftRes, bottomRightRes};

}

HarvestTile::HarvestTile() {
    resourceArr = new ResourceName[4];
}

HarvestTile::~HarvestTile() {
	delete[] resourceArr;
    resourceArr = nullptr;
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
