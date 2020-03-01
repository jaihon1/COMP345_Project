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
	GBMaps* gameBoard = new GBMaps(2, 'a', NULL);

	for (int i = 0; i < 5; i++) {
		HarvestTile* testHarvestTile = testDeck->draw();
		//ROTATE METHODS TEST
		//testHarvestTile -> RotateRight();
		gameBoard->addHarvestTile(3, i+1, testHarvestTile);
	}
	printGameBoard(gameBoard);
}

void gbMapLoaderTest() {
	GBMapLoader* testLoader = new GBMapLoader("C:\\Users\\Damian\\Documents\\Repos\\COMP345_Project\\data\\testSave.json");

	GBMapSaver* testSaver = new GBMapSaver();

	//testSaver->save(testLoader->getBoard(), "C:\\Users\\Damian\\Documents\\Repos\\COMP345_Project\\data\\testSave2.json");

	printGameBoard(testLoader->getBoard());
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

		int quit = 1;
		int xcoord = 0;
		int ycoord = 0;

		cout << "Would you like to add a harvest tile? Press 1 to continue. To quit, press 0. ";
		cin >> quit;
		while (quit != 0) {

			HarvestTile* testHarvestTile = testDeck->draw();
			cout << "Where would you like to place the tile?\n" << "x-coordinate: ";
			cin >> xcoord;
			cout << "y-coordinate: ";
			cin >> ycoord;
			cout << endl;
			gameBoard->addHarvestTile(xcoord, ycoord, testHarvestTile);
			printGameBoard(gameBoard);
			cout << endl;
			cout << "To place another tile, Press 1.  To see resource list press 2. Otherwise to quit press 0. ";
			cin >> quit;
			if (quit == 2) {
				sc->display_res();
				cout << "To place another tile, Press 1.  To see resource list press 2. Otherwise to quit press 0. ";
			}

		}
}

int main()
{
	int menuOption;
	int quit = 1;
	cout << endl << "1 - GBMaps Test" << endl << "2 - Harvest Tile Test" << endl << "3 - GBMapLoader Test" << endl << "Which test would you like to run? ";
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
			gbMapLoaderTest();
			break;
		}
		cout << "1 - GBMaps Test" << endl << "2 - Harvest Tile Test" << endl << "3 - GBMapLoader Test" << endl << "Which test would you like to run? Press 0 to quit. ";
		cin >> quit;
		return 0;

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
