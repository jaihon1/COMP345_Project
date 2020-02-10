#pragma once
#include<iostream> 
class Scoring;

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

		int get();
		void set(int typev);
	};

	Building village[village_row][village_col];
	int test;
	void init_building(int rv, int cv, int typev);

	friend int Scoring::get_score(VGMap &vil);

public:
	VGMap();
	~VGMap();

	const enum bld_type { empty = 0, red = 1, green = 2, yellow = 3, gray = 4, down = 5 };

	void put_building_sim();
	void display_village();
};

