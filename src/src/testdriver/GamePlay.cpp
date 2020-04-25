#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "GamePlay.h"
#include "../GameObservers/ViewObserver.h"

using namespace std;

bool GamePlay::enoughResourcesToPlayBT(vector<BuildingTile*>* btVector, Hand* hand){

	for (int btVectIndex = 0; btVectIndex < btVector->size(); btVectIndex++) {

		int resNum = btVector->at(btVectIndex)->getBuildingNum();

		switch(btVector->at(btVectIndex)->getBuildingColorType()){
		case BuildingColorType::RedLumber:
			if (hand->getResourceScore(0) >= resNum) {
				return true;
			}
			break;
		case BuildingColorType::GreenSheep:
			if (hand->getResourceScore(1) >= resNum) {
				return true;
			}
			break;
		case BuildingColorType::YellowHay:
			if (hand->getResourceScore(2) >= resNum) {
				return true;
			}
			break;
		case BuildingColorType::GreyRock:
			if (hand->getResourceScore(3) >= resNum) {
				return true;
			}
			break;
		}
	}
	return false;
}

BuildingTile* GamePlay::selectBT(vector<BuildingTile*>* btVector, Hand* hand) {
	int btInput;
	BuildingTile* btToAdd = nullptr;
	while (true) {

		if (!enoughResourcesToPlayBT(btVector, hand)) {
			cout<<"Sorry you have insufficient resources to play a building tile."<<endl;
			return nullptr;
		}

		// loop for building tile index
		while (true) {
			cout << "Which building tile would you like to use?" << endl;;
			cin >> btInput;

			if (btInput >= 0 && btInput < btVector->size()) {
				break;
			}
			cout << "Incorrect index, please choose again." << endl;
			notifyStateChange(5);
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
			notifyStateChange(5);
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
			notifyStateChange(5);
			continue;
		default:
			cout << "Rejected for unknown reason.  Please try again." << endl;
			notifyStateChange(5);
			break;
		}
	}
}

// parameter used to select initial prompt
bool GamePlay::exitBT(bool placeAnother) {

	while (true) {
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
		case 'n':
			notifyStateChange(4);
			return true;
		default:
			cout << "incorrect input" << endl;
			notifyStateChange(5);
			break;
		}
	}
	return true;
}

