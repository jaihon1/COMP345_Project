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

public:
	enum ResourceLocation{topLeft = 0, topRight = 1, bottomLeft = 2, bottomRight = 3};

	//parameters are the resources intended for the various locations on the tile
	HarvestTile(ResourceName topRightRes, ResourceName topLeftRes, ResourceName bottomRightRes, ResourceName bottomLeftRes);

	~HarvestTile();

	void RotateRight();
	
	void RotateLeft();

	ResourceName getResource(ResourceLocation inLocation);
};

