#include "Scoring.h"
#include "VGMap.h"


Scoring::Scoring()
{
	//vertices.name = 'm';
}

Scoring::Scoring(const Scoring &sc):vertices(sc.vertices)
{	
	ver_lim = sc.ver_lim;
	//std::cout << vertices.name << std::endl;
	//std::cout << "Barrier 1" << std::endl;
	//Temp object get destroy by des
	//Graph test = Graph(sc.vertices);
	//Graph test = sc.vertices;
	//Graph test{ sc.vertices };
	//test.name = 'a';
	//vertices =  Graph(sc.vertices);
	//std::cout << "Barrier 2" << std::endl;
	//std::cout << vertices.name << std::endl;
	//vertices.name = 'n';	
	//std::cout << vertices.name << std::endl;	
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
	//std::cout << std::endl;
	//for (int i = 0; i < 4; i++)
	//	std::cout << "Test " << res[i] << std::endl;
	//if (pos[0] == 96) {
	//	std::cout << vertices.is_adjacent(96, 111) << std::endl;
	//	std::cout << vertices.is_connected(96, 111) << std::endl;
	//}

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

int Scoring::get_score(const VGMap &vil)
{
	int score = 0;
	bool mul = false;
	bool complete = false;

	for (int i = 0; i < VGMap::village_row; i++)
	{
		mul = true;
		complete = true;
		for (int j = 0; j < VGMap::village_col; j++) {	
			if (vil.village[i][j].get() == 0)
				complete = false;
			else
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
			//if (vil.village[i][j].get() == 0)//Wrong
			if (vil.village[j][i].get() == 0)
				complete = false;
			else
				if (vil.village[j][i].get() == -1)
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

int Scoring::get_density(const VGMap &vil)
{
	int result = 0;
	for (int i = 0; i < VGMap::village_row; i++)
	{
		for (int j = 0; j < VGMap::village_col; j++) {
			if (vil.village[i][j].get() != 0)
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

int Scoring::get_winner(const VGMap villages[4])
{
	using namespace std;
	int winner = 0;

	for (int i = 0; i < 4; i++) {
		vil_score[i][0] = get_score(villages[i]);
		vil_score[i][1] = get_density(villages[i]);
		vil_score[i][2] = rand() % 50;
		if (i == 2) {
			vil_score[2][0] = 56;
			vil_score[2][1] = 29;
			vil_score[2][2] = 47;
		}
		std::cout << "village score: " << vil_score[i][0] << std::endl;
		std::cout << "village densi: " << vil_score[i][1] << std::endl;
		std::cout << "village build: " << vil_score[i][2] << std::endl;
	}

	for (int i = 0; i < 4; i++) 
		total_score[i] = vil_score[i][0] * 100000 + vil_score[i][1] * 1000 + (100 - vil_score[i][2]) * 10 + i;
	
	insertionSort(total_score, 4);

	for (int i = 0; i < 4; i++)
		if (total_score[i]/10 == total_score[0]/10)
			cout << "The winner is player at index: " << total_score[i]%10 << endl;
	
	return winner;
}


/*********************Nested Graph******************/
Scoring::Graph::Graph(int V)
{
	std::cout << "test Graph(int V)" << "\n";
	this->V = V;
	adj = new std::list<int>[V];
}

Scoring::Graph::Graph(const Graph &gr)
{
	V = gr.V;
	adj = new std::list<int>[V];
	for (int v = 0; v < V; v++)
		adj[v] = gr.adj[v];
	//for (auto v : adj[2])
	//	std::cout << v << "\n";	
	//std::cout << "test Graph(const Graph &gr) " << name << "\n";
	//name = 'c';
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

	//name = gr.name;
	//std::cout << "test Graph::operator= \n";

	// return the existing object so we can chain this operator
	return *this;
}

Scoring::Graph::~Graph()
{
	//std::cout << "test ~Graph() " << name << "\n";
	//delete adj; wrong
	//for (int v = 0; v < V; v++)
	//	adj[v].~list();
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

	delete [] visited;

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

	for (int v = 0; v<V; v++)
	{
		if (visited[v].visited == false)
		{
			// print all reachable vertices from v 			
			DFSUtil(v, visited);

			std::cout << "\n";				
		}
	}	

	delete [] visited;
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