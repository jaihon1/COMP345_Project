#include "Subject.h"

Subject::Subject() : observers(new vector<Observer*>) { }

Subject::~Subject()
{

	observers->clear(); 

	delete observers;
}

void Subject::attach(Observer* o)
{
	observers->push_back(o);
}

void Subject::detach(Observer* o)
{

	if(find(observers->begin(), observers->end(), o) != observers->end())
		observers->erase(find(observers->begin(), observers->end(), o));
}

void Subject::notify()
{
	//notify all observers attached to this subject!
	for (Observer* const& o : *observers)
	{
		o->update(); //calls display
	}
}

