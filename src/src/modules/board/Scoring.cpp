#include "Scoring.h"
#include "VGMap.h"


Scoring::Scoring()
{
}


Scoring::~Scoring()
{
}

void Scoring::addEdge(int v, int w)
{
	vertices.addEdge(v, w);
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

void Scoring::update_help(int v, int w, int res) {
	if (vertices.is_adjacent(v, w))
		add_res(res, vertices.connected(v));
	else {		
		add_res(res, vertices.connected(v));
		add_res(res, vertices.connected(w));
	}
}

void Scoring::update_res(ptrdiff_t pos[4], int res[4])
{
	//std::cout << "Test" << vertices.connected(90) << std::endl;
	//update_help(pos[0], pos[3], res[0]);
	//update_help(pos[1], pos[2], res[1]);
	//update_help(pos[2], pos[1], res[2]);
	//update_help(pos[3], pos[0], res[3]);
	
	for (int i = 0; i < 4; i++)
	{
		if (res[i] == 0)
			continue;
		for (int j = 0; j < 4; j++)
		{
			if (res[j] == 0)
				continue;
			if (vertices.is_adjacent(pos[i], pos[j]))
				res[j] = 0;
		}
		add_res(res[i], vertices.connected(pos[i]));
	}
		
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

int Scoring::get_score(VGMap &vil)
{
	int score = 0;
	bool mul = false;
	bool complete = false;
	//vil.village[3][3].set(-1);
	//vil.village[1][1].set(-1);

	for (int i = 0; i < VGMap::village_row; i++)
	{
		mul = true;
		complete = true;
		for (int j = 0; j < VGMap::village_col; j++) {	
			if (vil.village[i][j].get() == 0)
				complete = false;
			if (vil.village[i][j].get() == -1)
				mul = false;			
		}
		if (!complete)
			continue;
		if (mul)
			score += (VGMap::village_row - i) * 2;
		else 
			score += (VGMap::village_row - i);
	}		

	for (int i = 0; i < VGMap::village_col; i++) {
		mul = true;
		complete = true;
		for (int j = 0; j < VGMap::village_row; j++) {
			if (vil.village[i][j].get() == 0)
				complete = false;
			if (vil.village[i][j].get() == -1)
				mul = false;
		}
		if (!complete)
			continue;
		if (mul)
			score += (VGMap::village_col - (2 - abs(i-2))) * 2;
		else
			score += (VGMap::village_col - (2 - abs(i - 2)));
		//std::cout << "test: " << score << std::endl;
	}
		
		

	return score;
}

int Scoring::get_res(int resv)
{
	return res_score[resv];
}

void Scoring::display_res()
{
	std::cout << "Resource: " << std::endl;
	for(int i = 1; i < 5 ; i++)
		std::cout << res_score[i] << std::endl;
	std::cout << std::endl;
}


/*********************Nested Graph******************/
Scoring::Graph::Graph(int V)
{
	this->V = V;
	adj = new std::list<int>[V];
}

Scoring::Graph::~Graph()
{
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

	DFS(v, visited, count);

	delete visited;

	return count;
}

void Scoring::Graph::DFS(int v, bool visited[], int &count)
{
	visited[v] = true;

	// Recur for all the vertices 
	// adjacent to this vertex 
	std::list<int>::iterator i;
	for (i = adj[v].begin(); i != adj[v].end(); ++i)
		if (!visited[*i])
			DFS(*i, visited, ++count);
}

// Method to print connected components in an undirected graph 
void Scoring::Graph::connectedComponents()
{
	// Mark all the vertices as not visited 
	int retval = []() -> int { return 1; }();
	VER *visited = new VER[V]();

	for (int v = 0; v<V; v++)
	{
		if (visited[v].visited == false)
		{
			// print all reachable vertices from v 			
			DFSUtil(v, visited);

			std::cout << "\n";				
		}
	}	

	delete visited;
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