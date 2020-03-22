#include "GBMap.h"

//current system use row(x) and column(y)

GBMap::GBMap(int map_player, bool map_type, Scoring &sc)
{
	srand(1);
	no_tile = 0;
	for (int i = 0; i < board_length; i++)
		for (int j = 0; j < board_length; j++)
			map[i][j] = Tile(i, j, 0);

	XY obstacle_coor[4] = { { 0, 0 }, { 0, 6 }, { 6, 0 }, { 6, 6 } };//or XY(0,0), ...
	for (int i = 0; i < 4; i++)
		init_obstacle(obstacle_coor[i]);

	if (map_player == 4)	{
		std::cout << "full board" << std::endl;
	}
	else if (map_player == 3)	{
		for (int i = 1; i < board_size-1; i++)
		{
			init_obstacle(XY{ 0, i });
			init_obstacle(XY{ board_size - 1, i });
		}
	}
	else if (map_player == 2) {
		for (int i = 1; i < board_size -1; i++)
		{
			init_obstacle(XY{ 0, i });
			init_obstacle(XY{ board_size - 1, i });
			init_obstacle(XY{ i, 0 });
			init_obstacle(XY{ i, board_size - 1 });
		}
	}
	else {
		std::cout << "wrong" << std::endl;
	}

	if (map_type == true)
	{
		int init_res_coor[4][2] = { { 1, 1 },{ 1, 5 },{ 5, 1 },{ 5, 5 } };//int res_temp[] = { 1, 2, 3, 4 };
		for (int i = 0; i < 4; i++) {
			int temp[4] = { rand() % 4 + 1, rand() % 4 + 1, rand() % 4 + 1, rand() % 4 + 1 };
			add_tile(init_res_coor[i][0], init_res_coor[i][1], temp, sc);
		}			
	}
	else
	{
		int settlement_coor[8][2] = {	{ 1,1 },{ 1,3 },{ 1,5 },{ 3,1 },{ 3,5 },{ 5,1 },{ 5,3 },{ 5,5 } };
		int building_coor[13][2] = {	{ 0,2 },{ 0,4 },{ 2,0 },{ 2,2 },{ 2,4 },{ 2,6 },{ 3,3 },
										{ 4,0 },{ 4,2 },{ 4,4 },{ 4,6 },{ 6,2 },{ 6,4 } };
		for (int i = 0; i < 4; i++)
		{
			int temp = rand() % 8;
			if (!init_obstacle(settlement_coor[temp][0], settlement_coor[temp][1]))
				i--;
		}			
		for (int i = 0; i < 8; i++)
			init_resource(settlement_coor[i][0], settlement_coor[i][1]);		
		for (int i = 0; i < 13; i++)
				init_building(building_coor[i][0], building_coor[i][1]);
	}
}


GBMap::~GBMap()
{
}

void GBMap::init_obstacle(XY &coor)
{
	no_tile++;
	(map[coor.x][coor.y]).set(tile_type::obstacle);
	(map[coor.x][coor.y + 1]).set(tile_type::obstacle);
	(map[coor.x + 1][coor.y]).set(tile_type::obstacle);
	(map[coor.x + 1][coor.y + 1]).set(tile_type::obstacle);
}

void GBMap::init_tile(int &xv, int &yv, int val[4])
{
	no_tile++;
	XY coor{ xv, yv };
	(map[coor.x][coor.y]).set(static_cast<tile_type>(val[0]));
	(map[coor.x][coor.y + 1]).set(static_cast<tile_type>(val[1]));
	(map[coor.x + 1][coor.y]).set(static_cast<tile_type>(val[2]));
	(map[coor.x + 1][coor.y + 1]).set(static_cast<tile_type>(val[3]));
}

bool GBMap::init_obstacle(int &xv, int &yv)
{
	if (check_availibility(xv, yv) == 0)
	{
		int temp[4] = { -1, -1, -1, -1 };
		init_tile(xv, yv, temp);
		return true;
	}
	return false;
}

bool GBMap::init_resource(int &xv, int &yv)
{
	if (check_availibility(xv, yv) == 0)
	{
		int temp[4] = { rand() % 4 + 1, rand() % 4 + 1, rand() % 4 + 1, rand() % 4 + 1 };
		init_tile(xv, yv, temp);
		return true;
	}
	return false;
}

