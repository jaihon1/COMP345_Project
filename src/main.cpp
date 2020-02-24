
#include "src/modules/board/VGMaps.hpp"
#include "src/modules/tile/BuildingTile.hpp"

#include <iostream>
using namespace std; 


/*
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
*/

//main for VGMaps

/**/
int main()
{
	//test 
	//VGMaps *map = new VGMaps();
	VGMaps* v =  &VGMaps();

	VGMaps* gg(); //most vexing part annoying error 
	//int r = *(v.rows);
	//int c = *(v.columns); 

	//int *r = map->rows; 
	//int *c = map->columns; 

	int ro = *(v->rows); 
	int co = *(v->columns); 

	for (int i = 0; i < ro; i++)
	{
		for (int j = 0;  j < co; j++)
		{
			cout << "TILE ";
		}
		cout << "\n";
		cout << "==========================" << endl; 
	}
	cout << "created VGMap"; 

	
	//enum function with a switch statements 
	//give an example of VGMaps filled 
	//edits 

	BuildingColorType * type1 = new BuildingColorType(BuildingColorType::GreenSheep);
	BuildingStatus *status1 = new BuildingStatus(BuildingStatus::Normal);

	BuildingTile t1(type1, status1); //on stack? do I delete?

	v->addNewBuildingTile(t1, 1, 1); 
	cout << "added new tile" << endl; 

	for (int i = 0; i < ro; i++)
	{
		for (int j = 0; j < co; j++)
		{
			//BuildingColorType e = *v[i][j].VGSquare_type; 
			
		}
		cout << "\n";
		cout << "==========================" << endl;
	}
	cout << "created VGMap";


	return 0; 
}

