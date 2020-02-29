
#include "modules/board/VGMaps.hpp"
#include "modules/tile/Resources.h"
#include <string>
#include <ostream>
#include <iostream>
#include <stdlib.h>
using namespace std; 

string status_to_string(VGSlotStatus s)
{
	switch (s)
	{
	case VGSlotStatus::Empty:
		return "Empty";
	case VGSlotStatus::Taken:
		return "Taken"; 
	case VGSlotStatus::Unavailable:
		return "Unavailable";
	}

}

string colortype_to_string(BuildingColorType c)
{
	switch (c)
	{
	case BuildingColorType::GreenSheep:
		return "GreenSheep"; 
	case BuildingColorType::GreyRock:
		return "GreyRock"; 
	case BuildingColorType::RedLumber:
		return "RedLumber"; 
	case BuildingColorType::YellowHay:
		return "YellowHay"; 
	case BuildingColorType::None:
		return "None"; 
	}
}
/* building Tile test
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


int main()
{
	//test 
	VGMaps *v = new VGMaps();
	//VGMaps* v =  &VGMaps();

	//VGMaps* gg(); //most vexing part annoying error 
	//int r = *(v.rows);
	//int c = *(v.columns); 

	//int *r = map->rows; 
	//int *c = map->columns; 
	
	int ro = *(v->rows); 
	int co = *(v->columns); 

	/*
	for (int i = 0; i < ro; i++)
	{
		for (int j = 0;  j < co; j++)
		{
			cout << "TILE ";
		}
		cout << "\n";
		cout << "==========================" << endl; 
	}
	cout << "created VGMap" << endl; 

	cout << "More test" << endl; 
	cout << "\n"; 
	//give an example of VGMaps filled 
	*/
	

	for (int i = 0; i < ro; i++)
	{
		for (int j = 0; j < co; j++)
		{
			//VGSquare *s = v->village_board[i]; 
			//VGSlotStatus check = v->village_board[i][j].VGstatus; 
			//cout << status_to_string(check); 

			BuildingColorType check2 = v->village_board[i][j].VGSquare_type; 
			cout << colortype_to_string(check2) << "   "; 
		
		}
		cout << "\n";
		cout << "=====================================" << endl;
	}
	cout << "created VGMap" << endl;

	cout << "\n"; 
	cout << "Adding Building Tile" << endl; 

	
	BuildingColorType * type1 = new BuildingColorType(BuildingColorType::GreenSheep);
	BuildingStatus *status1 = new BuildingStatus(BuildingStatus::Normal);

	BuildingTile *t1 = new BuildingTile(type1, status1); 

	v->addNewBuildingTile(*t1, 0, 0);

	/*
	cout << "creating 6 types of each 4 types" << endl; 

	vector <BuildingTile> *greens = new vector<BuildingTile>(6); 
	for (int i = 0; i < 6; i++)
	{
		BuildingColorType *g = new BuildingColorType(BuildingColorType::GreenSheep); 
		BuildingStatus *t = new BuildingStatus(BuildingStatus::Normal); 
		BuildingTile *temp = new BuildingTile(g, t); //destroys it??? 

		cout << "Created new building" << endl; 

		greens->insert(greens->begin() + i, *temp); 
		cout << "created 6 green building tiles" << endl; 

	}
	*/

	
	cout << "\n"; 
	cout << "Current MAP" << endl; 
	
	for (int i = 0; i < ro; i++)
	{
		for (int j = 0; j < co; j++)
		{
			//VGSquare *s = v->village_board[i]; 
			//VGSlotStatus check = v->village_board[i][j].VGstatus; 
			//cout << status_to_string(check); 

			BuildingColorType check2 = v->village_board[i][j].VGSquare_type;
			cout << colortype_to_string(check2) << "     ";

	
		}
		cout << "\n";
		cout << "=============================================" << endl;
	}

	BuildingColorType * type2 = new BuildingColorType(BuildingColorType::GreenSheep);
	BuildingStatus *status2 = new BuildingStatus(BuildingStatus::Normal);

	BuildingTile *t2 = new BuildingTile(type2, status2);

	//v->addNewBuildingTile(*t2, 2, 2); //adding greensheep at another location but it has been previously placed - throws the right errors
	v->addNewBuildingTile(*t2, 0, 1); //GIVES two unavailable and does not add any element OR doesn't bypass and places the tile again (
	//v->addNewBuildingTile(*t2, 2, 3);


	

	return 0; 
}

