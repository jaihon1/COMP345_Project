#include "modules/VGMapLoader.h"
#include "modules/board/VGMaps.h"
#include "modules/tile/Resources.h"
#include "nlohmann/json.hpp"
#include <fstream>
#include <string>
#include <ostream>
#include <iostream>
#include <stdlib.h>
using namespace std;


//Methods to print out VGMap to see if it works in creating it 
//Main for Map Loader part 3 

//Test run for VGMap Loader

int main()
{
	//create a new VGBoard
	VGMaps *va = new VGMaps(); 

	int ro = *(va->rows);
	int co = *(va->columns);

	va->printVGMap(); 
	cout << "created VGMap" << endl;


	
	cout << "Add building" << endl; 



	BuildingColorType * type1 = new BuildingColorType(BuildingColorType::GreenSheep);
	BuildingStatus *status1 = new BuildingStatus(BuildingStatus::Normal);

	BuildingTile *t1 = new BuildingTile(type1, status1);

	/*
	cout << BuildingTile::Building_typeToChar(t1->getBuildingColorType()) << endl; 
	cout << BuildingTile::Building_statusToChar(t1->getSide()) << endl;
	*/
	cout << BuildingTile::Building_intToChar(t1->getBuildingNum()) << endl;
	

	va->addNewBuildingTile(*t1, 0, 0);
	

	cout << "Current map" << endl;
	va->printVGMap();

	
	cout << "Saving VGMAP out" << endl; 
	
	VGMapSaver *s = new VGMapSaver();

	//s->save(va, "C:\json_test\VGMaptest.json");  -> BAD 
	s->save(va, "C:\\json_test\\VGMaptest5.json");

	cout << "Saved va map" << endl; 
	

	
	VGMapLoader * m = new VGMapLoader(); 

	cout << "\n"; 
	cout << "Loading VGMap in " << endl; 

	VGMapLoader *l = new VGMapLoader("C:\\json_test\\VGMaptest5.json");
	
	cout << "\n";
	cout << "\n";
	cout << "Sucess in reading" << endl; 

	cout << "Current MAP" << endl;
	
	va->printVGMap(); 



	return 0; 
}