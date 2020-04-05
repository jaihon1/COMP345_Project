

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "../modules/board/GBMaps.h"
#include "../modules/GBMapLoader/GBMapLoader.h"
#include "../modules/tile/Dictionary.h"
#include "../modules/tile/Resources.h"
#include "../modules/Scoring/Scoring.h"
#include "../modules/player/player.h"
#include "../modules/board/VGMaps.h"
#include "../modules/VGMapLoader/VGMapLoader.h"
#include "../GameStart/GameStart.h"


#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

using namespace std;

void printHarvestTile(HarvestTile* inHarvestTile) {

	cout << setw(8) << HarvestTile::ResourceNameToString(inHarvestTile->getResource(ResourceLocation::topLeft))
		<< setw(8) << HarvestTile::ResourceNameToString(inHarvestTile->getResource(ResourceLocation::topRight)) << endl
		<< setw(8) << HarvestTile::ResourceNameToString(inHarvestTile->getResource(ResourceLocation::bottomLeft))
		<< setw(8) << HarvestTile::ResourceNameToString(inHarvestTile->getResource(ResourceLocation::bottomRight)) << endl;

}

void printBuildingTile(BuildingTile* inBT) {
	cout << inBT->getBuildingNum() << " " << inBT->Building_typeToChar(inBT->getBuildingColorType()) << endl;
}

void harvestTileTest() {

	HarvestDeck* testDeck = new HarvestDeck();
	HarvestTile* testHarvestTile = testDeck->draw();
	printHarvestTile(testHarvestTile);
	cout << endl;
	char yesNo;
	char rotate;
	cout << "Would you like to rotate the tile? y/n ";
	cin >> yesNo;
	//ROTATE METHODS TEST
	while (yesNo == 'y') {
		cout << "Right = r, Left = l: ";
		cin >> rotate;
		cout << endl;
		switch (rotate) {
		case 'r':
			testHarvestTile->RotateRight();
			break;
		case 'l':
			testHarvestTile->RotateLeft();
			break;
		default:
			cout << "Invalid selection." << endl;
			break;
		}
		printHarvestTile(testHarvestTile);
		cout << endl << "Again? y/n ";
		cin >> yesNo;
	}
	delete testDeck;

}

HarvestTile* rotateHT(HarvestTile* inTile) {

	printHarvestTile(inTile);
	cout << endl;
	char yesNo;
	char rotate;
	cout << "Would you like to rotate the tile? y/n ";
	cin >> yesNo;
	//ROTATE METHODS TEST
	while (yesNo == 'y') {
		cout << "Right = r, Left = l: ";
		cin >> rotate;
		cout << endl;
		switch (rotate) {
		case 'r':
			inTile->RotateRight();
			break;
		case 'l':
			inTile->RotateLeft();
			break;
		default:
			cout << "Invalid selection." << endl;
			break;
		}
		printHarvestTile(inTile);
		cout << endl << "Again? y/n ";
		cin >> yesNo;
	}

	return inTile;

}

void gbMapsTest() {

	int players;

	cout << "Welcome to GBMapsTest" << endl << "How many players? Select 2, 3, or 4: ";
	cin >> players;

	//SCORING OBJECT CONSTRUCTION
	Scoring* sc = new Scoring();

	//HARVEST DECK OBJECT CONSTRUCTION
	HarvestDeck* testDeck = new HarvestDeck();

	//GAMEBOARD CONSTRUCTION
	GBMaps* gameBoard = new GBMaps(players, 'a', sc);
	gameBoard->printGameBoard();
	cout << endl;

	int quit;
	int row;
	int column;
	int type;

	cout << "Would you like to add a harvest tile? Press 1 to continue. Press 3 to add ship. To quit, press 0. ";
	cin >> quit;
	HarvestTile* testHarvestTile;
	while (quit != 0) {

		switch (quit) {
		case 1:
			testHarvestTile = testDeck->draw();
			cout << "Where would you like to place the tile?\n" << "row: ";
			cin >> row;
			cout << "column: ";
			cin >> column;
			cout << endl;
			gameBoard->addHarvestTile(row, column, testHarvestTile);
			gameBoard->printGameBoard();
			cout << endl;
			break;
		case 2:
			//sc->display_res();
			cout << "Lumber: " << sc->get_lumber() << endl;
			cout << "Sheep:  " << sc->get_sheep() << endl;
			cout << "Wheat:  " << sc->get_wheat() << endl;
			cout << "Rock:   " << sc->get_stone() << endl;
			break;
		case 3:
			testHarvestTile = testDeck->draw();
			cout << "Where would you like to place the tile?\n" << "row: ";
			cin >> row;
			cout << "column: ";
			cin >> column;
			cout << "type: ";
			cin >> type;
			cout << endl;
			gameBoard->addShipmentTile(row, column, testHarvestTile, type);
			gameBoard->printGameBoard();
			cout << endl;
			break;
		default:
			cout << "Sorry invalid input." << endl;
			break;
		}
		cout << "To place another tile, Press 1.  To see resource list press 2. Otherwise to quit press 0. ";
		cin >> quit;
		cout << endl;
	}

	delete sc;
	delete testDeck;
	delete gameBoard;
}

