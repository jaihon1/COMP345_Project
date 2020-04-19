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
			turnConsole.cout << "Display current turn" << endl;
			turnConsole.cout << "Current player ID: " << _subject->getCurrentPlayer(i)->getID() << endl; 

			//Display action for harvest/shipment tile or building Tile? 
			if (_subject->getPlayerAction() == 1)
			{
				turnConsole.cout << "Placed a harvest tile" << endl; 
			}
			else if (_subject->getPlayerAction() == 2)
			{
				turnConsole.cout << "Placed a shipment tile" << endl; 
			}
			else if (_subject->getPlayerAction() == 3)
			{
				turnConsole.cout << "Adding a building to village board" << endl;
			}
			else if (_subject->getPlayerAction() == 4)
			{
				turnConsole.cout << "Player is not building anything" << endl; 
			}
			else
			{
				turnConsole.cout << "Player not doing the right thing" << endl;  
			}

			//show ressources - but where is this going to print? to test 
			_subject->getScoringObject()->display_res; 

			//print number of building tiles - add code when merge with Nguyen's new scoring 


		}
	}

}
