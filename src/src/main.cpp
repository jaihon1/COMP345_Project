#include <iostream>
#include <fstream>
#include "modules/player/player.h"
#include "modules/tile/Dictionary.h"
#include "modules/board/GBMaps.h"
#include "modules/tile/Resources.h"

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

void printHarvestTile(HarvestTile* inHarvestTile) {
    cout << setw(8) << HarvestTile::ResourceNameToString(inHarvestTile->getResource(ResourceLocation::topLeft))
        << setw(8) << HarvestTile::ResourceNameToString(inHarvestTile->getResource(ResourceLocation::topRight)) << endl
        << setw(8) << HarvestTile::ResourceNameToString(inHarvestTile->getResource(ResourceLocation::bottomLeft))
        << setw(8) << HarvestTile::ResourceNameToString(inHarvestTile->getResource(ResourceLocation::bottomRight)) << endl;

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

int main(int argc, const char * argv[]) {
    playerTest();
}

