#include "GBMap.h"



GBMap::GBMap(int map_player, bool map_type)
{
	srand(0);
	
	for (int i = 0; i < board_length; i++)
		for (int j = 0; j < board_length; j++)
			map[i][j] = Tile(i, j, 0);

	//init_obstacle(0, 0);
	//init_obstacle(0, board_length-1);
	//init_obstacle(board_length - 1, 0);
	//init_obstacle(board_length - 1, board_length - 1);

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
		XY init_resource_coor[4] = { { 1, 1 },{ 1, 5 },{ 5, 1 },{ 5, 5 } };
		int res_temp[] = { 1, 2, 3, 4 };
		for (int i = 0; i < 4; i++)
			init_resource(init_resource_coor[i], res_temp);
	}
	else
	{
		XY settlement_coor[8] = {	{ 1,1 },{ 1,3 },{ 1,5 },{ 3,1 },{ 3,5 },{ 5,1 },{ 5,3 },{ 5,5 } };
		for (int i = 0; i < 8; i++)
			init_obstacle(settlement_coor[i]);
		XY building_coor[13] = {	{ 0,2 },{ 0,4 },{ 2,0 },{ 2,2 },{ 2,4 },{ 2,6 },{ 3,3 },
									{ 4,0 },{ 4,2 },{ 4,4 },{ 4,6 },{ 0,2 },{ 0,4 } };
		for (int i = 0; i < 13; i++)
			init_building(building_coor[i]);

	}
}


GBMap::~GBMap()
{
}

void GBMap::init_obstacle(XY &coor)
{
	(map[coor.x][coor.y]).set(tile_type::black);
	(map[coor.x + 1][coor.y]).set(tile_type::black);
	(map[coor.x][coor.y + 1]).set(tile_type::black);
	(map[coor.x + 1][coor.y + 1]).set(tile_type::black);
}

void GBMap::init_resource(XY &coor, int res[4])
{
	(map[coor.x][coor.y]).set(res[0]);
	(map[coor.x + 1][coor.y]).set(res[1]);
	(map[coor.x][coor.y + 1]).set(res[2]);
	(map[coor.x + 1][coor.y + 1]).set(res[3]);
}

void GBMap::init_building(XY &coor)
{
	(map[coor.x][coor.y]).set(5);
	(map[coor.x + 1][coor.y]).set(5);
	(map[coor.x][coor.y + 1]).set(5);
	(map[coor.x + 1][coor.y + 1]).set(5);
}

void GBMap::connect_resource(Tile *pos, Scoring &sc)
{
	//check array out of bound; adjacent element; duplicate	
	Tile *org = &map[0][0];
	ptrdiff_t index = pos - org;

	if ( (index%board_length!=0) && ((*pos).get() == (*(pos-1)).get()) )
		sc.addEdge(index, index - 1);
	if ( ((index+1)%board_length!=0) && ((*pos).get() == (*(pos+1)).get()) )
		sc.addEdge(index, index + 1);
	if ( (index>=board_length) && ((*pos).get() == (*(pos - board_length)).get()) )
		sc.addEdge(index, (index - board_length));
	if ( (index< max_tile-board_length) && ((*pos).get() == (*(pos + board_length)).get()) )
		sc.addEdge(index, (index + board_length));
}

void GBMap::put_resource(int xv, int yv, int res[4], Scoring &sc)
{
	sc.reset_res();
	XY coor{ xv, yv };
	Tile *pos[4] = { &map[coor.x][coor.y],&map[coor.x+1][coor.y],&map[coor.x][coor.y+1],&map[coor.x+1][coor.y+1] };
	bool dub[4][4]{ { false, false, true, true },{ true, false, false, true },
					{ false, true, true, false },{ true, true, false, false } };//left, top, right, bot
	Tile *ptr = &map[0][0];
	ptrdiff_t index[4] = { pos[0] - ptr, pos[1] - ptr, pos[2] - ptr, pos[3] - ptr };
	int res_temp[5]{};//int res_temp[5] random number
	
	if (check_availibility(xv, yv)==0) {
		init_resource(coor, res);
		for (int i = 0; i < 4; i++)
			res_temp[res[i]]++;
		for (int i = 0; i < 4; i++)
			connect_resource(pos[i], sc);
	}
	sc.update_res(index, res);
}

int GBMap::check_availibility(int xv, int yv)
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

void GBMap::put_resource_sim()
{
	for (int i = 0; i < board_size; i++)
		for (int j = 0; j < board_size; j++)
		{
			if (check_availibility(i, j)==0) {
				int res_temp[] = { rand() % 4 + 1, rand() % 4 + 1, rand() % 4 + 1, rand() % 4 + 1 };
				init_resource(XY{ i, j }, res_temp);
			}			
		}	
}

void GBMap::display_map()
{
	std::cout << std::endl;
	for (int i = 0; i < board_length; i++) {
		std::cout << " ";
		for (int j = 0; j < board_length; j++)
			std::cout << (map[j][i]).get() << "\t";// swap as j is row - Ox 
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

void GBMap::Tile::set(int resv)
{
	res = resv;
}
/*********************Nested Tile******************/