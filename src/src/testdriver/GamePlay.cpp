#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "GamePlay.h"
#include "../GameObservers/ViewObserver.h"

using namespace std;

BuildingTile* GamePlay::selectBT(vector<BuildingTile*>* btVector, Hand* hand) {
	int btInput;
	BuildingTile* btToAdd = nullptr;
	while (true) {

		// loop for building tile index
		while (true) {
			cout << "Which building tile would you like to use? " << endl;;
			cin >> btInput;
			if (btInput >= 0 && btInput < btVector->size()) {
				break;
			}
			cout << "Incorrect index, please choose again." << endl;
		}

		btToAdd = btVector->at(btInput);
		int index;
		// get index for resourceScoreArr
		switch (btToAdd->getBuildingColorType()) {

		case BuildingColorType::GreenSheep:
			index = static_cast<int>(ResourceName::Sheep);
			break;
		case BuildingColorType::GreyRock:
			index = static_cast<int>(ResourceName::Rock);
			break;
		case BuildingColorType::RedLumber:
			index = static_cast<int>(ResourceName::Lumber);
			break;
		case BuildingColorType::YellowHay:
			index = static_cast<int>(ResourceName::Wheat);
			break;
		}

		//enum goes from 1-4 but array is 0-3
		index -= 1;

		// verify there are enough resources to add the building tile
		if (hand->getResourceScore(index) < btToAdd->getBuildingNum()) {
			cout << "Insufficient resources for this building tile.  Please select again." << endl;
		}
		else {
			break;
		}
	}
	return btToAdd;
}

bool GamePlay::placeBT(BuildingTile* btToAdd, Player* player, Hand* hand) {
	int vgRow;
	int vgColumn;
	cout << endl;
	while (true) {
		cout << "Where would you like to place the tile?\n" << "row: ";
		cin >> vgRow;
		cout << "column: ";
		cin >> vgColumn;
		cout << endl;

		Hand::ExchangeToken* exToken = new Hand::ExchangeToken(player, btToAdd, vgRow, vgColumn);

		switch (hand->exchange(exToken)) {
		case 0:
			return true;
		case 2:
			break;
		default:
			cout << "Rejected for unknown reason.  Please try again." << endl;
			break;
		}
	}
}

// parameter used to select initial prompt
bool exitBT(bool placeAnother) {

	bool correctInputFlag = false;
	while (!correctInputFlag) {
		char keepPlacingBT;

		if (placeAnother) {
			cout << "Would you like to place another building tile? y/n" << endl;
		}
		else {
			cout << "Would you like to place a building tile? y/n" << endl;
		}
		cin >> keepPlacingBT;
		switch (keepPlacingBT) {
		case 'y':
			return false;
			break;
		case 'n':
			return true;
			correctInputFlag = true;
			break;
		default:
			cout << "incorrect input" << endl;
			break;
		}
	}
	return true;
}

void GamePlay::singlePlayerBTplacement(Player* player, Hand* hand) {

	while (true) {
		vector<BuildingTile*>* btVector = player->getBuildings();
		cout << "These are your building tiles: " << endl;
		for (int i = 0; i < btVector->size(); i++) {
			cout << "Tile " << i << ": ";
			btVector->at(i)->printBuildingTile();
		}


		cout << endl;
		player->getVGBoard()->printVGMap();
		cout << endl;

		// parameter used to select initial prompt
		if (exitBT(false)) {
			break;
		}

		int btInput;

		// BUILDING TILE PLACEMENT
		BuildingTile* btToAdd = selectBT(btVector, hand);
		if (!placeBT(btToAdd, player, hand)) {
			cout << "error in placing building tile" << endl;
		}

		player->getVGBoard()->printVGMap();
		cout << endl;
		hand->displayHand();
		cout << endl;

		// parameter used to select initial prompt
		if (exitBT(true)) {
			break;
		}
	}
	return;
}


void GamePlay::singleTurn(GBMaps* gameBoard, Player** playerArr, Hand* hand, int turnIndex, int numPlayers) {
	gameBoard->printGameBoard();


	int htIndex;
	vector<HarvestTile*>* htVector = nullptr;

	while (true) {
		cout << "These are your harvest tiles: " << endl;
		htVector = playerArr[turnIndex]->getHarvestTiles();
		cout << endl << "0: " << endl;
		htVector->at(0)->printHarvestTile();
		cout << endl << "1: " << endl;
		htVector->at(1)->printHarvestTile();
		cout << endl << "Enter 0 or 1 to select tile: ";
		cin >> htIndex;
		if (htIndex == 0 || htIndex == 1) {
			break;
		}
		cout << "Incorrect index, please choose again." << endl;
	}
	HarvestTile* harvestTile = htVector->at(htIndex);

	int row;
	int column;
	int tilePlaced = 0;

	while (tilePlaced == 0) {
		cout << "Where would you like to place the tile?\n" << "row: ";
		cin >> row;
		cout << "column: ";
		cin >> column;
		tilePlaced = gameBoard->addHarvestTile(row, column, harvestTile);
		if (tilePlaced == 0) {
			cout << "Placement request rejected. Try again." << endl;
		}
	}

	hand->intializeHand();
	gameBoard->printGameBoard();
	cout << endl << "Resources:" << endl;
	hand->displayHand();
	cout << endl << endl;

	singlePlayerBTplacement(playerArr[turnIndex], hand);

	// SHARE THE WEALTH LOOP (loops through each player allowing them to use remaining resources
	cout << "Share the wealth!" << endl;
	for (int btRoundIndex = (turnIndex + 1) % numPlayers; btRoundIndex != turnIndex; btRoundIndex = (btRoundIndex + 1) % numPlayers) {
		cout << "Player " << playerArr[btRoundIndex]->getID() <<": " << endl;
		singlePlayerBTplacement(playerArr[btRoundIndex], hand);
	}
}

int GamePlay::getID(Player** playerArr, int numPlayers) {
	int id = 0;
	int min = INT_MAX;
	int startPlayer = 0;
	for (int i = 0; i < numPlayers; i++) {
		cout << "Please enter student ID: ";
		cin >> id;
		playerArr[i]->setID(id, i);
		if (id < min) {
			min = id;
			startPlayer = i;
		}
	}
	return startPlayer;

}

void GamePlay::playGame() {
	GameStart* gameStart = new GameStart();
	cout << "How many players: 2, 3, or 4? ";
	int numPlayers;
	cin >> numPlayers;
	gameStart->setup(numPlayers);

	// intialized Game Objects
	GBMaps* gameBoard = gameStart->getGBoard();
	Player** playerArr = gameStart->getPlayerArr();
	Hand* hand = gameStart->getHand();
	Scoring* sc = gameStart->getSc();
	ViewObserver* viewObs = new ViewObserver(sc);
	int startPlayer = getID(playerArr, numPlayers);

	for (int turnIndex = startPlayer; turnIndex < numPlayers; turnIndex = (turnIndex + 1) % numPlayers) {
		cout
			<< "**************************************************" << endl
			<< "Player " << playerArr[turnIndex]->getID() << endl;
		singleTurn(gameBoard, playerArr, hand, turnIndex, numPlayers);
		// check end game condition
		if (gameBoard->getOccupiedTile() == 48) {
			break;
		}
	}

	// declare winner
	VGMaps** vgMapArr = new VGMaps * [4];
	for (int i = 0; i < 4; i++) {
		vgMapArr[i] = i < numPlayers ? playerArr[i]->getVGMaps() : nullptr;
	}
	cout << "Winner is Player " << sc->get_winner(vgMapArr);
}