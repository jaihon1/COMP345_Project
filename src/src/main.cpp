#include <iostream>
#include <fstream>
#include "modules/player/player.h"
#include "modules/tile/Dictionary.h"
#include "modules/board/GBMaps.h"
#include "modules/tile/Resources.h"
#include "modules/Scoring/Scoring.h"

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
    testDeck = nullptr;

}

void gbMapsTest() {

    int players;

    cout << "Welcome to GBMapsTest" << endl << "How many players? Select 2, 3, or 4: ";
    cin >> players;

    //SCORING OBJECT CONSTRUCTION
    Scoring* sc = new Scoring();

    //HARVEST DECK OBJECT CONSTRUCTION
    HarvestDeck* testDeck = new HarvestDeck();

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

    delete sc;
    delete testDeck;
    delete gameBoard;
}


int main(int argc, const char * argv[]) {
    playerTest();
//    harvestTileTest();
//    gbMapsTest();
}

