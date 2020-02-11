#include <iostream>
#include <fstream>

#include "HarvestTile.h"
#include "player.h"
#include "Dictionary.h"

using namespace std;


int main(int argc, const char * argv[]) {

    ResourceLocation location = ResourceLocation::topLeft;

    ResourceName lumber = ResourceName::Lumber;
    ResourceName rock = ResourceName::Rock;
    ResourceName sheep = ResourceName::Sheep;
    ResourceName wheat = ResourceName::Wheat;
    
    HarvestTile harvestTile1(lumber, rock, sheep, wheat);
    HarvestTile harvestTile2(rock, rock, sheep, wheat);
    
    Player bob;
    
    bob.addHarvestTile(harvestTile1);
    bob.addHarvestTile(harvestTile2);
    cout << "Before:" << endl;
    bob.getHarvestTiles();
    
    bob.removeHarvestTile(harvestTile1);
    cout << "After:" << endl;
    bob.getHarvestTiles();
    
//    cout << "Address of new tile main: " << &harvestTile1 << endl;
    
//    if(bob.addHarvestTile(harvestTile1).getResource(location) == ResourceName::Lumber) {
//        cout << "Lumber" << endl;
//    }

    return 0;
}
