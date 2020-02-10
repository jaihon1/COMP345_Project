#pragma once
#include<iostream> 
#include <list> 
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
	int res_score[5] = { 0 , 0, 0, 0, 0 };//1st field for building

	void addEdge(int v, int w);
	void reset_res();
	void add_res(int resv, int numv);
	void update_help(int v, int w, int res);
	void update_res(int pos[4], int res[4]);
	
	friend class GBMap;

public:
	Scoring();
	~Scoring();		
	
	void connectedComponents();
	int adjacency(int v);
	int connected(int v);

	int get_lumber();
	int get_sheep();
	int get_wheat();
	int get_stone();
	int get_score(VGMap &vil);
	int get_res(int resv);
	void display_res();
};

