#include "GameObservers.h"



GameObservers::GameObservers()
{
	_subject = NULL; 
}

GameObservers::GameObservers(MainLoop * s)
{
	_subject = s; 
	n_players = _subject->getNumPlayers();
	_subject->attach(this); 
	turnConsole.Create("TurnObserver"); 
	turnConsole.cprintf(CConsoleLoggerEx::COLOR_WHITE | CConsoleLoggerEx::COLOR_BACKGROUND_BLACK, "TurnObserver Start\n\n"); 
}

GameObservers::GameObservers(Scoring * sc) : sc(sc)
{
	sc->attach(this);
}


GameObservers::~GameObservers()
{
	//detach itself from the mainloop subject
	_subject->detach(this); 
}

void GameObservers::update()
{
	cout << "Inside GameOberservers update" << endl; 
	turndisplay(); 
}

void GameObservers::turndisplay()
{
	//nothing to notify if the game ended 
	while (_subject->GameEnded == false)
	{
		for (int i = 0; i < *n_players; i++)
		{
			//Check for if player is building harvest tile or building tile?

			//Printing player id
			turnConsole.cout("Display current turn \n"); 
			turnConsole.cout("Current player ID: ", _subject->getCurrentPlayer(i)->getID(), "\n"); 

			//Display action for harvest/shipment tile or building Tile? 
			if (_subject->getPlayerAction() == 1)
			{
				turnConsole.cout("Placed a harvest tile \n"); 
			}
			else if (_subject->getPlayerAction() == 2)
			{
				turnConsole.cout("Placed a shipment tile \n"); 
			}
			else if (_subject->getPlayerAction() == 3)
			{
				turnConsole.cout("Adding a building to village board \n"); 
			}
			else if (_subject->getPlayerAction() == 4)
			{
				turnConsole.cout("Player is not building anything \n"); 
			}
			else
			{
				turnConsole.cout("Player not doing the right thing \n");  
			}

			//show ressources - but where is this going to print? to test 
			turnConsole.cout("Displaying current ressource tracker: \n"); 
			turnConsole.cout("Lumber: ", _subject->getScoringObject()->get_lumber()); 
			turnConsole.cout("Sheep: ", _subject->getScoringObject()->get_sheep());
			turnConsole.cout("Wheat: ", _subject->getScoringObject()->get_wheat());
			turnConsole.cout("Rock: ", _subject->getScoringObject()->get_stone());
			
			
			//print number of building tiles - add code when merge with Nguyen's new scoring 


		}
	}

}

void GameObservers::update()
{
	std::cout << "GameObservers updated" << std::endl;

}