#include "ViewObserver.h"



ViewObserver::ViewObserver()
{
}

ViewObserver::ViewObserver(Scoring * sc) : sc(sc)
{
	sc->attach(this);
}


ViewObserver::~ViewObserver()
{
	sc->detach(this);
}

void ViewObserver::update()
{
	std::cout << "ViewObserver updated" << std::endl;

}
