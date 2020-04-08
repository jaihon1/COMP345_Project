/*

#include <iostream>
#include <iomanip>
#include "GBMaps.h"
#include "../tile/Dictionary.h"
#include "../tile/Resources.h"
#include "../Scoring/Scoring.h"

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
		cout << setw(8) << columnNUM << setw(8)<<" ";
	}
	cout << endl;

	for (int i = 0; i < 7; i++) {
		cout << setw(2)<<i;
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

void testFunction1() {
	GBMaps* gameBoard = new GBMaps(2, 'a', NULL);

	for (int i = 0; i < 5; i++) {
		HarvestTile* testHarvestTile = testDeck->draw();
		//ROTATE METHODS TEST
		testHarvestTile->RotateRight();
		gameBoard->addHarvestTile(3, i + 1, testHarvestTile);
	}
	printGameBoard(gameBoard);
}


int main()
{
	int begin;
	cout << "Would you like to begin? Press any number.  To quit press 0. \n";
	cin >> begin;

	int players;

	if (begin) {
		cout << "How many players? Select 2, 3, or 4: ";
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
		while (quit == 1 || quit == 2) {

			if (quit == 1) {
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
				}
				cout << "To place another tile, Press 1.  To see resource list press 2. Otherwise to quit press 0. ";
				cin >> quit;
			}
		}
	}

}
*/ 