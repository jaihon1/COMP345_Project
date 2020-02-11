#pragma once
#include "Tile.h"
#include "Dictionary.h"


class HarvestTile :
	public Tile
{
private:
	ResourceName* resourceArr;

public:
	//parameters are the resources intended for the various locations on the tile
	HarvestTile(ResourceName topRightRes, ResourceName topLeftRes, ResourceName bottomRightRes, ResourceName bottomLeftRes);
    HarvestTile(const HarvestTile &harvestTile);
    HarvestTile();

	~HarvestTile();

	void RotateRight();
	
	void RotateLeft();

	ResourceName getResource(ResourceLocation inLocation);
};

