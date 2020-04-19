#pragma once
#include<iostream> 
#include "Scoring.h" 

class VGMap
{
public:
	static const int village_row = 6;
	static const int village_col = 5;
	static const int max_tile = village_row * village_col;

private:
	class Building
	{
	private:
		int x;
		int y;
		int num;
		int type;

	public:
		Building(int xv, int yv, int typev);
		Building(int xv, int yv, int numv, int typev);
		Building();
		~Building();

		int get() const;
		void set(int typev);
		int get_num() const;
		int get_type() const;
		void set_num(int numv);
		void set_type(int typev);
	};

	Building village[village_row][village_col];
	bool initial_res[4];//0 red, 1 green, 2 yellow ,3 gray
	int test;
	void init_building(int rv, int cv, int typev);
	void init_building(int rv, int cv, int numv, int typev);
	bool validate(int color, int num, int row, int col, int state);

	friend int Scoring::get_score(const VGMap &vil);
	friend int Scoring::get_density(const VGMap &vil);
	friend int Scoring::get_winner(const VGMap villages[4]);

public:
	VGMap();
	~VGMap();

	const enum bld_type { down = -1, empty = 0, up = 1 };

	void put_building_sim();
	void display_village();
};

