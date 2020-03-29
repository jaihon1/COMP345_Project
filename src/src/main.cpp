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

void part3Drive() {
    HarvestDeck* testDeck = new HarvestDeck();
    
    Scoring *scobj = new Scoring();
    GBMaps* gameBoard = new GBMaps(2, 'a', scobj);

    scobj->reset_res();

    for (int i = 0; i < 0; i++) {
        HarvestTile* testHarvestTile = testDeck->draw();
        //ROTATE METHODS TEST
        //testHarvestTile -> RotateRight();
        gameBoard->addHarvestTile(3, i+1, testHarvestTile);
        scobj->display_res();
    }

    printGameBoard(gameBoard);
}

int main(int argc, const char * argv[]) {
//    playerDriver();
    
    part3Drive();
    
    
    return 0;
}

