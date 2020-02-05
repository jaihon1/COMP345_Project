#include "HarvestTile.hpp"

HarvestTile::HarvestTile(ResourceName topRight, ResourceName topLeft, ResourceName bottomRight, ResourceName bottomLeft)
{
	//pointer for each row
	resourceArr = new ResourceName* [2];

	//pointer to an array for each element of the row index to form columns
	resourceArr[0] = new ResourceName[2];
	resourceArr[1] = new ResourceName[2];

	resourceArr[0][0] = topRight;
	resourceArr[0][1] = topLeft;
	resourceArr[1][0] = bottomRight;
	resourceArr[1][1] = bottomLeft;
}

HarvestTile::~HarvestTile()
{
	delete[] resourceArr[0];
	delete[] resourceArr[1];

	delete resourceArr;
}

void HarvestTile::RotateRight()
{
	ResourceName temp = resourceArr[0][0];

	resourceArr[0][0] = resourceArr[1][0];
	resourceArr[1][0] = resourceArr[1][1];
	resourceArr[1][1] = resourceArr[0][1];
	resourceArr[0][1] = temp;
	
}

void HarvestTile::RotateLeft()
{
	ResourceName temp = resourceArr[0][0];

	resourceArr[0][0] = resourceArr[0][1];
	resourceArr[0][1] = resourceArr[1][1];
	resourceArr[1][1] = resourceArr[1][0];
	resourceArr[1][0] = temp;

}

ResourceName HarvestTile::getResource(int row, int column)
{
	return resourceArr[row][column];
}
