#include <iostream>
#include <iomanip>
#include "../modules/board/GBMaps.h"
#include "../modules/GBMapLoader/GBMapLoader.h"
#include "../modules/tile/Dictionary.h"
#include "../modules/tile/Resources.h"

using namespace std;

HarvestDeck* testDeck = new HarvestDeck();

const char* ResourceNameToString(ResourceName inResourceName) {
	switch (inResourceName) {
	case ResourceName::Lumber:
		return "lumber";
	
	case ResourceName::Rock:
		return "rock";

	case ResourceName::Sheep:
		return "sheep";

	case ResourceName::Wheat:
		return "wheat";
	}

	return "Error from ResourceNameToString";
}

void printHarvestTile(HarvestTile* inHarvestTile) {
	cout << "\n";
	
	
}

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
	for (int i = 0; i < 7; i++) {
		for (int k = 0; k < 2; k++) {
			for (int j = 0; j < 7; j++) {
				if (inBoard->getSquareStatus(i, j) == GBSquareStatus::HarvestTile) {
					HarvestTile* tileTemp = inBoard->getHarvestTile(i, j);
					if (k == 0) {
						cout << setw(8) << ResourceNameToString(tileTemp->getResource(ResourceLocation::topLeft));
						cout << setw(8) << ResourceNameToString(tileTemp->getResource(ResourceLocation::topRight));
					}
					else {
						cout << setw(8) << ResourceNameToString(tileTemp->getResource(ResourceLocation::bottomLeft));
						cout << setw(8) << ResourceNameToString(tileTemp->getResource(ResourceLocation::bottomRight));
					}		
				}
				else {
					cout << setw(8) << SquareStatusToString(inBoard->getSquareStatus(i, j)) << setw(8) <<" ";
				}
			}
			cout << endl;
		}
	}
}

void testFunction1() {
	GBMaps* gameBoard = new GBMaps(2, 'a');

	for (int i = 0; i < 5; i++) {
		HarvestTile* testHarvestTile = testDeck->draw();
		//ROTATE METHODS TEST
		//testHarvestTile -> RotateRight();
		gameBoard->addHarvestTile(3, i+1, testHarvestTile);
	}
	printGameBoard(gameBoard);

	

}

void testFunction2() {
	GBMapLoader* testLoader = new GBMapLoader("C:\\Users\\Damian\\Documents\\Repos\\COMP345_Project\\data\\testMap.json");

	//GBMapSaver* testSaver = new GBMapSaver();

	//testSaver->save(testLoader->getBoard(), "C:\\Users\\Damian\\Documents\\Repos\\COMP345_Project\\data\\testSave.json");

	//printGameBoard(testLoader->getBoard());
}

int main()
{
	int hold;

	//testFunction1();
	testFunction2();
	cin >> hold;

	return 0;

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
