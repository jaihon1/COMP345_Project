#pragma once
#include<iostream> 
#include "Scoring.h" 

class GBMap
{
public:
	static const int board_size = 7;
	static const int board_length = board_size * 2;
	static const int max_tile = board_size * 2 * board_size * 2;
	const enum tile_type { obstacle = -1, white = 0, red = 1, green = 2, yellow = 3, gray = 4, building = 5 };

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
		void set(tile_type resv);
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

	void init_obstacle(XY &coor);
	void init_tile(int &xv, int &yv, int val[4]);
	bool init_obstacle(int &xv, int &yv);
	bool init_resource(int &xv, int &yv);	
	bool init_building(int &xv, int &yv);
	bool put_resource(int &xv, int &yv, int res[4]);
	void connect_resource(ptrdiff_t &index, Tile *pos, Scoring &sc);

public:
	GBMap(int map_player, bool map_type);
	~GBMap();

	void add_tile(int xv, int yv, int res[4], Scoring &sc);
	int check_availibility(int &xv, int &yv);
	void put_resource_sim();

	void display_map();	
};

