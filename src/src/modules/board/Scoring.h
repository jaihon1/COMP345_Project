#pragma once
#include<iostream> 
#include <list> 
//#include "GBMap.h"
//#include "Test.h"
class VGMap;


class Scoring
{
private:
	class Graph
	{
	private:
		struct VER
		{
			bool visited;
			int adj;

			VER(){
				visited = false;
				adj = 0;
			}
		};
				
		int V; // No. of vertices		
		std::list<int> *adj; // Pointer to an array containing adjacency lists 		

		void DFSUtil(int v, VER visited[]);// A function used by DFS 
		void DFS_count(int v, bool visited[], int &count);// A function used by DFS 
		void DFS_connect(int v, bool visited[], int w, bool &result);// A function used by is_connected 

	public:
		Graph(int V);
		Graph(const Graph &gr);
		Graph& operator= (const Graph &gr);
		~Graph();

		//char name;

		void addEdge(int v, int w);		
		int adjacency(int v);
		bool is_adjacent(int v, int w);
		int connected(int v);
		bool is_connected(int v, int w);
		void connectedComponents();
	};

	int ver_lim = 196;
	Graph vertices{ ver_lim };
	
	int res_score[5] = { 0 , 0, 0, 0, 0 };//Lumber = 1, Sheep = 2, Wheat = 3, Rock = 4; 0 for buildings leftover	
	int vil_score[4][3];//1st village score 2nd village density 3rd village build
	int total_score[4];

	void add_res(int resv, int numv);
	void update_help(int v, int w, int res);
	void insertionSort(int arr[], int n);
	
	//friend class GBMap;
	//friend void GBMap::add_tile(int xv, int yv, int res[4], Scoring &sc);
	//friend void Test::sum();
public:
	Scoring();
	Scoring(const Scoring &sc);
	~Scoring();		
	
	void connectedComponents();
	int adjacency(int v);
	int connected(int v);	
	void addEdge(int v, int w);	
	void reset_res();
	void set_res(int res[4]);
	void update_res(ptrdiff_t pos[4], int res[4]);

	int get_lumber();
	int get_sheep();
	int get_wheat();
	int get_stone();
	int get_res(int res[4]);
	int remove_res(int resv, int quantity);
	void display_res();

	int get_score(const VGMap &vil);
	int get_density(const VGMap &vil);
	int get_building(const VGMap &vil);
	int get_winner(const VGMap villages[4]);
};
