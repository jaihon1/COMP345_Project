
#include "src/modules/board/VGMaps.hpp"
#include "src/modules/tile/BuildingTile.hpp"
#include <iostream>
using namespace std; 

/*
int main()
{
	//read access exception???? 
	BuildingColorType * type = new BuildingColorType(BuildingColorType::GreenSheep); 
	BuildingStatus *status = new BuildingStatus(BuildingStatus::Normal); 

	BuildingTile t1(type, status); //on stack? 
	cout << "Created building tile"; 

	//A a(); stack
	//A* aPtr = &a; 

	//driver?
	return 0; 
}
*/

//main for VGMaps

int main()
{
	VGMaps v(); 
	cout << "Created Map Tile"; 

	return 0; 
}