#include <iostream>
#include <iomanip>

#include "../modules/board/GBMaps.h"
#include "../modules/tile/Dictionary.h"
#include "../modules/tile/Resources.h"
#include "../modules/Scoring/Scoring.h"
#include "../modules/player/player.h"
#include "../modules/board/VGMaps.h"
#include "../GameObservers/GameObservers.h"
#include "../GameObservers/ViewObserver.h"
#include "../modules/ConsoleLogger/ConsoleLogger.h"

using namespace std;

void playerDriver() {
	// Initializing variables
	Player bob;
	// GBMaps map(4, 'b');
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
		}
	}
}

void turnSequenceDriver() {
	// Setup
	HarvestDeck* harvestDeck = new HarvestDeck();
	BuildingDeck* buildingDeck = new BuildingDeck();
	Scoring *scobj = new Scoring();
	BuildingPool *building_pool = new BuildingPool(buildingDeck);

	int players_num = 2;
	GBMaps* gameBoard = new GBMaps(players_num, 'a', scobj);
	Player player1;
	Player player2;

	scobj->reset_res();


	// 1. Player 1 Turn: Place harvest tile on board
	/// Simulating player to use one of his own harvest tile
	HarvestTile* testHarvestTile = harvestDeck->draw();

	int row = 3;
	int column = 3;
	int ship = 3;
	if (rand() % 2 == 0) {
		player1.placeHarvestTile(row, column, *testHarvestTile, *gameBoard);
		cout << endl << "placeHarvestTile" << endl;
	}
	else {
		player1.placeShipmentTile(row, column, *testHarvestTile, *gameBoard, ship);
		cout << endl << "placeShipmentTile" << endl;
	}

	// 2. Determine Resources Gathered
	int res[4];
	scobj->get_res(res);


	// 3. Place building tile on board. Must be running in while(true) and until player decided to not do it anymore
	/// Simulating player to use one of his own harvest tile
	BuildingTile* testBuildingTile = buildingDeck->draw();

	int row_village = 1;
	int column_village = 2;
	player1.placeBuildingTile(row_village, column_village, *testBuildingTile);
	scobj->remove_res(static_cast<int>(testBuildingTile->getBuildingColorType()), row_village);//remove resource match the type of building???

	// 4. Share the Wealth
	scobj->get_res(res);//update res left
	cout << endl << "Sharing the Wealth" << endl;

	/// Each player takes a turn to use remaining resources. Simulating
	for (int i = 1; i < players_num; i++) { //start from next player 1
		scobj->display_res();
		int player_decision_pass = rand() % 2; // must take input from player (1 == use resource) (0 == pass turn)

		if (player_decision_pass == 1) {
			int res_usage[4];
			for (int i = 0; i < 4; i++) {
				//res_usage[i] = rand() % 10;
				cout << endl << "Type " << i << " .How many: " << endl;
				cin >> res_usage[i];
			}

			/// Use resources
			for (int i = 0; i < 4; i++)
			if (res_usage[i]>0) {
				if (scobj->remove_res(1, res_usage[i]) == 0)//return 0 mean not enough
					cout << endl << "Not enough resource type " << i << endl;
			}
		}
		else {
			cout << endl << "Player " << i << " passed" <<endl;
		}
	}

	// 5. Player draws building tiles. 1) Pick from game pool, 2) Pick from pool or deck
	/// Simulating player to select a buidling tile from pool and then select one more building tile from building deck
	scobj->get_res(res);
	int total_building = 0;
	for (int i = 0; i < 4; i++) {
		if( res[i]==0)
			total_building++;
	}
	int pool_pick = total_building % 3;
	for (int i = 0; i < pool_pick; i++) {
		player1.pickFromBuildingPool(*building_pool, i);
	}
	for (int i = 0; i < total_building - pool_pick; i++) {
		player1.drawBuilding(*buildingDeck);
	}

	// 6. Reset Resource Markers back to 0 AND draw one harvest tile
	player1.drawHarvestTile(*harvestDeck);

	cout << endl << "End of Turn" << endl;
	scobj->display_res();

	printGameBoard(gameBoard);
}

void scoringDriver() {
	// Setup
	HarvestDeck* harvestDeck = new HarvestDeck();
	BuildingDeck* buildingDeck = new BuildingDeck();
	Scoring *scobj = new Scoring();
	BuildingPool *building_pool = new BuildingPool(buildingDeck);
	srand(time(NULL));

	Player p[4];
	VGMaps* m[4];
	for (int k = 0; k < 4; k++) {
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 5; j++) {
				BuildingTile* testBuildingTile = buildingDeck->draw();
				p[k].placeBuildingTile(i, j, *testBuildingTile);
			}
		}
		m[k] = p[k].getVGBoard();
	}
	for (int k = 0; k < 4; k++)
		p[k].getVGBoard()->printVGMap();

	scobj->get_winner(m);
}

//ConsoleLoggerHelper.exe must be in the same folder with main
void observerDriver() {
	// Setup
	HarvestDeck* harvestDeck = new HarvestDeck();
	BuildingDeck* buildingDeck = new BuildingDeck();
	Scoring *scobj = new Scoring();
	BuildingPool *building_pool = new BuildingPool(buildingDeck);
	srand(time(NULL));

	Player p[2];
	VGMaps* m[2];
	scobj->set_id(1, 1);
	scobj->set_id(2, 2);
	ViewObserver o1(scobj);
	//ViewObserver o2(scobj);
	scobj->notify();
	
	std::cout << "notify 0 " << std::endl;
	//do something

	o1.display();

	std::cout << "notify 1 " << std::endl;
	//do something

	o1.display();

	//scobj->detach(&o1);
	//scobj->detach(&o2);

	std::cout << "notify 2 " << std::endl;
	//do something

	o1.display();
}

void consoleDriver() {
	printf("Hi , i'm the main-process , and  i'm going to show you 2 more consoles...");
	CConsoleLoggerEx console1;
	console1.Create("Observer 1");
	console1.cprintf(CConsoleLoggerEx::COLOR_WHITE | CConsoleLoggerEx::COLOR_BACKGROUND_BLACK, "Hello Damian");


	CConsoleLoggerEx console2;
	console2.Create("Observer 2");
	console2.cprintf(CConsoleLoggerEx::COLOR_WHITE | CConsoleLoggerEx::COLOR_BACKGROUND_BLACK, "Hello Tiffany");
}

int main(int argc, const char * argv[]) {

	//turnSequenceDriver();
	//scoringDriver1();	
	//consoleDriver;
	observerDriver();



	system("pause");
	return 0;
}