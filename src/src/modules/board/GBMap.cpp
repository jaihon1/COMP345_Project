#include "GBMap.h"



GBMap::GBMap(int map_player, bool map_type)
{
	srand(0);
	
	for (int i = 0; i < board_length; i++)
		for (int j = 0; j < board_length; j++)
			map[i][j] = Tile(i, j, 0);

	/*init_obstacle(0, 0);
	init_obstacle(0, board_length-1);
	init_obstacle(board_length - 1, 0);
	init_obstacle(board_length - 1, board_length - 1);*/

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

void GBMap::connect_resource(Tile *pos, bool dub[4], Scoring &sc, Tile *org)
{
	if (((*pos).get() == (*(pos+1)).get()) && (sc.get_res((*pos).get() > 0)))
	{
		ptrdiff_t index = pos - org;
		vertices.addEdge(index, index + 1);
		if (dub[0])
			sc.add_res((*pos).get(), -1);
	}
	if (((*pos).get() == (*(pos-1)).get()) && (sc.get_res((*pos).get() > 0)))
	{
		ptrdiff_t index = pos - org;
		vertices.addEdge(index, index - 1);
		if (dub[1])
			sc.add_res((*pos).get(), -1);
	}
	if (((*pos).get() == (*(pos + board_length)).get()) && (sc.get_res((*pos).get() > 0)))
	{
		ptrdiff_t index = pos - org;
		vertices.addEdge(index, (index + board_length));
		if (dub[2])
			sc.add_res((*pos).get(), -1);
	}
	if (((*pos).get() == (*(pos - board_length)).get()) && (sc.get_res((*pos).get() > 0)))
	{
		ptrdiff_t index = pos - org;
		vertices.addEdge(index, (index - board_length));
		if (dub[3])
			sc.add_res((*pos).get(), -1);
	}
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

void GBMap::put_resource(int xv, int yv, int res[4], Scoring &sc)
{
	XY coor{ xv, yv };
	Tile *pos[4] = { &map[coor.x][coor.y],&map[coor.x+1][coor.y],&map[coor.x][coor.y+1],&map[coor.x+1][coor.y+1] };
	bool dub[4][4]{ { false, false, true, true },{ true, false, false, true },
					{ false, true, true, false },{ true, true, false, false } };
	Tile *ptr1 = &map[coor.x+1][coor.y];
	Tile *ptr2 = &map[coor.x][coor.y];
	ptrdiff_t index = pos[0] - &map[0][0];
	std::cout << "result: " << index << std::endl;
	
	if (check_availibility(xv, yv)==0) {
		init_resource(coor, res);
		for (int i = 0; i < 4; i++)
			sc.add_res(res[i], 1);

		for (int i = 0; i < 4; i++)
			connect_resource(pos[i], dub[i], sc, &map[0][0]);
	}

	/*resource calculation*/
	std::cout << "Following are connected components \n" << std::endl;
	vertices.connectedComponents();
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

/*********************Nested Graph******************/
GBMap::Graph::Graph(int V)
{
	this->V = V;
	adj = new std::list<int>[V];
}

GBMap::Graph::~Graph()
{
}

// Method to print connected components in an 
// undirected graph 
void GBMap::Graph::connectedComponents()
{
	// Mark all the vertices as not visited 
	bool *visited = new bool[V];
	for (int v = 0; v < V; v++)
		visited[v] = false;

	for (int v = 0; v<V; v++)
	{
		if (visited[v] == false)
		{
			// print all reachable vertices 
			// from v 
			DFSUtil(v, visited);

			std::cout << "\n";
		}
	}
}

void GBMap::Graph::DFSUtil(int v, bool visited[])
{
	// Mark the current node as visited and print it 
	visited[v] = true;
	std::cout << v << " ";

	// Recur for all the vertices 
	// adjacent to this vertex 
	std::list<int>::iterator i;
	for (i = adj[v].begin(); i != adj[v].end(); ++i)
		if (!visited[*i])
			DFSUtil(*i, visited);
}

// method to add an undirected edge 
void GBMap::Graph::addEdge(int v, int w)
{
	adj[v].push_back(w);
	adj[w].push_back(v);
}
/*********************Nested Graph******************/