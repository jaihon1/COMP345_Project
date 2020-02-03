#pragma once
#include<iostream> 

class Scoring
{
private:
	int res_score[5] = { 0 , 0, 0, 0, 0 };//1st field for building

	void reset_res();

public:
	Scoring();
	~Scoring();	

	int get_lumber();
	int get_sheep();
	int get_wheat();
	int get_stone();
	int get_score();
	int get_res(int resv);
	void add_res(int resv, int numv);
	void display_res();
};

