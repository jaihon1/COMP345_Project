#include "GameObservers.h"
#include <iostream>
using namespace std; 


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
	cout << "Created observer" << endl; 
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
	turnConsole.cout("Current player ID: ", _subject->getCurrentPlayer()->getID(), " \n"); 


	if (_subject->getPlayerAction() == 1)
	{
		turnConsole.cout("Placed a harvest tile \n"); 


		turnConsole.cout("Displaying current ressource tracker: \n"); 
		turnConsole.cout("Lumber: ", _subject->getScoringObject()->get_lumber(), " \n");
		turnConsole.cout("Sheep: ", _subject->getScoringObject()->get_sheep(), "\n"); 
		turnConsole.cout("Wheat: ", _subject->getScoringObject()->get_wheat(), "\n"); 
		turnConsole.cout("Rock: ", _subject->getScoringObject()->get_stone(), "\n"); 
	}
	else if (_subject->getPlayerAction() == 2)
	{
		turnConsole.cout("Placed a shipment tile \n"); 
	}
	else if (_subject->getPlayerAction() == 3)
	{
		turnConsole.cout("Added a building to village board \n"); 

		//print out updated village count
		VGMaps *ref = _subject->getCurrentPlayer()->getVGMaps();

		turnConsole.cout("Number of buildings on player's VGMAP: ", _subject->getScoringObject()->get_density(*ref), "\n"); 

		//display ressources left (always displayed below)
		turnConsole.cout("Displaying current ressource tracker: \n");
		turnConsole.cout("Lumber: ", _subject->getScoringObject()->get_lumber(), " \n");
		turnConsole.cout("Sheep: ", _subject->getScoringObject()->get_sheep(), "\n");
		turnConsole.cout("Wheat: ", _subject->getScoringObject()->get_wheat(), "\n");
		turnConsole.cout("Rock: ", _subject->getScoringObject()->get_stone(), "\n");

	}
	else if (_subject->getPlayerAction() == 4)
	{
		turnConsole.cout("Player is not building anything \n"); 
	}
	else if (_subject->getPlayerAction() == 5)
	{
		turnConsole.cout("Player not doing the right thing \n"); 
	}
			/*
			cout << "Current player ID: " << _subject->getCurrentPlayer()->getID() << endl; 

		
			if (_subject->getPlayerAction() == 1)
			{
				cout << "Placed a harvest tile" << endl; 


				cout << "Displaying current ressource tracker:" << endl;
				cout << "Lumber: " << _subject->getScoringObject()->get_lumber() << endl;
				cout << "Sheep: " << _subject->getScoringObject()->get_sheep() << endl;
				cout << "Wheat: " << _subject->getScoringObject()->get_wheat() << endl;
				cout << "Rock: " << _subject->getScoringObject()->get_stone() << endl;
			}
			else if (_subject->getPlayerAction() == 2)
			{
				cout << "Placed a shipment tile" << endl; 
			}
			else if (_subject->getPlayerAction() == 3)
			{
				cout << "Added a building to village board" << endl; 

				//print out updated village count
				VGMaps *ref = _subject->getCurrentPlayer()->getVGMaps(); 

				cout << "Number of buildings on player's VGMAP: " << _subject->getScoringObject()->get_density(*ref) << endl << endl; 

				//display ressources left (always displayed below)
				cout << "Displaying current ressource tracker:" << endl;
				cout << "Lumber: " << _subject->getScoringObject()->get_lumber() << endl;
				cout << "Sheep: " << _subject->getScoringObject()->get_sheep() << endl;
				cout << "Wheat: " << _subject->getScoringObject()->get_wheat() << endl;
				cout << "Rock: " << _subject->getScoringObject()->get_stone() << endl;

			}
			else if (_subject->getPlayerAction() == 4)
			{
				cout << "Player is not building anything" << endl; 
			}
			else if (_subject->getPlayerAction() == 5)
			{
				cout << "Player not doing the right thing" << endl; 
			}
			*/ 

	
}
