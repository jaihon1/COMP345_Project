#include "VGMap.h"



VGMap::VGMap()
{
	srand(0);

	for (int i = 0; i < village_row; i++)
		for (int j = 0; j < village_col; j++)
			village[i][j] = Building(i, j, 0);
}

VGMap::~VGMap()
{
}

void VGMap::init_building(int rv, int cv, int typev)
{
	(village[rv][cv]).set(typev);
}

void VGMap::put_building_sim()
{
	for (int i = 0; i < village_row; i++)
		for (int j = 0; j < village_col; j++)
			init_building(i, j, 6 - i);
}

void VGMap::display_village()
{
	std::cout << std::endl;
	for (int i = 0; i < village_row; i++) {
		std::cout << " ";
		for (int j = 0; j < village_col; j++)
			std::cout << (village[i][j]).get() << "\t";
		std::cout << std::endl << std::endl;
	}
}


/*********************Nested Building******************/
VGMap::Building::Building(int xv, int yv, int typev)
{
	x = xv;
	y = yv;
	type = typev;
}

VGMap::Building::Building()
{
}

VGMap::Building::~Building()
{
}

int VGMap::Building::get()
{
	return type;
}

void VGMap::Building::set(int typev)
{
	type = typev;
}
/*********************Nested Building******************/