void playerTest() {
	// Initializing variables
	Player bob;
	//    GBMaps map(4, 'b');
	BuildingDeck buildingDeck;
	HarvestDeck harvestDeck;
	HarvestTile harvestTile(ResourceName::Wheat, ResourceName::Sheep, ResourceName::Wheat, ResourceName::Lumber);

	// Get status of resources
	bob.ressourceTracker();

	// Drawing items from Building Deck
	cout << "BuildingDeck size: " << buildingDeck.getSize() << endl;
	cout << "My Buildings size: " << bob.getNumberOfBuildingTiles() << endl;
	cout << "Draw from BuildingDeck: " << bob.drawBuilding(buildingDeck) << endl;
	cout << "Deck size: " << buildingDeck.getSize() << endl;
	cout << "My Buildings size: " << bob.getNumberOfBuildingTiles() << endl;
	cout << "Draw from BuildingDeck: " << bob.drawBuilding(buildingDeck) << endl << endl;

	// Drawing items from Harvest Deck
	cout << "HarvestDeck size: " << harvestDeck.getSize() << endl;
	cout << "My Harvest size: " << bob.getNumberOfHarvestTiles() << endl;
	cout << "Draw from HarvestDeck: " << bob.drawHarvestTile(harvestDeck) << endl;
	cout << "H Deck size: " << harvestDeck.getSize() << endl;
	cout << "My Harvest size: " << bob.getNumberOfHarvestTiles() << endl;
	cout << "Draw from HarvestDeck: " << bob.drawHarvestTile(harvestDeck) << endl << endl;

	// Get status of resources
	bob.ressourceTracker();

	// Placing a Harvest Tile
//    cout << "Placing Harvest Tile: " << endl;
//    bob.placeHarvestTile(0, 0, harvestTile, map);

}

void runGame(GBMaps* gameBoard, HarvestDeck* testDeck) {

	gameBoard->printGameBoard();

	//SAVER CONTSTRUCTION
	GBMapSaver* testSaver = new GBMapSaver();

	int quit;
	int row;
	int column;

	cout << "Would you like to add a harvest tile? Press 1 to continue. To quit, press 0. ";
	cin >> quit;
	while (quit != 0) {

		HarvestTile* testHarvestTile = testDeck->draw();
		cout << "Where would you like to place the tile?\n" << "row: ";
		cin >> row;
		cout << "column: ";
		cin >> column;
		cout << endl;
		gameBoard->addHarvestTile(row, column, testHarvestTile);
		gameBoard->printGameBoard();
		cout << endl;
		cout << "To place another tile, Press 1.  To save game press 2. Otherwise to quit press 0. ";
		cin >> quit;
		if (quit == 2) {
			string filePath;
			cout << "Please enter the file path: " << endl;
			cin >> filePath;

			testSaver->save(gameBoard, &filePath[0]);
			quit = 0;
		}

	}
	
	delete testSaver;

}

void playGBMaps() {
	bool flag = true;
	while (flag) {
		int oldOrNew;
		cout << "Welcome to New Haven" << endl << "1 - Start a new game" << endl << "2 - Load game" << endl << "0 - return to previous menu" << endl << "Which would you like to do: ";
		cin >> oldOrNew;

		// SCORING OBJECT CONSTRUCTION
		Scoring* sc = new Scoring();

		// HARVEST DECK OBJECT CONSTRUCTION
		HarvestDeck* testDeck = new HarvestDeck();

		GBMaps* gameBoard = NULL;
		GBMapLoader* testLoader;
		switch (oldOrNew) {
		case 0:
			flag = false;
			break;

		case 1:
			int players;
			cout << "How many players? Select 2, 3, or 4: ";
			cin >> players;

			//GAMEBOARD CONSTRUCTION
			gameBoard = new GBMaps(players, 'a', sc);
			runGame(gameBoard, testDeck);
			break;

		case 2: {
				string filePath;
				cout << "Please enter the file path of the game you wish to load: " << endl;
				cin >> filePath;
				// LOADER CONSTRUCTION
				testLoader = new GBMapLoader(&filePath[0], sc);
				gameBoard = testLoader->getBoard();
				delete testLoader;
				if (gameBoard != NULL) {
					runGame(gameBoard, testDeck);
				}
				break;
		}
		default:
			cout << "Sorry invalid input, please choose again" << endl;
			break;
		}

		delete sc;
		delete testDeck;
		
		delete gameBoard;

	}
}

