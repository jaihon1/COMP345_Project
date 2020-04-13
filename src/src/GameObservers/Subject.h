#pragma once
#include <vector>
#include "Observer.h"

using std::vector;

class Subject
{
public:
	Subject();
	virtual ~Subject() = 0;

	virtual void attach(Observer* o);
	virtual void detach(Observer* o);
	virtual void notify();

protected:
	vector<Observer*>* observers;
};