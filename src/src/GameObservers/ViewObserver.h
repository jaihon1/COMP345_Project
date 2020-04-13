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

private:
	Scoring* sc;
};

