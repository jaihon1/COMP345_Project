#include "ViewObserver.h"



ViewObserver::ViewObserver()
{
}

ViewObserver::ViewObserver(Scoring * sc) : sc(sc)
{
	sc->attach(this);
	console.Create("ViewObserver");
	console.cprintf(CConsoleLoggerEx::COLOR_WHITE | CConsoleLoggerEx::COLOR_BACKGROUND_BLACK, "ViewObserver Start\n\n");
}


ViewObserver::~ViewObserver()
{
	sc->detach(this);
}

void ViewObserver::update()
{
	std::cout << "ViewObserver updated" << std::endl;
	sc->get_state(statistic);
	console << "a" << "b" << 3 << "\n";
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
		case 1: console << "Player # " << "\n";
			break;
		case 2: console << "Village score " << "\n";
			break;
		case 3: console << "Village density " << "\n";
			break;
		case 4: console << "Avail building " << "\n";
			break;
		case 5: console << "Turn remain " << "\n";
			break;
		default: printf("N/A");
			break;
		}
		for (int j = 1; j <= total_player; j++)
		{
			console << "Player #" << j << ": " << statistic[i][j] << "\n";
		}
		console << "\n";
	}
	console << "Resource Marker " << "\n";
	for (int i = 1; i < 5; i++)
		console << "Res #" << i << ": " << statistic[6][i] << "\n";
	console << "\n";
}