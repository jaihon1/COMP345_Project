#include "ViewObserver.h"

#include <iostream>

ViewObserver::ViewObserver()
{
}

ViewObserver::ViewObserver(Scoring * sc) : sc(sc)
{
	sc->attach(this);
//	console.Create("ViewObserver");
//	console.cprintf(CConsoleLoggerEx::COLOR_WHITE | CConsoleLoggerEx::COLOR_BACKGROUND_BLACK, "ViewObserver Start\n\n");
}

ViewObserver::~ViewObserver()
{
	sc->detach(this);
}

void ViewObserver::update()
{
	std::cout << "ViewObserver updated" << std::endl;
	sc->get_state(statistic);
	display();
//	console << "a" << "bc \n";
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
            std::cout << "Player #" << j << ": " << statistic[i][j] << std::endl;
        }
        std::cout << std::endl;
    }
    std::cout << "Resource Marker " << std::endl;
    for (int i = 1; i < 5; i++)
        std::cout << "Res #" << i << ": " << statistic[6][i] << std::endl;
    std::cout << std::endl;
}

//void ViewObserver::display()
//{
//	int total_player = 4;
//	for (int i = 1; i < 5; i++)
//	{
//		if (statistic[0][i] == 0)
//			total_player--;
//	}
//	for (int i = 1; i < 6; i++)
//	{
//		if (statistic[i][0] == 0)
//			continue;
//		switch (i)
//		{
//		case 1: console.cout("Player # \n");
//			break;
//		case 2: console.cout("Village score \n");
//			break;
//		case 3: console.cout("Village density \n");
//			break;
//		case 4: console.cout("Avail building \n");
//			break;
//		case 5: console.cout("Turn remain \n");
//			break;
//		default: printf("N/A");
//			break;
//		}
//		for (int j = 1; j <= total_player; j++)
//		{
//			console.cout("Player #%d: %d \n", j, statistic[i][j]);
//		}
//		console.cout("\n");
//	}
//	console.cout("Resource Marker \n");
//	for (int i = 1; i < 5; i++)
//		console.cout("Res #%d: %d \n", i, statistic[6][i]);
//	console.cout("\n");
//}
