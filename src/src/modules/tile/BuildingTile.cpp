#include "BuildingTile.hpp"

//randomized
// int random = rand() % 6 + 1; //generate a random number from 1 to 6 



BuildingTile::BuildingTile()
{
	//?? 
}


BuildingTile::BuildingTile(BuildingColorType t, WhichSide s, int n)
{
	this.getBuildingColorType() = t;
	this.getSide() = s;
	int random = rand() % 6 + 1; //generate a random number from 1 to 6 
	n = random;
	this.getBuildingNum() = n;
}


BuildingTile::~BuildingTile()
{
	delete this.getBuildingColorType();
	delete this.getSide();
	delete this.this.getBuildingNum();
}


//someone check this... 
void BuildingTile::Flip()
{
	if (this.getSide() == WhichSide::"Normal") 
	{
		this->getBuildingNum = -1; 
	}
	//cannot flip back 
	
}
