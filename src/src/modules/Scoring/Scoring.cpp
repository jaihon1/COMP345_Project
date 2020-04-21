
#include "../tile/Resources.h"
#include "../board/GBMaps.h"
#include "Scoring.h"

Scoring::Scoring()
{
	for (int i = 1; i < 5; i++)
		statistic[i][0] = 1;
	statistic[6][0] = 1;
}

Scoring::Scoring(const Scoring &sc) :vertices(sc.vertices)
{
	ver_lim = sc.ver_lim;
}

Scoring::~Scoring()
{
}

void Scoring::addEdge(int v, int w)
{
	vertices.addEdge(v, w);
}

void Scoring::set_res(int res[4])
{
	res_score[1] = res[0];
	res_score[2] = res[1];
	res_score[3] = res[2];
	res_score[4] = res[3];
}

void Scoring::reset_res()
{
	res_score[1] = 0;
	res_score[2] = 0;
	res_score[3] = 0;
	res_score[4] = 0;
}

void Scoring::add_res(int resv, int numv)
{
	res_score[resv] += numv;
}

void Scoring::update_res(ptrdiff_t pos[4], int res[4])
{
	//std::cout << "Test" << vertices.connected(90) << std::endl;

	for (int i = 0; i < 4; i++)
	{
		if (res[i] == 0)
			continue;
		for (int j = 0; j < 4; j++)
		{
			if (res[j] == 0)
				continue;
			if (j == i)
				continue;
			//vertices.is_adjacent() wrong
			if (vertices.is_connected(pos[i], pos[j]))
				res[j] = 0;
		}
		add_res(res[i], vertices.connected(pos[i]));
	}

	//update resource marker
	for (int i = 1; i < 5; i++)
	statistic[6][i] = res_score[i];
	notify();
}

void Scoring::set_id(int index, int id)
{
	statistic[0][index] = 1;
	statistic[1][index] = id;
	notify();
}

void Scoring::set_score(int index, int score)
{
	statistic[2][index] = score;
	notify();
}

void Scoring::add_density(int index, int number)
{
	statistic[3][index] += number;
	notify();
}

void Scoring::set_avail_building(int index, int number)
{
	statistic[4][index] = number;
	notify();
}

void Scoring::connectedComponents()
{
	vertices.connectedComponents();
}

int Scoring::adjacency(int v)
{
	return vertices.adjacency(v);
}

int Scoring::connected(int v)
{
	return vertices.connected(v);
}

void Scoring::get_state()
{
	int total_player = 4;
	for (int i = 1; i < 5; i++)
	{
		if (statistic[0][i] == 0)
			total_player--;
	}
	for (int i = 1; i < 6; i++)
	{
		if (statistic[i][0] == 0)
			continue;
		switch (i)
		{
		case 1: std::cout << "Player # " << std::endl;
			break;
		case 2: std::cout << "Village score " << std::endl;
			break;
		case 3: std::cout << "Village density " << std::endl;
			break;
		case 4: std::cout << "Avail building " << std::endl;
			break;
		case 5: std::cout << "Turn remain " << std::endl;
			break;
		default: printf("N/A");
			break;
		}
		for (int j = 1; j <= total_player; j++)
		{
			std::cout << "Player #" << j << ": " << statistic[i][j] << std::endl;
		}
		std::cout << std::endl;
	}
	std::cout << "Resource Marker " << std::endl;
	for (int i = 1; i < 5; i++)
		std::cout << "Res #" << i << ": " << statistic[6][i] << std::endl;
	std::cout << std::endl;
}

int Scoring::get_state(int state[10][5])
{
	{
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 5; j++)
				state[i][j] = statistic[i][j];
		}
		return 1;
	}
	return 0;
}

int Scoring::get_lumber()
{
	return res_score[1];
}

int Scoring::get_sheep()
{
	return res_score[2];
}

int Scoring::get_wheat()
{
	return res_score[3];
}

int Scoring::get_stone()
{
	return res_score[4];
}

int Scoring::get_res(int res[4])
{
	res[0] = res_score[1];
	res[1] = res_score[2];
	res[2] = res_score[3];
	res[3] = res_score[4];
	return 0;
}

int Scoring::remove_res(int resv, int quantity)
{
	if (res_score[resv] > quantity) {
		res_score[resv] = res_score[resv] - quantity;
		statistic[6][resv] = statistic[6][resv] - quantity;
		notify();
		return quantity;
	}
	else
		return 0;
}

void Scoring::display_res()
{
	std::cout << "Resource: " << std::endl;
	std::cout << "Lumber: " << res_score[1] << std::endl;
	std::cout << "Sheep: " << res_score[2] << std::endl;
	std::cout << "Wheat: " << res_score[3] << std::endl;
	std::cout << "Rock: " << res_score[4] << std::endl;
	std::cout << std::endl;
}

