#include <iostream>
#include "..\modules\board\GBMaps.hpp"

using namespace std;

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
	cout << ResourceNameToString(inHarvestTile->getResource(0, 0)) << " ";
	cout << ResourceNameToString(inHarvestTile->getResource(0, 1)) << "\n";
	cout << ResourceNameToString(inHarvestTile->getResource(1, 0)) << " ";
	cout << ResourceNameToString(inHarvestTile->getResource(1, 1)) << "\n";
}

const char* SquareStatusToString(GBSquareStatus inSquareStatus) {
	switch (inSquareStatus) {
	case GBSquareStatus::Empty:
		return "Empty";
	case GBSquareStatus::HarvestTile:
		return "Harvest Tile";

	case GBSquareStatus::BuildingTile:
		return "Building Tile";

	case GBSquareStatus::PondTile:
		return "Pond Tile";

	case GBSquareStatus::Unavailable:
		return "Unavailable";

	}

	return "Error from SquareStatusToString";
}

void printGameBoard(GBMaps* inBoard) {
	for (int i = 0; i < inBoard->getRows(); i++) {
		for (int j = 0; j < inBoard->getColumns(); j++) {
			if (inBoard->getSquareStatus(i, j) == GBSquareStatus::HarvestTile) {
				printHarvestTile(inBoard->getHarvestTile(i, j));
			}
			else {
				cout << SquareStatusToString(inBoard->getSquareStatus(i, j)) << " ";
			}
		}
	}
}

void testFunction1() {
	GBMaps* gameBoard = new GBMaps(2, 'a');

	HarvestTile* testHarvestTile = new HarvestTile(ResourceName::Lumber, ResourceName::Rock, ResourceName::Sheep, ResourceName::Wheat); 
	testHarvestTile -> RotateRight();
	gameBoard->addHarvestTile(0, 3, testHarvestTile);

	printGameBoard(gameBoard);

	

}

int main()
{
	int hold;
	testFunction1();
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
