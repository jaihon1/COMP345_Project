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
	sc->get_state(statistic);
}

void ViewObserver::display()
{
	int total_player = 4;
	for (int i = 1; i < 5; i++)
	{
		if (statistic[0][i] == 0)
			total_player--;
	}
	for (int i = 1; i < 6; i++)
	{
		if (statistic[i][0] == 0)
			continue;
		switch (i)
		{
		case 1: std::cout << "Player # " << std::endl;
			break;
		case 2: std::cout << "Village score " << std::endl;
			break;
		case 3: std::cout << "Village density " << std::endl;
			break;
		case 4: std::cout << "Avail building " << std::endl;
			break;
		case 5: std::cout << "Turn remain " << std::endl;
			break;
		default: printf("N/A");
			break;
		}
		for (int j = 1; j <= total_player; j++)
		{
			std::cout << "Player #" << i << ": " << statistic[i][j] << std::endl;
		}
		std::cout << std::endl;
	}
	std::cout << "Resource Marker " << std::endl;
	for (int i = 1; i < 5; i++)
		std::cout << "Res #" << i << ": " << statistic[6][i] << std::endl;
	std::cout << std::endl;
}