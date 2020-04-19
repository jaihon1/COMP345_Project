#pragma once
#include "../modules/ConsoleLogger/ConsoleLogger.h"


class Observer
{
public:
	Observer();
	~Observer();

	virtual void update() = 0; 
};

