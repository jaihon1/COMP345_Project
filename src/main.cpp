
#include "src/modules/board/VGMaps.hpp"
#include "src/modules/tile/BuildingTile.hpp"

#include <iostream>
using namespace std; 


/**/
int main()
{
	BuildingColorType * type1 = new BuildingColorType(BuildingColorType::GreenSheep); 
	BuildingStatus *status1 = new BuildingStatus(BuildingStatus::Normal); 

	BuildingTile t1(type1, status1); //on stack? do I delete?
	cout << t1.getBuildingNum() << endl;

	BuildingColorType * type2 = new BuildingColorType(BuildingColorType::RedLumber);
	BuildingStatus *status2 = new BuildingStatus(BuildingStatus::Normal);
	BuildingTile t2(type2, status2); //why??? 

	cout << t2.getBuildingNum() << endl;

	cout << "Created building tile"; 

	//A a(); stack
	//A* aPtr = &a; 

	//driver?
	return 0; 
}


//main for VGMaps

/*
int main()
{
	VGMaps v(); 
	//print the map out 
	for (int i = 0; i < ; i++)
	cout << "Created Map Tile"; 

	return 0; 
}
*/