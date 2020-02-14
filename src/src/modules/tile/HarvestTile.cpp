#include "HarvestTile.h"

HarvestTile::HarvestTile(ResourceName topLeftRes, ResourceName topRightRes, ResourceName bottomLeftRes, ResourceName bottomRightRes)
{
	//pointer for each row
	resourceArr = new ResourceName[4]  {topLeftRes, topRightRes, bottomLeftRes, bottomRightRes};

}

HarvestTile::HarvestTile(int topLeftRes, int topRightRes, int bottomLeftRes, int bottomRightRes)
{
	//pointer for each row
	resourceArr = new ResourceName[4]{ static_cast<ResourceName>(topLeftRes), static_cast<ResourceName>(topRightRes), 
		static_cast<ResourceName>(bottomLeftRes), static_cast<ResourceName>(bottomRightRes) };

}

HarvestTile::~HarvestTile()
{
	delete[] resourceArr;

	delete resourceArr;
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