void VGMapLoaderTest()
{
	//create a new VGBoard
	VGMaps* va = new VGMaps();

	int ro = *(va->rows);
	int co = *(va->columns);

	va->printVGMap();
	cout << "created VGMap" << endl;



	cout << "Add building" << endl;



	BuildingColorType* type1 = new BuildingColorType(BuildingColorType::GreenSheep);
	BuildingStatus* status1 = new BuildingStatus(BuildingStatus::Normal);

	BuildingTile* t1 = new BuildingTile(type1, status1);

	/*
	cout << BuildingTile::Building_typeToChar(t1->getBuildingColorType()) << endl;
	cout << BuildingTile::Building_statusToChar(t1->getSide()) << endl;
	*/


	cout << BuildingTile::Building_intToChar(t1->getBuildingNum()) << endl;


	va->addNewBuildingTile(*t1, 0, 0);


	cout << "Current map" << endl;
	va->printVGMap();


	cout << "Saving VGMAP out" << endl;

	VGMapSaver* s = new VGMapSaver();
	/*************************************************
	**************************************************
					CHECK FILE PATH!
	**************************************************
	**************************************************
	vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
	*/
	//s->save(va, "C:\json_test\VGMaptest.json");  -> BAD 

	s->save(va, "C:\\Users\\Damian\\Documents\\Repos\\COMP345_Project\\data\\VGMaptest5.json");

	cout << "Saved va map" << endl;



	VGMapLoader* m = new VGMapLoader();

	cout << "\n";
	cout << "Loading VGMap in " << endl;

	VGMapLoader* l = new VGMapLoader("C:\\json_test\\VGMaptest5.json");

	cout << "\n";
	cout << "\n";
	cout << "Sucess in reading" << endl;

	cout << "Current MAP" << endl;

	va->printVGMap();
	
	delete va;
	delete type1;
	delete status1;
	delete t1;
	delete s;
	delete m;
	delete l;
}


void gameStartTest() {
	GameStart* gameStart = new GameStart();
	cout << "How many players: 2, 3, or 4? ";
	int numPlayers;
	cin >> numPlayers;
	gameStart->setup(numPlayers);

	cout << "Initial Game Board: \n";
	gameStart->getGBoard()->printGameBoard();

	Player** player = gameStart->getPlayerArr();
	cout << "These are your initial harvest tiles, which tile would you like to use (indexed 0 and 1): ";
	// PLAY AS FIRST PLAYER FOR NOW
	vector<HarvestTile*>* htVector = player[0]->getHarvestTiles();
	printHarvestTile(htVector->at(0));
	cout << endl;
	printHarvestTile(htVector->at(1));
	int htIndex;
	cin >> htIndex;
	HarvestTile* harvestTile = htVector->at(htIndex);

	int row;
	int column;

	cout << "Where would you like to place the tile?\n" << "row: ";
	cin >> row;
	cout << "column: ";
	cin >> column;
	cout << endl;

	gameStart->getGBoard()->addHarvestTile(row, column, harvestTile);
	gameStart->getHand()->intializeHand();
	gameStart->getGBoard()->printGameBoard();
	cout << endl;
	gameStart->getHand()->displayHand();
	cout << endl;
	
	vector<BuildingTile*>* btVector = player[0]->getBuildings();
	for (int i = 0; i < btVector->size(); i++) {
		cout << "Tile "<< i + 1 << ": ";
		printBuildingTile(btVector->at(i));
	}
	cout << endl;
	player[0]->getVGBoard()->printVGMap();
	cout << endl;
	int btInput;
	cout << "Which building tile would you like to use? ";
	cin >> btInput;
	BuildingTile* btToAdd = btVector->at(btInput-1);
	int vgRow;
	int vgColumn;

	cout << endl;
	cout << "Where would you like to place the tile?\n" << "row: ";
	cin >> vgRow;
	cout << "column: ";
	cin >> vgColumn;
	cout << endl;

	Hand::ExchangeToken* exToken = new Hand::ExchangeToken(player[0], btToAdd, vgRow, vgColumn);
	gameStart->getHand()->exchange(exToken);

	player[0]->getVGBoard()->printVGMap();
	cout << endl;
	gameStart->getHand()->displayHand();
	cout << endl;
}

void menuOptions() {
	cout << "1 - GBMaps and Scoring Test" << endl << "2 - Harvest Tile Test" << endl << "3 - GBMapLoader Test" << endl << "4 - Player Test" << endl << "5 - GameStart Test" << endl << "0 - Exit" << endl << endl << "Which test would you like to run? ";
}

int main()
{
	/*MemoryLeak*/

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	int menuOption;
	menuOptions();
	cin >> menuOption;


	while (menuOption != 0) {
		cout << endl;
		switch (menuOption) {
		case 1:
			gbMapsTest();
			break;
		case 2:
			harvestTileTest();
			break;
		case 3:
			playGBMaps();
			break;
		case 4:
			playerTest();
			break;
		case 5:
			gameStartTest();
			break;
		}
		cout << endl;
		menuOptions();
		cin >> menuOption;
	}
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file