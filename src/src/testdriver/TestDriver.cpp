#include <iostream>
#include <iomanip>
#include "../modules/board/GBMaps.h"
#include "../modules/GBMapLoader/GBMapLoader.h"
#include "../modules/tile/Dictionary.h"
#include "../modules/tile/Resources.h"
#include "../modules/Scoring/Scoring.h"

using namespace std;

HarvestDeck* testDeck = new HarvestDeck();

const char* SquareStatusToString(GBSquareStatus inSquareStatus) {
	switch (inSquareStatus) {
	case GBSquareStatus::Empty:
		return "Empty";
	case GBSquareStatus::HarvestTile:
		return "Harvest";

	case GBSquareStatus::BuildingTile:
		return "Buildin";

	case GBSquareStatus::PondTile:
		return "Pond";

	case GBSquareStatus::Unavailable:
		return "Unavail";

	}

	return "Error from SquareStatusToString";
}

void printHarvestTile(HarvestTile* inHarvestTile) {

	cout << setw(8) << HarvestTile::ResourceNameToString(inHarvestTile->getResource(ResourceLocation::topLeft)) 
		<< setw(8) << HarvestTile::ResourceNameToString(inHarvestTile->getResource(ResourceLocation::topRight))<<endl
		<< setw(8) << HarvestTile::ResourceNameToString(inHarvestTile->getResource(ResourceLocation::bottomLeft))
		<< setw(8) << HarvestTile::ResourceNameToString(inHarvestTile->getResource(ResourceLocation::bottomRight))<<endl;
	
}

void printGameBoard(GBMaps* inBoard) {
	cout << "  ";
	for (int columnNUM = 0; columnNUM < 7; columnNUM++) {
		cout << setw(8) << columnNUM << setw(8) << " ";
	}
	cout << endl;

	for (int i = 0; i < 7; i++) {
		cout << setw(2) << i;
		for (int k = 0; k < 2; k++) {
			for (int j = 0; j < 7; j++) {

				if (inBoard->getSquareStatus(i, j) == GBSquareStatus::HarvestTile) {
					HarvestTile* tileTemp = inBoard->getHarvestTile(i, j);
					if (k == 0) {
						cout << setw(8) << HarvestTile::ResourceNameToString(tileTemp->getResource(ResourceLocation::topLeft));
						cout << setw(8) << HarvestTile::ResourceNameToString(tileTemp->getResource(ResourceLocation::topRight));
					}
					else {
						cout << setw(8) << HarvestTile::ResourceNameToString(tileTemp->getResource(ResourceLocation::bottomLeft));
						cout << setw(8) << HarvestTile::ResourceNameToString(tileTemp->getResource(ResourceLocation::bottomRight));
					}
				}
				else {
					cout << setw(8) << SquareStatusToString(inBoard->getSquareStatus(i, j)) << setw(8) << " ";
				}
			}
			cout << endl;
			if (k == 0) {
				cout << "  ";
			}
		}
	}
}

void harvestTileTest() {
	
		HarvestTile* testHarvestTile = testDeck->draw();
		printHarvestTile(testHarvestTile);
		char yesNo;
		char rotate;
		cout << "Would you like to rotate the tile? y/n "<<endl;
		cin >> yesNo;
		//ROTATE METHODS TEST
		while (yesNo == 'y') {
			cout << "Right = r, Left = l: ";
			cin >> rotate;
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
			cout << "Again? y/n ";
			cin >> yesNo;
		}
	
}

void gbMapsTest() {

	int players;

		cout << "Welcome to GBMapsTest"<< endl << "How many players? Select 2, 3, or 4: ";
		cin >> players;

		//SCORING OBJECT CONSTRUCTION
		Scoring* sc = new Scoring();

		//GAMEBOARD CONSTRUCTION
		GBMaps* gameBoard = new GBMaps(players, 'a', sc);
		printGameBoard(gameBoard);
		cout << endl;

		int quit;
		int row;
		int column;

		cout << "Would you like to add a harvest tile? Press 1 to continue. To quit, press 0. ";
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
				printGameBoard(gameBoard);
				cout << endl;
				break;
			case 2:
				//sc->display_res();
				cout << "Rock:   " << sc->get_stone() << endl;
				cout << "Lumber: " << sc->get_lumber() << endl;
				cout << "Wheat:  " << sc->get_wheat() << endl;
				cout << "Sheep:  " << sc->get_sheep() << endl;
			
				break;
			default:
				cout << "Sorry invalid input." << endl;
				break;
			}
			cout << "To place another tile, Press 1.  To see resource list press 2. Otherwise to quit press 0. ";
			cin >> quit;
			cout << endl;
		}
}

void runGame(GBMaps* gameBoard) {

	printGameBoard(gameBoard);

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
		printGameBoard(gameBoard);
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

}

void playGBMaps() {
	bool flag = true;
	while (flag) {
		int oldOrNew;
		cout << "Welcome to New Haven" << endl << "1 - Start a new game" << endl << "2 - Load game" << endl<< "0 - return to previous menu" << endl << "Which would you like to do: ";
		cin >> oldOrNew;

		// SCORING OBJECT CONSTRUCTION
		Scoring* sc = new Scoring();

		switch (oldOrNew) {
		case 0:
			flag = false;
			break;

		case 1: {
			int players;
			cout << "How many players? Select 2, 3, or 4: ";
			cin >> players;

			//GAMEBOARD CONSTRUCTION
			GBMaps* gameBoard = new GBMaps(players, 'a', sc);
			runGame(gameBoard);
			break;
		}
		case 2: {
			string filePath;
			cout << "Please enter the file path of the game you wish to load: " << endl;
			cin >> filePath;
			// LOADER CONSTRUCTION
			GBMapLoader* testLoader = new GBMapLoader(&filePath[0], sc);
			runGame(testLoader->getBoard());
			break;
		}
		default:
			cout << "Sorry invalid input, please choose again" << endl;
			break;
		}
	}
}


void menuOptions() {
	cout << "1 - GBMaps Test" << endl << "2 - Harvest Tile Test" << endl << "3 - GBMapLoader Test" << endl << "Which test would you like to run? ";
}

int main()
{
	int menuOption;
	int quit = 1;
	menuOptions();
	cin >> menuOption;

	while (quit != 0) {
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
		}
		menuOptions();
		cin >> quit;
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
