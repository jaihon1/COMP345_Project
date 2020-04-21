#pragma once
#include "Observer.h"
#include "../modules/Scoring/Scoring.h"

class ViewObserver : public Observer
{
public:
	ViewObserver();
	ViewObserver(Scoring* sc);
	~ViewObserver();

	void update() override;
	void display();

private:
	Scoring* sc;
//	CConsoleLoggerEx console;
	int statistic[10][5] = { 0 };
};

