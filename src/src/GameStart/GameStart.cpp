
#include <string>
#include "../modules/GBMapLoader/GBMapLoader.h"
#include "../modules/tile/Dictionary.h"
#include "../modules/tile/Resources.h"
#include "../modules/Scoring/Scoring.h"
#include "../modules/player/player.h"
#include "../modules/board/VGMaps.h"
#include "../modules/VGMapLoader/VGMapLoader.h"
#include "GameStart.h"

GBMaps* GameStart::getGBoard()
{
	return gB;
}

Player** GameStart::getPlayerArr()
{
	return playerArr;
}

Scoring* GameStart::getSc()
{
	return sc;
}

HarvestDeck* GameStart::getHarvestDeck()
{
	return harvestDeck;
}

BuildingDeck* GameStart::getBuildingDeck()
{
	return buildingDeck;
}

BuildingPool * GameStart::getBuildingPool()
{
	return buildingPool; 
}

Hand* GameStart::getHand()
{
	return hand;
}

int GameStart::getNumPlayers()
{
	return numPlayers;
}

void GameStart::setup(int inNumPlayers) {

	sc = new Scoring();
	harvestDeck = new HarvestDeck();
	buildingDeck = new BuildingDeck();
	buildingPool = new BuildingPool(buildingDeck);

	// SWITCH FOR MAP LOADER
	gB = new GBMaps(inNumPlayers, 'a', sc);
	GBMapLoader* gBLoader = NULL;

	// TODO: add error catching statements
	/*******************************************
	******* REMEMBER TO CHECK FILE PATHS *******
	********************************************
	*/ 

	//DAMIAN CHECK PATH ON YOUR COMPUTER 

	string root = "..\\..\\data\\StartGameMaps\\";
	//string root = "C:\\Users\\titi7\\source\\repos\\Comp345_Assignment2\\Comp345_Assignment2\\files\\data\\StartGameMaps\\"; 

	switch (inNumPlayers) {
	case 2:
		gBLoader = new GBMapLoader((root+"2-PlayerGameStart.txt").c_str(), sc);
		break;
	case 3:
		gBLoader = new GBMapLoader((root+"3-PlayerGameStart.txt").c_str(), sc);
		break;
	case 4:
		gBLoader = new GBMapLoader((root+"4-PlayerGameStart.txt").c_str(), sc);
		break;
	default:
		cout << "Error in GameStart setup method";
		break;
	}
	gB = gBLoader->getBoard();

	playerArr = new Player*[inNumPlayers];

	// instantiate each player and initialize their harvest and building tiles
	for (int i = 0; i < inNumPlayers; i++) {
		playerArr[i] = new Player(sc, i);
		for (int j = 0; j < 6; j++) {
			playerArr[i]->drawBuilding(*buildingDeck);
		}
		playerArr[i]->drawHarvestTile(*harvestDeck);
		playerArr[i]->drawHarvestTile(*harvestDeck);
		//HarvestTile *ship = playerArr[i]->drawHarvestTile(*harvestDeck); 

		playerArr[i]->setShipmentTile(harvestDeck->draw()); //he has a shipment tile 
		//playerArr[i]->setShipmentTile(ship); //that harvest tile is not a shipment tile

	}

	hand = new Hand(sc);
}



