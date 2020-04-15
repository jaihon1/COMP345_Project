#include "GameObservers.h"



GameObservers::GameObservers()
{
}

GameObservers::GameObservers(Scoring * sc) : sc(sc)
{
	sc->attach(this);
}


GameObservers::~GameObservers()
{
	sc->detach(this);
}

void GameObservers::update()
{
	std::cout << "GameObservers updated" << std::endl;

}