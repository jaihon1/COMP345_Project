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
		void DFS(int v, bool visited[], int &count);// A function used by DFS 

	public:
		Graph(int V);
		~Graph();

		void addEdge(int v, int w);		
		int adjacency(int v);
		bool is_adjacent(int v, int w);
		int connected(int v);
		void connectedComponents();
	};

	Graph vertices{ 196 };
	//Lumber = 1, Sheep = 2, Wheat = 3,	Rock = 4
	int res_score[5] = { 0 , 0, 0, 0, 0 };//1st field for buildings leftover	
	int player_score[5] = { 0 , 0, 0, 0, 0 };//1st field for buildings leftover
	int player_density[5] = { 0 , 0, 0, 0, 0 };//1st field for buildings leftover

	void add_res(int resv, int numv);
	void update_help(int v, int w, int res);
	
	
	//friend class GBMap;
	//friend void GBMap::add_tile(int xv, int yv, int res[4], Scoring &sc);
	//friend void Test::sum();
public:
	Scoring();
	~Scoring();		
	
	void connectedComponents();
	int adjacency(int v);
	int connected(int v);
	void reset_res();
	void addEdge(int v, int w);	
	void update_res(ptrdiff_t pos[4], int res[4]);

	int get_lumber();
	int get_sheep();
	int get_wheat();
	int get_stone();
	int get_res(int resv);
	void display_res();

	int get_score(const VGMap &vil);//const VGMap &vil
	int get_density(const VGMap &vil);//const VGMap &vil
	int get_winner(const int score[4][3]);
};

