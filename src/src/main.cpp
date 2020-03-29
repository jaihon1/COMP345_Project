#include <iostream>
#include <iomanip>

#include "player.h"
#include "Dictionary.h"
#include "GBMaps.h"
#include "Resources.h"
#include "Scoring.h"

using namespace std;

void playerDriver() {
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
    cout << "Draw from BuildingDeck: " <<  bob.drawBuilding(buildingDeck) << endl;
    cout << "Deck size: " << buildingDeck.getSize() << endl;
    cout << "My Buildings size: " << bob.getNumberOfBuildingTiles() << endl;
    cout << "Draw from BuildingDeck: " <<  bob.drawBuilding(buildingDeck) << endl << endl;
    
    // Drawing items from Harvest Deck
    cout << "HarvestDeck size: " << harvestDeck.getSize() << endl;
    cout << "My Harvest size: " << bob.getNumberOfHarvestTiles() << endl;
    cout << "Draw from HarvestDeck: " <<  bob.drawHarvestTile(harvestDeck) << endl;
    cout << "H Deck size: " << harvestDeck.getSize() << endl;
    cout << "My Harvest size: " << bob.getNumberOfHarvestTiles() << endl;
    cout << "Draw from HarvestDeck: " <<  bob.drawHarvestTile(harvestDeck) << endl << endl;
    
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
                    cout << setw(8) << SquareStatusToString(inBoard->getSquareStatus(i, j)) << setw(8) <<" ";
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
    
    GBMaps* gameBoard = new GBMaps(2, 'a', scobj);
    Player player1;
    Player player2;

    scobj->reset_res();
    
    
    // 1. Place harvest tile on board
    /// Simulating player to use one of his own harvest tile
    HarvestTile* testHarvestTile = harvestDeck->draw();
    
    int row = 3;
    int column = 3;
    player1.placeHarvestTile(row, column, *testHarvestTile, *gameBoard);
    
    
    // TODO: 2. Determine Resources Gathered
    int res[4];
    scobj->get_res(res);
    
    
    // 3. Place building tile on board. Must be running in while(true) and until player decided to not do it anymore
    /// Simulating player to use one of his own harvest tile
    BuildingTile* testBuildingTile = buildingDeck->draw();
    
    int row_village = 1;
    int column_village = 2;
    player1.placeBuildingTile(row_village, column_village, *testBuildingTile);
    
    // TODO: 4. Share the Wealth
    
    
    
    // 5. Player draws building tiles. 1) Pick from game pool, 2) Pick from pool or deck
    /// Simulating player to select a buidling tile from pool and then select one more building tile from building deck
    int pick_index_1 = 1;
    int pick_index_2 = 3;
    int decision = 1;
    
    player1.pickFromBuildingPool(*building_pool, pick_index_1);
    
    if (decision == 0) {
        player1.pickFromBuildingPool(*building_pool, pick_index_2);
    }
    else if (decision == 1){
        player1.drawBuilding(*buildingDeck);
    }
    
    // 6. Reset Resource Markers back to 0 AND draw one harvest tile
    player1.drawHarvestTile(*harvestDeck);
    
    
    
    scobj->display_res();

    printGameBoard(gameBoard);
}

int main(int argc, const char * argv[]) {

    turnSequenceDriver();
        
    return 0;
}

