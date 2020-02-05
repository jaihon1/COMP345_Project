  
#include <iostream>
#include <fstream>

#include "HarvestTile.hpp"
#include "loader.hpp"
#include "player.hpp"
#include "Dictionary.hpp"

using namespace std;



int main(int argc, const char * argv[]) {


    ResourceName lumber = ResourceName::Lumber;
    ResourceName rock = ResourceName::Rock;
    ResourceName sheep = ResourceName::Sheep;
    ResourceName wheat = ResourceName::Wheat;
    
    HarvestTile harvestTile1(lumber, rock, sheep, wheat);
    HarvestTile harvestTile2(rock, rock, sheep, wheat);
    HarvestTile harvestTile3(lumber, lumber, sheep, wheat);
    HarvestTile harvestTile4(sheep, rock, sheep, lumber);
    
    
    if(harvestTile1.getResource(0, 1) == ResourceName::Lumber) {
        cout << "Lumber" << endl;
    }

    
//    Loader myLoader;
//    ofstream myfile ("/Users/dzhay/Github/COMP345_Project/src/test.txt");
//    if (myfile.is_open())
//    {
//      myfile << "This is a line.\n";
//      myfile << "This is another line.\n";
//      myfile.close();
//    }
//    else cout << "Unable to open file";
//
//	
//    myLoader.read("/Users/dzhay/Github/COMP345_Project/src/test.txt");

    return 0;
}
