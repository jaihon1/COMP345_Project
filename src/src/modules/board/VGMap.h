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
		int type;

	public:
		Building(int xv, int yv, int typev);
		Building();
		~Building();

		int get() const;
		void set(int typev);
	};

	Building village[village_row][village_col];
	int test;
	void init_building(int rv, int cv, int typev);

	friend int Scoring::get_score(const VGMap &vil);
	friend int Scoring::get_density(const VGMap &vil);
	friend int Scoring::get_winner(const int score[4][3]);

public:
	VGMap();
	~VGMap();

	const enum bld_type { down = -1, empty = 0, up = 1 };

	void put_building_sim();
	void display_village();
};

