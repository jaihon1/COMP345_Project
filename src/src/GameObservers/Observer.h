#pragma once
#include "../modules/ConsoleLogger/ConsoleLogger.h"

class Observer
{
public:
	virtual ~Observer() = 0;

	virtual void update() = 0;

protected:
	Observer();
};