bool GBMap::init_building(int &xv, int &yv)
{
	if (check_availibility(xv, yv) == 0)
	{
		int temp[4] = { 5, 5, 5, 5 };
		init_tile(xv, yv, temp);
		return true;
	}
	return false;
}

bool GBMap::put_resource(int &xv, int &yv, int res[4])
{
	if (check_availibility(xv, yv) == 0)
	{
		init_tile(xv, yv, res);
		return true;
	}
	return false;
}

void GBMap::connect_resource(ptrdiff_t &index, Tile *pos, Scoring &sc)
{
	//check array out of bound; adjacent element; duplicate	

	if ( (index%board_length!=0) && ((*pos).get() == (*(pos-1)).get()) )
		sc.addEdge(index, index - 1);
	if ( ((index+1)%board_length!=0) && ((*pos).get() == (*(pos+1)).get()) )
		sc.addEdge(index, index + 1);
	if ( (index>=board_length) && ((*pos).get() == (*(pos - board_length)).get()) )
		sc.addEdge(index, (index - board_length));
	if ( (index< max_tile-board_length) && ((*pos).get() == (*(pos + board_length)).get()) )
		sc.addEdge(index, (index + board_length));
}

void GBMap::add_tile(int xv, int yv, int res[4], Scoring &sc)
{
	//prevent circular dependency slit into composite object with friend part independent
	//int res_temp[5]{};//int res_temp[5] random number
	
	sc.reset_res();
	XY coor{ xv, yv };
	Tile *pos[4] = { &map[coor.x][coor.y],&map[coor.x][coor.y+1],&map[coor.x+1][coor.y],&map[coor.x+1][coor.y+1] };
	Tile *org = &map[0][0];
	ptrdiff_t index[4] = { pos[0] - org, pos[1] - org, pos[2] - org, pos[3] - org };	
	
	if (put_resource(xv, yv, res))
		for (int i = 0; i < 4; i++)
			connect_resource(index[i], pos[i], sc);
	sc.update_res(index, res);
}

int GBMap::check_availibility(int &xv, int &yv)
{
	XY coor{ xv, yv };
	int temp = (map[coor.x][coor.y]).get();
	if (temp == 5)
		return 1;
	else if (temp == 0)
		return 0;
	else
		return -1;
}

int GBMap::get_no_tile()
{
	return no_tile;
}

bool GBMap::end_game()
{
	return (max_tile-no_tile==1);
}

void GBMap::put_resource_sim()
{
	for (int i = 0; i < board_size; i++)
		for (int j = 0; j < board_size; j++)
		{
			if (check_availibility(i, j)==0) {
				int res_temp[] = { rand() % 4 + 1, rand() % 4 + 1, rand() % 4 + 1, rand() % 4 + 1 };
				put_resource(i, j, res_temp);
			}			
		}	
}

void GBMap::put_resource_sim(Scoring &sc)
{
	for (int i = 0; i < board_size-1; i++)
		for (int j = 0; j < board_size; j++)
		{
			if (check_availibility(i, j) == 0) {
				int res_temp[] = { rand() % 4 + 1, rand() % 4 + 1, rand() % 4 + 1, rand() % 4 + 1 };
				add_tile(i, j, res_temp, sc);				
			}
		}
	//sc.display_res();//must pass by ref
}

void GBMap::display_map()
{
	std::cout << std::endl;
	for (int i = 0; i < board_length; i++) {
		std::cout << " ";
		for (int j = 0; j < board_length; j++)
			std::cout << (map[i][j]).get() << "\t";// if use x and y swap i and j
		std::cout << std::endl << std::endl;
	}
		
}


/*********************Nested Tile******************/
GBMap::Tile::Tile(int xv, int yv, int resv)
{
	x = xv;
	y = yv;
	res = resv;
}

GBMap::Tile::Tile()
{
}

GBMap::Tile::~Tile()
{
}

int GBMap::Tile::get()
{
	return res;
}

void GBMap::Tile::set(tile_type resv)
{
	res = resv;
}
/*********************Nested Tile******************/