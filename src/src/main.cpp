#include <iostream>
#include "player.h"
#include "Dictionary.h"
#include "GBMaps.h"
#include "Resources.h"

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

int main(int argc, const char * argv[]) {
    playerDriver();
    
    return 0;
}

