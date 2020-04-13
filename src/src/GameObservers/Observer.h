#pragma once

class Observer
{
public:
	virtual ~Observer() = 0;

	virtual void update() = 0;

protected:
	Observer();
};