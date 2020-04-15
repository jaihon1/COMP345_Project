#pragma once
#include "Observer.h"
#include "../modules/Scoring/Scoring.h"

class GameObservers : public Observer
{
public:
	GameObservers();
	GameObservers(Scoring* sc);
	~GameObservers();

	void update() override;
	void display();

private:
	Scoring* sc;
	int statistic[10][5] = { 0 };
};

