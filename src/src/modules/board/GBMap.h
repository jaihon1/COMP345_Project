#pragma once
#include<iostream> 
#include <list> 
#include "Scoring.h" 

class GBMap
{
public:
	static const int board_size = 7;
	static const int board_length = board_size * 2;
	static const int max_tile = board_size * 2 * board_size * 4;

private:
	class Tile
	{
	private:		
		int x;
		int y;
		int res;

	public:		
		Tile(int xv, int yv, int resv);
		Tile();
		~Tile();

		int get();
		void set(int resv);
	};

	class Building
	{
	private:
		int x;
		int y;
		int type;

	public:
		Building(int xv, int yv, int typev);
		~Building();

		int get();
		void set(int typev);
	};

	class Graph
	{
	private:
		// No. of vertices
		int V;     

		// Pointer to an array containing adjacency lists 
		std::list<int> *adj;

		// A function used by DFS 
		void DFSUtil(int v, bool visited[]);
	public:
		Graph(int V); 
		~Graph();

		void addEdge(int v, int w);
		void connectedComponents();
	};

	struct XY {
		int x;
		int y;
		//top left of 4
		XY(int xv, int yv) {
			x = xv * 2;
			y = yv * 2;
		}

		//single
		XY(int xv, int yv, bool v ) {
			x = xv;
			y = yv;
		}
	};

	bool map_type;//true = A
	int map_player;
	Tile map[board_length][board_length];
	int test[4];

	void init_obstacle(XY &coor);
	void init_resource(XY &coor, int res[4]);
	void init_building(XY &coor);
	void connect_resource(Tile *pos, bool dub[4], Scoring &sc, Tile *org);

public:
	const enum tile_type { black = -1, white = 0, red = 1, green = 2, yellow = 3, gray = 4, building = 5 };

	GBMap(int map_player, bool map_type);
	~GBMap();

	Graph vertices{ 196 };

	void put_resource(int xv, int yv, int res[4], Scoring &sc);
	int check_availibility(int xv, int yv);
	void put_resource_sim();

	void display_map();	
};

