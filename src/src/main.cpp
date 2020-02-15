#include <iostream>
#include <fstream>

#include "HarvestTile.h"
#include "player.h"
#include "Dictionary.h"

#include "GBMaps.h"
#include "BuildingTile.h"
#include "BuildingDeck.h"

using namespace std;


int main(int argc, const char * argv[]) {

    ResourceLocation location = ResourceLocation::topLeft;

    ResourceName lumber = ResourceName::Lumber;
    ResourceName rock = ResourceName::Rock;
    ResourceName sheep = ResourceName::Sheep;
    ResourceName wheat = ResourceName::Wheat;
    
    HarvestTile harvestTile1(lumber, rock, sheep, wheat);
    HarvestTile harvestTile2(rock, rock, sheep, wheat);
	
	int id = 11;
    int players = 4;

    
    Player bob;
    
    bob.addHarvestTile(harvestTile1);
    
    BuildingDeck buildingDeck;
    
    
    
    
    
//    bob.addHarvestTile(harvestTile2);
//    cout << "Before:" << endl;
//    bob.getHarvestTiles();
//
//    bob.removeHarvestTile(harvestTile1);
//    cout << "After:" << endl;
//    bob.getHarvestTiles();
    
//    cout << "Address of new tile main: " << &harvestTile1 << endl;
    
//    if(bob.addHarvestTile(harvestTile1).getResource(location) == ResourceName::Lumber) {
//        cout << "Lumber" << endl;
//    }
//
//
//    cout << "Board ID: " << map1.getIdAddress() << endl;
//    cout << "Number of Players: " << map1.getNumberOfPlayers() << endl;


//	VGMaps bmap1 = new VGMaps();
//
//	BuildingTile t1 = new BuildingTile();
//
//	bmap1.addNewBuildingTile(t1, 1, 1);




    
	system("pause"); 

    return 0;
}