int Scoring::get_score(const VGMaps &vil)
{
	int score = 0;
	bool mul = false;
	bool complete = false;

	for (int i = 0; i < village_row; i++)
	{
		mul = true;
		complete = true;
		for (int j = 0; j < village_col; j++) {
			if (vil.isEmpty(i, j))
				complete = false;
			else
				if (vil.isFlipped(i, j))
					mul = false;
		}
		if (!complete)
			continue;
		if (mul)
			score += (village_row - i) * 2;
		else
			score += (village_row - i);
	}

	for (int i = 0; i < village_col; i++) {
		mul = true;
		complete = true;
		for (int j = 0; j < village_row; j++) {
			//cout << i << "****************************" << j << endl;
			if (vil.isEmpty(j, i))
				complete = false;
			else
				if (vil.isFlipped(j, i))
					mul = false;
		}
		if (!complete)
			continue;
		if (mul)
			score += (village_col - (2 - abs(i - 2))) * 2;
		else
			score += (village_col - (2 - abs(i - 2)));
		//std::cout << "test: " << score << std::endl;
	}
	return score;
}

int Scoring::get_density(const VGMaps &vil)
{
	int result = 0;
	for (int i = 0; i < village_row; i++)
	{
		for (int j = 0; j < village_col; j++) {
			if (!vil.isEmpty(i, j))
				result++;
		}
	}

	return result;
}

