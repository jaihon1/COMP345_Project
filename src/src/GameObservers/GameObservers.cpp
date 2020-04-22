#include "GameObservers.h"
#include <iostream>
using namespace std;


GameObservers::GameObservers()
{
	_subject = NULL;
}

GameObservers::GameObservers(GamePlay* const gp)
{
	_subject = gp;
	// n_players = _subject->getNumPlayers(); - n_players attribute not used?
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
	if (_subject->getCurrentPlayer() != NULL) {
		turnConsole.cout("\nCurrent player ID: %d\n", _subject->getCurrentPlayer()->getID());
	}

	if (_subject->getPlayerAction() == 1)
	{
		turnConsole.cout("\nPlaced a harvest tile \n");

		turnConsole.cout("\nDisplaying current ressource tracker: \n");
		turnConsole.cout("Lumber: %d\n", _subject->getScoringObject()->get_lumber());
		turnConsole.cout("Sheep: %d\n", _subject->getScoringObject()->get_sheep());
		turnConsole.cout("Wheat: %d\n", _subject->getScoringObject()->get_wheat());
		turnConsole.cout("Rock: %d\n", _subject->getScoringObject()->get_stone());
	}
	else if (_subject->getPlayerAction() == 2)
	{
		turnConsole.cout("\nPlaced a shipment tile \n");

		turnConsole.cout("\nDisplaying current ressource tracker: \n");
		turnConsole.cout("Lumber: %d\n", _subject->getScoringObject()->get_lumber());
		turnConsole.cout("Sheep: %d\n", _subject->getScoringObject()->get_sheep());
		turnConsole.cout("Wheat: %d\n", _subject->getScoringObject()->get_wheat());
		turnConsole.cout("Rock: %d\n", _subject->getScoringObject()->get_stone());
	}
	else if (_subject->getPlayerAction() == 3)
	{
		turnConsole.cout("\nAdded a building to village board \n");

		//print out updated village count
		VGMaps* ref = _subject->getCurrentPlayer()->getVGMaps();

		turnConsole.cout("\nNumber of buildings on player's VGMAP: %d\n", _subject->getScoringObject()->get_density(*ref));

		//display ressources left (always displayed below)
		turnConsole.cout("\nDisplaying current ressource tracker: \n");
		turnConsole.cout("Lumber: %d\n", _subject->getScoringObject()->get_lumber());
		turnConsole.cout("Sheep: %d\n", _subject->getScoringObject()->get_sheep());
		turnConsole.cout("Wheat: %d\n", _subject->getScoringObject()->get_wheat());
		turnConsole.cout("Rock: %d\n", _subject->getScoringObject()->get_stone());

	}
	else if (_subject->getPlayerAction() == 4)
	{
		turnConsole.cout("\nPlayer is not building anything \n");
	}
	else if (_subject->getPlayerAction() == 5)
	{
		turnConsole.cout("\nPlayer not doing the right thing \n");
	}
	else if (_subject->getPlayerAction() == 6) {
		turnConsole.cout("\nEntered SHARE THE WEALTH portion of Player %d's turn \n", _subject->getCurrentPlayer()->getID());
	}
	else if (_subject->getPlayerAction() == 7) {
		turnConsole.cout("START Player %d's turn \n", _subject->getCurrentPlayer()->getID());
	}
	else if (_subject->getPlayerAction() == 8) {
		turnConsole.cout("\nEND Player %d's turn \n", _subject->getCurrentPlayer()->getID());
	}
	else if (_subject->getPlayerAction() == 9) {
		turnConsole.cout("GAME START");
	}
	else if (_subject->getPlayerAction() == 10) {
		turnConsole.cout("\nGAME END");
	}
	else {
		turnConsole.cout("\nUnknown Player Action \n");
	}

}