#pragma once
#include "Tile.hpp"

enum class ResourceName {
	Lumber,
	Rock,
	Sheep,
	Wheat
};

class HarvestTile :
	public Tile
{
private:
	ResourceName* resourceArr;

	const int* const topLeft = new int(0);
	const int* const topRight = new int(1);
	const int* const bottomLeft = new int(2);
	const int* const bottomRight = new int(3);

public:
	HarvestTile(ResourceName topRight, ResourceName topLeft, ResourceName bottomRight, ResourceName bottomLeft);

	~HarvestTile();

	void RotateRight();
	
	void RotateLeft();

	ResourceName getResource(int row, int column);
};

