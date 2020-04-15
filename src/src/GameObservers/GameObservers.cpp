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
	while (_subject->GameEnded == false)
	{
		for (int i = 0; i < *n_players; i++)
		{
			//Check for if player is building harvest tile or building tile?

			//Printing player id
			cout << "Display current turn" << endl;
			cout << "Current player ID: " << _subject->getCurrentPlayer(i)->getID() << endl; 

			//Display action for harvest/shipment tile 
			if (_subject->hschoice == 1)
			{
				cout << "Placed a harvest tile" << endl; 
			}
			else if (_subject->hschoice == 2)
			{
				cout << "Placed a shipment tile" << endl; 
			}
			else
			{
				cout << "Player misplaced" << endl;  
			}

			//show ressources
			


			//show updated ressources - call notify from inside main loop?? 

		}
	}

}
