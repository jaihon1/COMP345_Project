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

void VGMap::init_building(int rv, int cv, int numv, int typev)
{
	(village[rv][cv]).set_num(numv);
	(village[rv][cv]).set_type(typev);
}

void VGMap::put_building_sim()
{
	for (int i = 0; i < village_row; i++)
		for (int j = 0; j < village_col; j++)
			if (i == j && i > 2)
				init_building(i, j, -1);
			else if (rand() % 8 < 1)
				init_building(i, j, 0);
			else
				init_building(i, j, 6 - i);
}

bool VGMap::validate(int type, int num, int row, int col, int state)//state 0 = face down
{
	if ((row+1>village_row) ? false : village[row+1][col].get() == type
		|| (row-1<0) ? false : village[row-1][col].get() == type
		|| (col+1>village_col) ? false : village[row][col+1].get() == type
		|| (col-1>village_col) ? false : village[row][col-1].get() == type) {
		if (state != 0) {
			if (num == row) {
				init_building(row, col, num, type);
				return 1;
			}			
		}
		else {
			init_building(row, col, state, type);
			return 1;
		}			
	}
	else {
		if (initial_res[type] == false) {
			initial_res[type] = true;
			init_building(row, col, num, type);
			return 1;
		}
	}
	return 0;			
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

VGMap::Building::Building(int xv, int yv, int numv, int typev)
{
	x = xv;
	y = yv;
	num = numv;
	type = typev;
}

VGMap::Building::Building()
{
}

VGMap::Building::~Building()
{
}

int VGMap::Building::get() const
{
	return type;
}

void VGMap::Building::set(int typev)
{
	type = typev;
}

int VGMap::Building::get_num() const
{
	return num;
}

int VGMap::Building::get_type() const
{
	return type;
}
void VGMap::Building::set_num(int numv)
{
	num = numv;
}
void VGMap::Building::set_type(int typev)
{
	type = typev;
}
/*********************Nested Building******************/