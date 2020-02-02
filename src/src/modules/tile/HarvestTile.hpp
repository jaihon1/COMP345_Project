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
	void Rotate(int count);
	ResourceName getResource(int row, int column);
};

