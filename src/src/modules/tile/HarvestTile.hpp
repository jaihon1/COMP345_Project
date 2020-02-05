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
	ResourceName** resourceArr;

public:
	HarvestTile(ResourceName topRight, ResourceName topLeft, ResourceName bottomRight, ResourceName bottomLeft);

	~HarvestTile();

	void RotateRight();
	
	void RotateLeft();

	ResourceName getResource(int row, int column);
};

