#include <iostream>
#include "modules/board/GBMaps.hpp"
#include "modules/board/VGMaps.hpp"
#include "modules/tile/BuildingTile.hpp"
#include "modules/VGMapLoader.h"
using namespace std;

int main(int argc, const char * argv[]) {
    
	//Damian's test code
	/**
	int id = 11;
    int players = 4;
    
    GBMaps map1(&id, &players);
    
    cout << "Board ID: " << map1.getIdAddress() << endl;
    cout << "Number of Players: " << map1.getNumberOfPlayers() << endl;
	**/

	VGMaps *bmap1 = new VGMaps(); 

	BuildingTile *t1 = new BuildingTile();

	bmap1->addNewBuildingTile(*t1, 1, 1); 



	system("pause"); 
    return 0;
}
