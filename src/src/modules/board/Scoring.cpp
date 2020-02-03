#include "Scoring.h"



Scoring::Scoring()
{
}


Scoring::~Scoring()
{
}

void Scoring::reset_res()
{
	res_score[1] = 0;
	res_score[2] = 0;
	res_score[3] = 0;
	res_score[4] = 0;
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

int Scoring::get_score()
{
	return 0;
}

int Scoring::get_res(int resv)
{
	return res_score[resv];
}

void Scoring::add_res(int resv, int numv)
{
	res_score[resv] += numv;
}

void Scoring::display_res()
{
	std::cout << "Resource: " << std::endl;
	for(int i = 1; i < 5 ; i++)
		std::cout << res_score[i] << std::endl;
	std::cout << std::endl;
}