void Scoring::insertionSort(int arr[], int n)
{
	int i, key, j;
	for (i = 1; i < n; i++)
	{
		key = arr[i];
		j = i - 1;

		while (j >= 0 && arr[j] < key)
		{
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = key;
	}
}

int Scoring::get_winner(const VGMaps villages[4])
{
	using namespace std;
	int winner = 0;

	for (int i = 0; i < 4; i++) {
		vil_score[i][0] = get_score(villages[i]);
		vil_score[i][1] = get_density(villages[i]);
		vil_score[i][2] = rand() % 50;
		std::cout << "village score: " << vil_score[i][0] << std::endl;
		std::cout << "village densi: " << vil_score[i][1] << std::endl;
		std::cout << "village build: " << vil_score[i][2] << std::endl;
	}

	for (int i = 0; i < 4; i++)
		total_score[i] = vil_score[i][0] * 100000 + vil_score[i][1] * 1000 + (100 - vil_score[i][2]) * 10 + i + 1;

	insertionSort(total_score, 4);

	for (int i = 0; i < 4; i++)
		if (total_score[i] / 10 == total_score[0] / 10)
			cout << "The winner is player at index: " << total_score[i] % 10 << endl;

	return winner;
}

int Scoring::get_winner(VGMaps *villages[4])
{
	using namespace std;
	int winner = 0;

	for (int i = 0; i < 4; i++) {
		vil_score[i][0] = get_score(*villages[i]);
		vil_score[i][1] = get_density(*villages[i]);
		vil_score[i][2] = rand() % 50;
		std::cout << "village score: " << vil_score[i][0] << std::endl;
		std::cout << "village densi: " << vil_score[i][1] << std::endl;
		std::cout << "village build: " << vil_score[i][2] << std::endl;
	}

	for (int i = 0; i < 4; i++)
		total_score[i] = vil_score[i][0] * 100000 + vil_score[i][1] * 1000 + (100 - vil_score[i][2]) * 10 + i + 1;

	insertionSort(total_score, 4);

	for (int i = 0; i < 4; i++)
		if (total_score[i] / 10 == total_score[0] / 10)
			cout << "The winner is player at index: " << total_score[i] % 10 << endl;

	return winner;
}

/*********************Nested Graph******************/
Scoring::Graph::Graph(int V)
{
	this->V = V;
	adj = new std::list<int>[V];
}

Scoring::Graph::Graph(const Graph &gr)
{
	V = gr.V;
	adj = new std::list<int>[V];
	for (int v = 0; v < V; v++)
		adj[v] = gr.adj[v];
}

Scoring::Graph & Scoring::Graph::operator= (const Graph &gr)
{
	// self-assignment check
	if (this == &gr)
		return *this;

	// if data exists in the current string, delete it
	if (adj) delete[] adj;

	V = gr.V;
	adj = new std::list<int>[V];
	for (int v = 0; v < V; v++)
		adj[v] = gr.adj[v];

	// return the existing object so we can chain this operator
	return *this;
}

Scoring::Graph::~Graph()
{
	if (adj) delete[] adj;
}

int Scoring::Graph::adjacency(int v)
{
	for (auto e : adj[v])
		std::cout << e << "\n";
	return adj[v].size();
}

bool Scoring::Graph::is_adjacent(int v, int w)
{
	return std::find(adj[v].begin(), adj[v].end(), w) != adj[v].end();
}

int Scoring::Graph::connected(int v)
{
	bool *visited = new bool[V];
	int count = 1;
	for (int v = 0; v < V; v++)
		visited[v] = false;

	DFS_count(v, visited, count);

	delete[] visited;

	return count;
}

bool Scoring::Graph::is_connected(int v, int w)
{
	bool *visited = new bool[V];
	bool result = false;
	for (int v = 0; v < V; v++)
		visited[v] = false;

	DFS_connect(v, visited, w, result);

	delete[] visited;

	return result;
}

void Scoring::Graph::DFS_connect(int v, bool visited[], int w, bool &result)
{
	visited[v] = true;
	if (v == w)
		result = true;
	else {
		// Recur for all the vertices 
		// adjacent to this vertex 
		std::list<int>::iterator i;
		for (i = adj[v].begin(); i != adj[v].end(); ++i)
			if (!visited[*i])
				DFS_connect(*i, visited, w, result);
	}
}

void Scoring::Graph::DFS_count(int v, bool visited[], int &count)
{
	visited[v] = true;

	// Recur for all the vertices 
	// adjacent to this vertex 
	std::list<int>::iterator i;
	for (i = adj[v].begin(); i != adj[v].end(); ++i)
		if (!visited[*i])
			DFS_count(*i, visited, ++count);
}

// Method to print connected components in an undirected graph 
void Scoring::Graph::connectedComponents()
{
	// Mark all the vertices as not visited 
	int retval = []() -> int { return 1; }();
	VER *visited = new VER[V]();

	for (int v = 0; v < V; v++)
	{
		if (visited[v].visited == false)
		{
			// print all reachable vertices from v 			
			DFSUtil(v, visited);

			std::cout << "\n";
		}
	}

	delete[] visited;
}

void Scoring::Graph::DFSUtil(int v, VER visited[])
{
	// Mark the current node as visited and print it 
	visited[v].visited = true;
	std::cout << v << " ";

	// Recur for all the vertices adjacent to this vertex 
	std::list<int>::iterator i;
	for (i = adj[v].begin(); i != adj[v].end(); ++i)
		if (!visited[*i].visited)
			DFSUtil(*i, visited);
}

// method to add an undirected edge 
void Scoring::Graph::addEdge(int v, int w)
{
	adj[v].push_back(w);
	adj[w].push_back(v);
}
/*********************Nested Graph******************/


int Scoring::map(int index, GBMaps* inHarvestBoard)
{
	int row = index / 28;
	int column = (index % 14) / 2;
	//HarvestTile temp = *getHarvestTile(row, column);

	int pos = index % 28;
	if (pos > 14)
		pos = pos % 2 + 2;
	else
		pos = pos % 2;
	//std::cout << row << " " << column << " " << index << " " <<pos << std::endl;
	//std::cin >> test;
	int result = -1;
	if (inHarvestBoard->getSquareStatus(row, column) == GBSquareStatus::HarvestTile) {
		result = static_cast<int>((inHarvestBoard->getHarvestTile(row, column))->getResource(static_cast<ResourceLocation>(pos)));
	}
	return result;
}

void Scoring::computeResources(int row, int column, HarvestTile* inHarvestTilePtr, GBMaps* inHarvestBoard) {
	int board_length = 14;
	int max_tile = 196;

	reset_res();
	int topleft = row * 28 + column * 2;
	ptrdiff_t index[4] = { topleft, topleft + 1, topleft + 14, topleft + 15 };

	for (int i = 0; i < 4; i++)
	{
		int next = index[i] - 1;
		if ((index[i] % board_length != 0) && (inHarvestBoard->getSquareStatus(next / 28, (next % 14) / 2) == GBSquareStatus::HarvestTile) && (map(index[i], inHarvestBoard) == map(next, inHarvestBoard)))
			addEdge(index[i], next);
		next = index[i] + 1;
		if (((index[i] + 1) % board_length != 0) && (inHarvestBoard->getSquareStatus(next / 28, (next % 14) / 2) == GBSquareStatus::HarvestTile) && (map(index[i], inHarvestBoard) == map(next, inHarvestBoard)))
			addEdge(index[i], next);
		next = index[i] - board_length;
		if ((index[i] >= board_length) && (inHarvestBoard->getSquareStatus(next / 28, (next % 14) / 2) == GBSquareStatus::HarvestTile) && (map(index[i], inHarvestBoard) == map(next, inHarvestBoard)))
			addEdge(index[i], next);
		next = index[i] + board_length;
		if ((index[i] < max_tile - board_length) && (inHarvestBoard->getSquareStatus(next / 28, (next % 14) / 2) == GBSquareStatus::HarvestTile) && (map(index[i], inHarvestBoard) == map(next, inHarvestBoard)))
			addEdge(index[i], next);
	}
	int res[4] = {
		static_cast<int>((*inHarvestTilePtr).getResource(ResourceLocation::topLeft)),
		static_cast<int>((*inHarvestTilePtr).getResource(ResourceLocation::topRight)),
		static_cast<int>((*inHarvestTilePtr).getResource(ResourceLocation::bottomLeft)),
		static_cast<int>((*inHarvestTilePtr).getResource(ResourceLocation::bottomRight)) };
	update_res(index, res);
}