void GamePlay::singlePlayerBTplacement(Player* player, Hand* hand) {

	while (true) {
		showResources(hand);
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

		if (btToAdd == nullptr) {
			break;
		}

		if (!placeBT(btToAdd, player, hand)) {
			cout << "error in placing building tile" << endl;
			notifyStateChange(5);
		}
		notifyStateChange(3);
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

ResourceName GamePlay::getResourceName(const char* name) {
	bool error = true;
	int resource;
	while (error) {
		cout << name << ": ";
		cin >> resource;
		error = (resource < 1 || resource > 4);
		if (error) {
			cout << "Invalid input. Try again." << endl;
			notifyStateChange(5);
		}
	}
	return static_cast<ResourceName>(resource);
}

HarvestTile* GamePlay::shipmentTile() {
	ResourceName topLeft, topRight, bottomLeft, bottomRight;
	cout << "Which resource would you like your shipmentTile to consist of? Lumber = 1, Sheep = 2, Wheat = 3, Rock = 4" << endl;
	topLeft = getResourceName("Top Left");
	topRight = getResourceName("Top Right");
	bottomLeft = getResourceName("Bottom Left");
	bottomRight = getResourceName("Bottom Right");

	return new HarvestTile(topLeft, topRight, bottomLeft, bottomRight);
}

void GamePlay::showResources(Hand* hand) {
	cout << endl << "Resources:" << endl;
	hand->displayHand();
	cout << endl;
}


void GamePlay::singleTurn(GBMaps* gameBoard, Player** playerArr, Hand* hand, int turnIndex, int numPlayers) {
	gameBoard->printGameBoard();

	int htIndex;
	vector<HarvestTile*>* htVector = nullptr;
	bool shipmentFlag = false;


	while (true) {
		cout << "These are your harvest tiles: " << endl;
		htVector = playerArr[turnIndex]->getHarvestTiles();
		cout << endl << "0: " << endl;
		htVector->at(0)->printHarvestTile();
		cout << endl << "1: " << endl;
		htVector->at(1)->printHarvestTile();
		cout << endl << "Enter 0 or 1 to select tile ";
		if (playerArr[turnIndex]->getShipmentTile() != nullptr) {
			cout << "(or 5 to place your shipment tile): ";
		}
		cin >> htIndex;
		if (htIndex == 0 || htIndex == 1) {
			break;
		}
		else if (htIndex == 5 && playerArr[turnIndex]->getShipmentTile() != nullptr) {
			shipmentFlag = true;
			break;
		}

		cout << "Incorrect index, please choose again." << endl;
		notifyStateChange(5);
	}

	HarvestTile* tile;

	if (shipmentFlag == true) {
		tile = shipmentTile();
	}
	else {
		tile = htVector->at(htIndex);
	}

	int row;
	int column;
	int tilePlaced = 0;

	while (tilePlaced == 0) {
		cout << "Where would you like to place the tile?\n" << "row: ";
		cin >> row;
		cout << "column: ";
		cin >> column;
		tilePlaced = gameBoard->addHarvestTile(row, column, tile);
		if (tilePlaced == 0) {
			cout << "Placement request rejected. Try again." << endl;
			notifyStateChange(5);
		}
	}
	if (shipmentFlag == true) {
		notifyStateChange(2);
	}
	else {
		notifyStateChange(1);
	}

	hand->intializeHand();
	gameBoard->printGameBoard();

	singlePlayerBTplacement(playerArr[turnIndex], hand);

	// SHARE THE WEALTH LOOP (loops through each player allowing them to use remaining resources
	cout << "Share the wealth!" << endl;
	notifyStateChange(6);
	for (int btRoundIndex = (turnIndex + 1) % numPlayers; btRoundIndex != turnIndex; btRoundIndex = (btRoundIndex + 1) % numPlayers) {
		cout << "Player " << playerArr[btRoundIndex]->getID() << ": " << endl;
		currentPlayer = playerArr[btRoundIndex];
		singlePlayerBTplacement(playerArr[btRoundIndex], hand);
	}
	currentPlayer = playerArr[turnIndex];
	if (shipmentFlag == true) {
		gameBoard->replaceHarvestTile(row, column, playerArr[turnIndex]->getShipmentTile());
		playerArr[turnIndex]->setShipmentTile(nullptr);
		delete tile;
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
	sc = gameStart->getSc();
	ViewObserver* viewObs = new ViewObserver(sc);
	int startPlayer = getID(playerArr, numPlayers);
	for (int turnIndex = startPlayer; turnIndex < numPlayers; turnIndex = (turnIndex + 1) % numPlayers) {
		cout
			<< "**************************************************" << endl
			<< "Player " << playerArr[turnIndex]->getID() << endl;
		currentPlayer = playerArr[turnIndex];
		notifyStateChange(7);
		singleTurn(gameBoard, playerArr, hand, turnIndex, numPlayers);
		notifyStateChange(8);
		// check end game condition
		if (gameBoard->getOccupiedTile() == 48) {
			break;
		}
	}

	// declare winner
	declareWinner(playerArr, numPlayers);
	
	notifyStateChange(9);
}

void GamePlay::declareWinner(Player** playerArr, int numPlayers) {
	int winner = -1;
	int maxScore = -1;
	int availBuild = -1;
	for (int i = 0; i < numPlayers; i++) {
		int score = playerArr[i]->getScore();
		if (score > maxScore) {
			winner = i;
			maxScore = score;
		}
		else if (score == maxScore) {
			winner = tieBreaker(playerArr[winner], playerArr[i])-1;
		}
		cout << "Player " << playerArr[i]->getID() << " score " << score << endl;
	}
	if (winner == -1) {
		cout << "WOW! It's a tie!" << endl;
	}
	else {
		cout << endl << "And the winner is... Player " << playerArr[winner]->getID() << endl;
	}
}

int GamePlay::tieBreaker(Player* winner, Player* contender) {
	if (winner->getVGMaps()->getEmptySpaces() > contender->getVGMaps()->getEmptySpaces()) {
		return winner->getPosition();
	}
	else if (winner->getVGMaps()->getEmptySpaces() < contender->getVGMaps()->getEmptySpaces()) {
		return contender->getPosition();
	}
	else if (winner->getNumberOfBuildingTiles()>contender->getNumberOfBuildingTiles()){
		return winner->getPosition();
	}
	else if (winner->getNumberOfBuildingTiles() < contender->getNumberOfBuildingTiles()) {
		return contender->getPosition();
	}
	return -1;

}

// METHODS FOR TIFF's GAME OBSERVER
Player* GamePlay::getCurrentPlayer() {
	return currentPlayer;
}

int GamePlay::getPlayerAction() {
	return player_action;
}

Scoring* GamePlay::getScoringObject() {
	return sc;
}

void GamePlay::notifyStateChange(int action) {
	player_action = action;
	notify();
}